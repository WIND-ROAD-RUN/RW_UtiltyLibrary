#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <vector>
#include <functional>
#include<string>
 
class BloomFilter {
public:
    BloomFilter(size_t size, size_t numHashes);
    void add(const std::string& item);
    bool possiblyContains(const std::string& item) const;

private:
    size_t hash(const std::string& item, size_t seed) const;

    std::vector<bool> bitArray;
    size_t numHashes;
};

#endif // BLOOM_FILTER_H