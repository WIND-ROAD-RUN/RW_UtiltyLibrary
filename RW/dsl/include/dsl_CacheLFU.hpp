#pragma once

#include"dsl_Cache.hpp"

#include"dsl_PriorityQueue.hpp"

#include<list>
#include<unordered_map>
#include <chrono>

namespace rw {
    namespace dsl {    
        //TODO:实现LFU缓存 当前实现有问题
        template <typename Key, typename Value>
        class CacheLFU : public ICache<Key, Value> {
        private:
            using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
            using Counter = size_t;
            using Priority = std::pair<Counter, TimePoint>;
            struct PriorityNode {
                Key key;
                Value value;
                Counter counter;
                TimePoint timePoint;
                PriorityNode(Key key, Value value, Counter counter, TimePoint timePoint)
                    : key(key), value(value), counter(counter), timePoint(timePoint) {
                }
            };
        public:
            explicit CacheLFU(size_t capacity)
                : ICache<Key, Value>(capacity),
                _heap(4, false, [](const std::shared_ptr<PriorityNode>& a, const std::shared_ptr<PriorityNode>& b) {
                if (a->counter == b->counter) {
                    return a->timePoint < b->timePoint;
                }
                return a->counter < b->counter;
                    }) {
            }

        public:
            // 通过 ICache 继承
            std::optional<Value> get(const Key& key) override {
                auto it = _cache.find(key);
                if (it == _cache.end()) {
                    return std::nullopt;
                }
                auto now = std::chrono::system_clock::now();
                it->second->counter++;
                it->second->timePoint = now;
                _heap.update(it->second, it->second->counter);
                return it->second->value;
            }

            bool set(const Key& key, const Value& value) override {
                auto it = _cache.find(key);
                auto now = std::chrono::system_clock::now();
                if (it != _cache.end()) {
                    it->second->value = value;
                    it->second->counter++;
                    it->second->timePoint = now;
                    _heap.update(it->second, it->second->counter);
                    return false;
                }
                if (_cache.size() >= this->_capacity) {
                    auto top = _heap.top();
                    _cache.erase(top->key);
                    _heap.remove(top);
                }
                auto node = std::make_shared<PriorityNode>(key, value, 1, now);
                _cache[key] = node;
                _heap.insert(node, 1);
                return true;
            }

            size_t size() const override {
                return _cache.size();
            }

            bool resize(size_t capacity) override {
                if (capacity < this->_capacity) {
                    while (_cache.size() > capacity) {
                        auto top = _heap.top();
                        _cache.erase(top->key);
                        _heap.remove(top);
                    }
                }
                this->_capacity = capacity;
                return true;
            }

        private:
            std::unordered_map<Key, std::shared_ptr<PriorityNode>> _cache;
            DHeap<std::shared_ptr<PriorityNode>> _heap;
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
