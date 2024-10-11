#ifndef DSL_BLOOMFILTERREFACTOR_H_
#define DSL_BLOOMFILTERREFACTOR_H_

namespace rw {
    namespace dsl {
        class BloomFilterRefactor {
        public:
   /*         BloomFilterRefactor(int size, int numHashes);
            void add(const std::string& value);
            bool contains(const std::string& value) const;*/
            size_t hash(const std::string& item, size_t seed) const;
        private:
            /*std::vector<bool> m_bits;
            std::vector<std::function<int(const std::string&, int)>> m_hashFunctions;*/
        };
    }
}


#endif // !DSL_BLOOMFILTERREFACTOR_H_
