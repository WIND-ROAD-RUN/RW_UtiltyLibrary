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
            //Calculate the number of buffer bits for the Bloom filter and initialize the buffer
            auto size = getBloomFilterBitNum(estimatedStorageSize, _maxTolerance);
            size *= 1.3;//Increase the buffer size by 30% to reduce the false positive rate
            _bloomFilterbuffer.resize(size, false);

            //Calculate the number of hash functions and initialize the hash functions
            auto maxHashFunctions = static_cast<double>(size) / static_cast<double>(estimatedStorageSize) * (ln2);
            _maxHashFunctions = static_cast<size_t>(maxHashFunctions);
            iniHashFunctions(_maxHashFunctions, size);
        }

        void BloomFilter::iniHashFunctions(size_t numHashFunctions, size_t numBits)
        {
            //Initialize the hash function set using the formula 
            // hi (key)=murmurmHash (key)+i * fnv1Hash (key)+i ^ 2% numBits
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