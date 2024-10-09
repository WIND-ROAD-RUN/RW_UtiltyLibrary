#include "dsl_BloomFilter.h"
#include <string>

BloomFilter::BloomFilter(size_t size, size_t numHashes)
    : bitArray(size), numHashes(numHashes) {}

void BloomFilter::add(const std::string& item) {
    for (size_t i = 0; i < numHashes; ++i) {
        bitArray[hash(item, i) % bitArray.size()] = true;
    }
}

bool BloomFilter::possiblyContains(const std::string& item) const {
    for (size_t i = 0; i < numHashes; ++i) {
        if (!bitArray[hash(item, i) % bitArray.size()]) {
            return false;
        }
    }
    return true;
}

size_t BloomFilter::hash(const std::string& item, size_t seed) const {
    std::hash<std::string> hasher;
    return hasher(item) + seed;
}