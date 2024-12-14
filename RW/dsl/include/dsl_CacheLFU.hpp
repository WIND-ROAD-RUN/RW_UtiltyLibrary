#pragma once

#include"dsl_Cache.hpp"

#include"dsl_PriorityQueue.hpp"

#include<list>
#include<unordered_map>
#include <chrono>

namespace rw {
    namespace dsl {
        template <typename Key, typename Value>
        class CacheLFU
            :public ICache<Key, Value> {
            MAKE_FRIEND_TEST_CLASS(CacheLRU_Test)
        private:
            using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
            using Counter = size_t;
            using Pripority = std::pair<Counter, TimePoint>;
            using PriorityNode = std::pair<typename ICache<Key, Value>::CacheNode, typename Pripority>;
        public:
            explicit CacheLFU(size_t capacity)
                : ICache<Key, Value>(capacity), 
                _heap(4, true, [](const std::pair<Key, Value> & a, const std::pair<Key, Value>& b) {
                if (a.first==b.first) {
                    if (a.second == b.second) {
                        return true;
                    }
                }
                return false;
                    }) 
            {

            }

            std::optional<Value> get(const Key& key) override {
                auto it = _cache.find(key);
                if (it == _cache.end()) {
                    return std::nullopt;
                }
                return std::nullopt;
            }

            bool set(const Key& key, const Value& value) override {
                auto it = _cache.find(key);
                auto now = std::chrono::system_clock::now();
                if (it != _cache.end()) {
                    it->second->first.second = value;
                    _heap.update(*(it->second),it->second->second.first + 1);
                    return false;
                }

                if (_cache.size() >= this->_capacity) {
                    auto top = _heap.top();
                    _cache.erase(top.first.key);
                }

                auto node = new PriorityNode({ key, value }, { 1, now });
                _cache[key] = node;
                _heap.insert(*node, { 1, now });
                return true;
            }

            size_t size() const override {
                return 0;
            }

            bool resize(size_t capacity) {
                return false;
            }
        private:
            std::unordered_map<Key, PriorityNode*> _cache;
            DHeap<PriorityNode> _heap;
        };
        
        class CacheLFU_String_int 
            : public ICache<std::string, int> {
        private:
            using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
            using Counter = size_t;
            using Pripority = std::pair<Counter, TimePoint>;
            struct PriorityNode {
                std::string key;
                int value;
                Counter counter;
                TimePoint timePoint;
                PriorityNode(std::string key, int value, Counter counter, TimePoint timePoint)
                    : key(key), value(value), counter(counter), timePoint(timePoint) {
                }
            };
        public:
            explicit CacheLFU_String_int(size_t capacity)
                : ICache<std::string, int>(capacity),
                _heap(4, false, [](const std::shared_ptr<PriorityNode>& a, const std::shared_ptr<PriorityNode>& b) {
                if (a->key == b->key) {
                    if (a->value == b->value) {
                        return true;
                    }
                }
                return false;
                    }) {
            }

        public:
            // 通过 ICache 继承
            std::optional<int> get(const std::string& key) override;

            bool set(const std::string& key, const int& value) override;

            size_t size() const override;

            bool resize(size_t capacity) override;

        private:
            std::unordered_map<std::string, std::shared_ptr<PriorityNode> > _cache;
            DHeap<std::shared_ptr<PriorityNode>> _heap;
        
        };

    } // namespace dsl

} // namespace rw
