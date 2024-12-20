#pragma once

#include "dsl_Cache.hpp"
#include <vector>
#include <unordered_map>
#include <optional>

namespace rw {
    namespace dsl {
        template <typename Key, typename Value>
        class CacheClock : public ICache<Key, Value> {
        private:
            struct Node {
                Key key;
                Value value;
                bool referenceBit;
                Node(Key key, Value value)
                    : key(key), value(value), referenceBit(true) {
                }
            };

            std::vector<std::shared_ptr<Node>> _cache;
            std::unordered_map<Key, std::shared_ptr<Node>> _cacheMap;
            size_t _clockHand;

        public:
            CacheClock(size_t capacity)
                : ICache<Key, Value>(capacity), _clockHand(0) {
            }

            ~CacheClock() {}

            std::optional<Value> get(const Key& key) override {
                auto it = _cacheMap.find(key);
                if (it == _cacheMap.end()) {
                    return std::nullopt;
                }
                it->second->referenceBit = true;
                return it->second->value;
            }

            bool set(const Key& key, const Value& value) override {
                auto it = _cacheMap.find(key);
                if (it != _cacheMap.end()) {
                    it->second->value = value;
                    it->second->referenceBit = true;
                    return false;
                }

                if (_cache.size() >= _capacity) {
                    while (_cache[_clockHand]->referenceBit) {
                        _cache[_clockHand]->referenceBit = false;
                        _clockHand = (_clockHand + 1) % _capacity;
                    }
                    _cacheMap.erase(_cache[_clockHand]->key);
                    _cache[_clockHand] = std::make_shared<Node>(key, value);
                    _cacheMap[key] = _cache[_clockHand];
                    _clockHand = (_clockHand + 1) % _capacity;
                }
                else {
                    auto node = std::make_shared<Node>(key, value);
                    _cache.push_back(node);
                    _cacheMap[key] = node;
                }
                return true;
            }

            size_t size() const override {
                return _cacheMap.size();
            }

            bool resizeCapacity(size_t capacity) override {
                _capacity = capacity;
                while (_cache.size() > _capacity) {
                    while (_cache[_clockHand]->referenceBit) {
                        _cache[_clockHand]->referenceBit = false;
                        _clockHand = (_clockHand + 1) % _capacity;
                    }
                    _cacheMap.erase(_cache[_clockHand]->key);
                    _cache.erase(_cache.begin() + _clockHand);
                }
                return true;
            }

            void clear() override {
                _cache.clear();
                _cacheMap.clear();
                _clockHand = 0;
            }
        };

    } // namespace dsl
} // namespace rw