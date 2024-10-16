#ifndef DSL_BLOOMFILTERREFACTOR_H_
#define DSL_BLOOMFILTERREFACTOR_H_

#include<vector>
#include <cmath> 


namespace rw {
    namespace dsl {
        inline uint32_t MurmurHash3(const void* key, int len, uint32_t seed);
        inline uint32_t fnv1Hash(const std::string& str);

        class BloomFilterRefactor {
            const double ln2 = 0.6931471805599453;
            const double ln2Square = 0.4804530139182014;
        public:
            //parameter estimatedStorageSize: 预计插入元素的数量
            //parameter bloomFilter: 布隆过滤器的缓冲区位数,建议bloomfilterBitNum=size*5(当size*4.792=bloomFilterBitNum时有90%的精确度)
            explicit BloomFilterRefactor(size_t estimatedStorageSize);

            //parameter estimatedStorageSize: 预计插入元素的数量
            //parameter maxTolerance: 最大容忍的假阳性率（误判率） 
            //parameter estimatedStorageSize: 预计插入元素的数量,默认maxTolerance=0.01 也即误判率为1%
            
            explicit BloomFilterRefactor(size_t estimatedStorageSize, double maxTolerance=0.1);
        private:
            //公式为m=-n*ln(p)/(ln(2)^2),其中m为布隆过滤器的缓冲区位数，n为预计插入元素的数量，p为误判率
            inline size_t getBloomFilterBitNum(size_t estimatedStorageSize, double maxTolerance) {
                auto bloomFilterBitNum = -(estimatedStorageSize * log(maxTolerance) / (ln2Square));
                size_t size = std::ceil(bloomFilterBitNum);
                return size;
            }
        private:
            std::function<uint32_t(const std::string&)> murmurHash = [](const std::string& str) {
                return MurmurHash3(str.c_str(), str.size(), 0);
                };

            std::function<uint32_t(const std::string&)> fnv1Hash = [this](const std::string& str) {
                return fnv1Hash(str);
                };

            void iniHashFunctions(size_t numHashFunctions,size_t numBits);

        private:
            std::vector<bool> _bloomFilterbuffer;

            size_t _estimatedStorageSize;

            double _maxTolerance;

            std::vector<std::function<size_t(const std::string&)>> _hashFunctions;

        
        };

        inline uint32_t MurmurHash3(const void* key, int len, uint32_t seed)
        {
            const uint8_t* data = (const uint8_t*)key;
            const int nblocks = len / 4;
            uint32_t h1 = seed;

            const uint32_t c1 = 0xcc9e2d51;
            const uint32_t c2 = 0x1b873593;

            // Body
            const uint32_t* blocks = (const uint32_t*)(data + nblocks * 4);
            for (int i = -nblocks; i; i++) {
                uint32_t k1 = blocks[i];

                k1 *= c1;
                k1 = (k1 << 15) | (k1 >> (32 - 15));
                k1 *= c2;

                h1 ^= k1;
                h1 = (h1 << 13) | (h1 >> (32 - 13));
                h1 = h1 * 5 + 0xe6546b64;
            }

            // Tail
            const uint8_t* tail = (const uint8_t*)(data + nblocks * 4);
            uint32_t k1 = 0;

            switch (len & 3) {
            case 3: k1 ^= tail[2] << 16;
            case 2: k1 ^= tail[1] << 8;
            case 1: k1 ^= tail[0];
                k1 *= c1; k1 = (k1 << 15) | (k1 >> (32 - 15)); k1 *= c2; h1 ^= k1;
            };

            // Finalization
            h1 ^= len;
            h1 ^= h1 >> 16;
            h1 *= 0x85ebca6b;
            h1 ^= h1 >> 13;
            h1 *= 0xc2b2ae35;
            h1 ^= h1 >> 16;

            return h1;
        }

        inline uint32_t fnv1Hash(const std::string& str) {
            const uint32_t fnv_prime = 16777619;
            uint32_t hash = 2166136261;

            for (char c : str) {
                hash *= fnv_prime;
                hash ^= c;
            }

            return hash;
        }

    }
}


#endif // !DSL_BLOOMFILTERREFACTOR_H_
