#ifndef DSL_PRIORITY_QUEUE_H
#define DSL_PRIORITY_QUEUE_H

#include "dsl_core.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <functional>

namespace rw
{
    namespace dsl
    {
        const bool HighPriorityFirst = true;
        const bool LowPriorityFirst = false;

        /**
         * @brief: Priority Queue Interface
         *
         * @template variable:
         *   - T: The type of the elements in the priority queue
         *
         * @details: Detailed description of the template class
         *
         */
        template <class T>
        class IPriorityQueue
        {
        public:


            /**
             *@Parameters:
             *  -a: The first element to be compared
             *  -b: The second element to be compared
             *@Methods:
             * Compare two elements to determine whether they are equal
             *@Returns: bool
             * If the two elements are equal, return true, otherwise return false
             *@Throws:
             *
             */
            using CompareEqual = std::function<bool(const T&, const T&)>;
        public:
            virtual ~IPriorityQueue() {};

            /**
             *@Parameters:
             *  1. bool isHighPriorityFirst: The priority queue is a high priority first queue or a low priority first queue
             *  2. CompareEqual compareEqual: The function to compare two elements
             *@Methods:
             *  Constructor
             *@Returns: void
             *@Throws: void
             */
            IPriorityQueue(bool isHighPriorityFirst = true,
                CompareEqual compareEqual = [](const T& a, const T& b) {
                    return a == b;
                })
                : _isHighPriorityFirst(isHighPriorityFirst), _compareEqual(compareEqual) {
            }
        protected:
            CompareEqual _compareEqual;

        public:

            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Get the top element of the priority queue and remove it
             *@Returns: template variable T
             *  The top element of the priority queue
             *@Throws:
             *  1. std::runtime_error: If the priority queue is empty
             */
            virtual T top() = 0;

            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Get the top element of the priority queue without removing it
             *@Returns: template variable T
             *  The top element of the priority queue
             *@Throws:
             *  1. std::runtime_error: If the priority queue is empty
             */
            virtual T peek() = 0;

            /**
             *@Parameters:
             *  1. T element: The element to be inserted
             *  2. size_t priority: The priority of the element
             *@Methods:
             *  Insert an element into the priority queue with a priority
             *@Returns: void
             *@Throws: void
             *@Warning:
             *  1.If the insert element 's value is the same as the existing element, the new element will be inserted as a new element
             *  2.If some elements have the same priority, the order of the elements is not guaranteed
             */
            virtual void insert(T element, size_t priority) = 0;

            /**
             *@Parameters:
             *  1. T element: The element to be removed
             *@Methods:
             *  Remove an element from the priority queue
             *@Returns: void
             *@Throws: void
             *@Warning:
             * 1. If the element is not in the priority queue, the method will do nothing
             * 2. If some elements in the priority queue have the same value,the element to be removed is not guaranteed
             */
            virtual void remove(T element) = 0;

            /**
             *@Parameters:
             *  1. T element: The element to be updated
             *  2. size_t priority: The new priority of the element
             *@Methods:
             *  Update the priority of an element in the priority queue
             *@Returns: void
             *@Throws: void
             *@Warning:
             * 1. If the element is not in the priority queue, the method will do nothing
             * 2. If some elements in the priority queue have the same value,the element to be updated is not guaranteed
             */
            virtual void update(T element, size_t priority) = 0;

            /**
             *@Parameters:
             *  void
             *@Methods:
             *  Get the size of the priority queue
             *@Returns: size_t
             *  The size of the priority queue
             *@Throws: void
             */
            virtual size_t size() = 0;

        protected:
            bool _isHighPriorityFirst;
        public:
            bool getIsHighPriorityFirst() {
                return _isHighPriorityFirst;
            }
        };

        template <class T>
        class DHeap
            : public IPriorityQueue<T>
        {
        public:
            /**
             *@Parameters:
             *  -d: The number of children of each node 
             *     note: According to test,when d=4 or d=5, the performance of the heap is better
             *  -isHighPriorityFirst: The priority queue is a high priority first queue or a low priority first queue
             *@Methods:
             *  Constructor
             *@Returns: void
             *
             *@Throws:
             *
             */
            DHeap(size_t d = 4, bool isHighPriorityFirst = true);
            DHeap(size_t d, bool isHighPriorityFirst, CompareEqual compareEqual);
            ~DHeap();
        public:
            T top() override;
            T peek() override;
            void insert(T element, size_t priority) override;
            void remove(T element) override;
            void update(T element, size_t priority) override;
            size_t size() override;

        private:
            void bubble_up(size_t index);
            void push_down(size_t index);
            size_t parent(size_t index) const;
            size_t child(size_t index, size_t k) const;
            bool compare(size_t a, size_t b) const;

        private:
            size_t _d;
            std::vector<std::pair<T, size_t>> _heap_array;
        };

