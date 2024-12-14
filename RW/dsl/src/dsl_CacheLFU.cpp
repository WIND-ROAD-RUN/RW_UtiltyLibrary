#include"dsl_CacheLFU.hpp"

std::optional<int> rw::dsl::CacheLFU_String_int::get(const std::string& key)
{
    auto it = _cache.find(key);
    if (it == _cache.end()) {
        return std::nullopt;
    }
    auto now = std::chrono::system_clock::now();
    it->second->counter = it->second->counter + 1;
    _heap.update(it->second, it->second->counter);
    it->second->timePoint = now;
    return it->second->value;
}

bool rw::dsl::CacheLFU_String_int::set(const std::string& key, const int& value)
{
    auto it = _cache.find(key);
    auto now = std::chrono::system_clock::now();
    if (it != _cache.end()) {
        it->second->value = value;
        it->second->counter = it->second->counter + 1;
        _heap.update(it->second, it->second->counter);
        it->second->timePoint = now;
        return false;
    }
    if (_cache.size() >= _capacity) {
        auto top = _heap.top();
        _cache.erase(top->key);
    }
    auto node = std::make_shared<PriorityNode>(key, value, 1, now);
    _cache[key] = node;
    _heap.insert(node, 1);
    return true;
}

size_t rw::dsl::CacheLFU_String_int::size() const
{
    return _cache.size();
}

bool rw::dsl::CacheLFU_String_int::resize(size_t capacity)
{    
    if (capacity < _capacity) {
        while (_cache.size() > capacity) {
            auto top = _heap.top();
            _cache.erase(top->key);
        }
    }
    _capacity = capacity;
    return true;
}
