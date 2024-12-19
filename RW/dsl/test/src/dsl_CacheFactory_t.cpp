#include"dsl_CacheFactory_t.hpp"

namespace dsl_cache {

    TEST_P(CacheFactoryTest, createCache) {
        auto& [policy] = GetParam();
        auto cache = rw::dsl::CacheFactory::createCache<int, int>(policy, 10);
        ASSERT_TRUE(cache);
    }


   
}