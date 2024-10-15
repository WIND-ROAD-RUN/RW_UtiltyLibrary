#ifndef DSL_BLOOMFILTERREFACTOR_H_
#define DSL_BLOOMFILTERREFACTOR_H_

#include<vector>
#include <cmath> 

namespace rw {
    namespace dsl {
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
        public:

        private:
            std::vector<bool> _bloomFilterbuffer;

            size_t _estimatedStorageSize;

            double _maxTolerance;
        
        };
    }
}


#endif // !DSL_BLOOMFILTERREFACTOR_H_
