#pragma once

#include <functional>

//TODO:添加新的模板参数Priority
namespace rw {
    namespace dsl {
        template <class T,class Priority>
        class IPriorityQueue {
        public:
            using TCompareEqual = std::function<bool(const T&, const T&)>;
            using PriorityCompareEqual = std::function<bool(const Priority&, const Priority&)>;
            using PriorityCompare = std::function<bool(const Priority&, const Priority&)>;
            using PriorityCompareBigger = std::function<bool(const Priority&, const Priority&)>;
            using PriorityCompareSmaller = std::function<bool(const Priority&, const Priority&)>;

        protected:
            TCompareEqual _compareEqual{};
        public:
            virtual ~IPriorityQueue() {};

            IPriorityQueue(bool isHighPriorityFirst = true) 
                : _isHighPriorityFirst(isHighPriorityFirst) {}
        public:

            virtual T top() = 0;

            virtual T peek() = 0;

            virtual void insert(T element, T priority) = 0;

            virtual void remove(T element) = 0;

            virtual void update(T element, size_t priority) = 0;

            virtual size_t size() = 0;

        protected:
            bool _isHighPriorityFirst;
        public:
            bool getIsHighPriorityFirst() {
                return _isHighPriorityFirst;
            }
        
        };

    } // namespace dsl

} // namespace rw
