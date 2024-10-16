#include<iostream>

#include"dsl_BloomFilterRefactor.h"

using namespace rw::dsl;
int main() {
    auto a = fnv1Hash("13");
    std::cout << a << std::endl;
    return 0;
}