        template <class T>
        DHeap<T>::DHeap(size_t d, bool isHighPriorityFirst)
            : IPriorityQueue<T>(isHighPriorityFirst), _d(d) {}

        template<class T>
        DHeap<T>::DHeap(size_t d, bool isHighPriorityFirst, CompareEqual compareEqual)
            : IPriorityQueue<T>(isHighPriorityFirst, compareEqual), _d(d)
        {
        }

        template <class T>
        DHeap<T>::~DHeap() {}

        template <class T>
        T DHeap<T>::top() {
            if (this->_heap_array.empty()) {
                throw std::runtime_error("Heap is empty");
            }
            T top_element = this->_heap_array.front().first;
            std::swap(this->_heap_array.front(), this->_heap_array.back());
            this->_heap_array.pop_back();
            if (!this->_heap_array.empty()) {
                push_down(0);
            }
            return top_element;
        }

        template <class T>
        T DHeap<T>::peek() {
            if (this->_heap_array.empty()) {
                throw std::runtime_error("Heap is empty");
            }
            return this->_heap_array.front().first;
        }

        template <class T>
        void DHeap<T>::insert(T element, size_t priority) {
            this->_heap_array.emplace_back(element, priority);
            bubble_up(this->_heap_array.size() - 1);
        }

        template <class T>
        void DHeap<T>::remove(T element) {
            auto it = std::find_if(this->_heap_array.begin(), this->_heap_array.end(),
                [element, this](const std::pair<T, size_t>& p) { return  _compareEqual(p.first, element); });
            if (it != this->_heap_array.end()) {
                std::swap(*it, this->_heap_array.back());
                this->_heap_array.pop_back();
                if (it != this->_heap_array.end()) {
                    bubble_up(std::distance(this->_heap_array.begin(), it));
                    push_down(std::distance(this->_heap_array.begin(), it));
                }
            }
        }

        template <class T>
        void DHeap<T>::update(T element, size_t priority) {
            auto it = std::find_if(this->_heap_array.begin(), this->_heap_array.end(),
                [element, this](const std::pair<T, size_t>& p) { return  _compareEqual(p.first, element); });
            if (it != this->_heap_array.end()) {
                it->second = priority;
                bubble_up(std::distance(this->_heap_array.begin(), it));
                push_down(std::distance(this->_heap_array.begin(), it));
            }
        }

        template <class T>
        size_t DHeap<T>::size() {
            return this->_heap_array.size();
        }

        template <class T>
        void DHeap<T>::bubble_up(size_t index) {
            while (index > 0) {
                size_t p = parent(index);
                if (compare(index, p)) {
                    std::swap(this->_heap_array[index], this->_heap_array[p]);
                    index = p;
                }
                else {
                    break;
                }
            }
        }

        template <class T>
        void DHeap<T>::push_down(size_t index) {
            while (true) {
                size_t min_index = index;
                for (size_t k = 1; k <= _d; ++k) {
                    size_t c = child(index, k);
                    if (c < this->_heap_array.size() && compare(c, min_index)) {
                        min_index = c;
                    }
                }
                if (min_index != index) {
                    std::swap(this->_heap_array[index], this->_heap_array[min_index]);
                    index = min_index;
                }
                else {
                    break;
                }
            }
        }

        template <class T>
        size_t DHeap<T>::parent(size_t index) const {
            return (index - 1) / _d;
        }

        template <class T>
        size_t DHeap<T>::child(size_t index, size_t k) const {
            return _d * index + k;
        }

        template <class T>
        bool DHeap<T>::compare(size_t a, size_t b) const {
            if (this->_isHighPriorityFirst) {
                return this->_heap_array[a].second > this->_heap_array[b].second;
            }
            else {
                return this->_heap_array[a].second < this->_heap_array[b].second;
            }
        }

    }

}

#endif //DSL_PRIORITY_QUEUE_H