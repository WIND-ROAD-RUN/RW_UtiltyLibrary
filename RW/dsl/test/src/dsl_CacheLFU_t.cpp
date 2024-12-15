#include"dsl_CacheLFU_t.hpp"
#include"dsl_PriorityQueue.hpp"

#include<unordered_map>
#include<vector>

int generateRandomNumber(int min, int max) {
    std::random_device rd; // 用于生成种子
    std::mt19937 gen(rd()); // Mersenne Twister 19937 生成器
    std::uniform_int_distribution<> dis(min, max); // 均匀分布
    return dis(gen);
}

namespace dsl_cache {
    TEST(CacheLFU,akwjd) {
        rw::dsl::CacheLFU_String_int cache(3);
        cache.set("a", 4);
        cache.set("a", 4);
        cache.set("a", 4);
        cache.set("a", 4);
        cache.set("b", 3);
        cache.set("b", 3);
        cache.set("b", 3);
        cache.set("c", 2);
        cache.set("c", 2);
        cache.set("c", 2);
        cache.set("d", 1);
        cache.set("e", 3);
        cache.set("e", 3);
        cache.set("e", 3);
    }

    TEST(CacheLFU,awd) {
        rw::dsl::CacheLFU<std::string, int> cache(3);

        cache.set("a", 4);
        cache.set("a", 4);
        cache.set("a", 4);
        cache.set("a", 4);
        cache.set("b", 3);
        cache.set("b", 3);
        cache.set("b", 3);
        cache.set("c", 2);
        cache.set("c", 2);
        cache.set("c", 2);
        cache.set("d", 1);
        cache.set("e", 3);
        cache.set("e", 3);
        cache.set("e", 3);
    
    }
}