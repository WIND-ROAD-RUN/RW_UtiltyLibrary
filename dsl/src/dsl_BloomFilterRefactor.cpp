#include"dsl_BloomFilter.h"
#include "dsl_BloomFilterRefactor.h"

#include <functional>
#include <cmath> 
namespace rw
{
    namespace dsl {
        BloomFilterRefactor::BloomFilterRefactor
        (size_t estimatedStorageSize)
            : _estimatedStorageSize(estimatedStorageSize)
        {
            _maxTolerance = 0.1;
            auto size = getBloomFilterBitNum(estimatedStorageSize, _maxTolerance);
            _bloomFilterbuffer.resize(size, false);
        }

        BloomFilterRefactor::BloomFilterRefactor
        (size_t estimatedStorageSize, double maxTolerance)
            :_estimatedStorageSize(estimatedStorageSize), _maxTolerance(maxTolerance)
        {
            auto size = getBloomFilterBitNum(estimatedStorageSize, _maxTolerance);
            _bloomFilterbuffer.resize(size, false);
        }
    }
}