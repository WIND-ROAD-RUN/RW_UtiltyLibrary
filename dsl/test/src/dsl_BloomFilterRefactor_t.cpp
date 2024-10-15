#include"gtest/gtest.h"

#include"dsl_BloomFilterRefactor.h"

#include<iostream>

using namespace rw::dsl;

TEST(DSL, BLOOMFILTER_REFACTOR) {
    BloomFilterRefactor bf1(10,0.1);
    int i = 0;
    EXPECT_EQ(i, 0);
}
