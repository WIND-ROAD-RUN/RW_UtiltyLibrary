#include "dsl_BloomFilter.h"

#include <functional>
#include <cmath> 
namespace rw
{
    namespace dsl {
        BloomFilter::BloomFilter
        (size_t estimatedStorageSize, double maxTolerance)
            :_estimatedStorageSize(estimatedStorageSize), _maxTolerance(maxTolerance)
        {
            auto size = getBloomFilterBitNum(estimatedStorageSize, _maxTolerance);
            _bloomFilterbuffer.resize(size, false);
            _maxHashFunctions = static_cast<double>(size) / static_cast<double>(estimatedStorageSize) * (ln2);
            iniHashFunctions(_maxHashFunctions, size);
        }

        void BloomFilter::iniHashFunctions(size_t numHashFunctions, size_t numBits)
        {
            for (size_t i = 0; i < numHashFunctions;++i) {
                _hashFunctions.push_back([numBits, i, this](const std::string& str) {
                    uint32_t hash1 = murmurHash(str.c_str());
                    uint32_t hash2 = fnv1Hash(str);

                    return (hash1 + i * hash2 + i * i) % numBits;
                    });
            }
        }

        void BloomFilter::insert(const std::string& key)
        {
            for (auto& hashFunction : _hashFunctions) {
                auto index = hashFunction(key);
                _bloomFilterbuffer[index] = true;
            }
        }

        bool BloomFilter::contains(const std::string& key)
        {
            for (auto& hashFunction : _hashFunctions) {
                auto index = hashFunction(key);
                if (!_bloomFilterbuffer[index]) {
                    return false;
                }
            }
            return true;
        }
    }
}