#pragma once

#include"dsl_core.hpp"

#include<list>
#include<unordered_map>
#include<optional>

FORWARD_DECLARE_TEST_CLASS(CacheLRU_Test)

namespace rw {
    namespace dsl {
        template <typename Key, typename Value>
        class ICache {
        public:
            // Constructor with capacity
            explicit ICache(size_t capacity) : _capacity(capacity) {}

            // Get the value associated with the key, if it exists
            virtual std::optional<Value> get(const Key& key) = 0;

            // Put the key-value pair in the cache
            virtual bool set(const Key& key, const Value& value) = 0;

            // Get the number of key-value pairs in the cache
            virtual size_t size() const = 0;

            // Get the capacity of the cache
            virtual size_t capacity() const { return _capacity; }

            // Virtual destructor
            virtual ~ICache() = default;

            virtual bool resize(size_t capacity) = 0;

        protected:
            size_t _capacity;
        };

        template <typename Key, typename Value>
        class CacheLRU
        :public ICache<Key,Value> {
            MAKE_FRIEND_TEST_CLASS(CacheLRU_Test)
        public:
            explicit CacheLRU(size_t capacity) 
                : ICache<Key, Value>(capacity){
                _cache.reserve(capacity);
            }

            std::optional<Value> get(const Key& key) override {
                auto it = _cache.find(key);
                if (it == _cache.end()) {
                    return std::nullopt;
                }
                _list.splice(_list.begin(), _list, it->second);
                return it->second->second;
            }

            bool set(const Key& key, const Value& value) override {
                // If the key is already present, update its value and move it to the front of the list
                auto it = _cache.find(key);
                if (it != _cache.end()) {
                    // Update the value
                    it->second->second = value;
                    // Move the key to the front of the list
                    _list.splice(_list.begin(), _list, it->second);
                    // Return false since we did not insert a new key
                    return false;
                }
                if (_cache.size() >= this->_capacity) {
                    // Remove the least recently used key
                    _cache.erase(_list.back().first);
                    _list.pop_back();
                }
                // Insert the new key at the front of the list
                _list.emplace_front(key, value);
                // Insert the new key in the cache
                _cache.insert({ key, _list.begin() });
                // Return true since we inserted a new key
                return true;
            }

            size_t size() const override {
                return _cache.size();
            }

            bool resize(size_t capacity) {
                if (capacity < this->_capacity) {
                    // Remove the least recently used keys until the size of the cache is less than the new capacity
                    while (_cache.size() > capacity) {
                        _cache.erase(_list.back().first);
                        _list.pop_back();
                    }
                }
                this->_capacity = capacity;
                return true;
            }
        private:
            std::list<std::pair<Key, Value>> _list;
            std::unordered_map<Key, typename std::list<std::pair<Key, Value>>::iterator> _cache;
        };


    } // namespace dsl

} // namespace rw
