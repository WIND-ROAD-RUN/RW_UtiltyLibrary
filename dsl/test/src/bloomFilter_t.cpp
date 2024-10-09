#include"gtest/gtest.h"

#include"dsl_BloomFilter.h"

TEST(DSL,BLOOMFILTER) {
    BloomFilter bf(100, 3);
    bf.add("hello");
    bf.add("world");
    ASSERT_TRUE(bf.possiblyContains("122"));
}