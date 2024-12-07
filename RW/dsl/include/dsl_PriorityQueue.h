#ifndef DSL_PRIORITY_QUEUE_H
#define DSL_PRIORITY_QUEUE_H

#include "dsl_core.h"
#include <iostream>
#include <vector>
#include <stdexcept>

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
            virtual ~IPriorityQueue() = 0;

            IPriorityQueue(bool isHighPriorityFirst = true);

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
             *@warning: 
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
             *@warning:
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
        IPriorityQueue<T>::~IPriorityQueue() {}

        template <class T>
        IPriorityQueue<T>::IPriorityQueue(bool isHighPriorityFirst)
            : _isHighPriorityFirst(isHighPriorityFirst) {
        }

        class DHeap
            : public IPriorityQueue<int>
        {
        public:
            DHeap(size_t d = 2, bool isHighPriorityFirst = true);
            ~DHeap();
        public:
            int top() override;
            int peek() override;
            void insert(int element, size_t priority) override;
            void remove(int element) override;
            void update(int element, size_t priority) override;
            size_t size() override;

        private:
            void bubble_up(size_t index);
            void push_down(size_t index);
            size_t parent(size_t index) const;
            size_t child(size_t index, size_t k) const;
            bool compare(size_t a, size_t b) const;

        private:
            size_t _d;
            std::vector<std::pair<int, size_t>> _heap_array;
        };

        DHeap::DHeap(size_t d, bool isHighPriorityFirst)
            : IPriorityQueue<int>(isHighPriorityFirst), _d(d) {}

        DHeap::~DHeap() {}

        int DHeap::top() {
            if (_heap_array.empty()) {
                throw std::runtime_error("Heap is empty");
            }
            int top_element = _heap_array.front().first;
            std::swap(_heap_array.front(), _heap_array.back());
            _heap_array.pop_back();
            if (!_heap_array.empty()) {
                push_down(0);
            }
            return top_element;
        }

        int DHeap::peek() {
            if (_heap_array.empty()) {
                throw std::runtime_error("Heap is empty");
            }
            return _heap_array.front().first;
        }

        void DHeap::insert(int element, size_t priority) {
            _heap_array.emplace_back(element, priority);
            bubble_up(_heap_array.size() - 1);
        }

        void DHeap::remove(int element) {
            auto it = std::find_if(_heap_array.begin(), _heap_array.end(),
                [element](const std::pair<int, size_t>& p) { return p.first == element; });
            if (it != _heap_array.end()) {
                std::swap(*it, _heap_array.back());
                _heap_array.pop_back();
                if (it != _heap_array.end()) {
                    bubble_up(std::distance(_heap_array.begin(), it));
                    push_down(std::distance(_heap_array.begin(), it));
                }
            }
        }

        void DHeap::update(int element, size_t priority) {
            auto it = std::find_if(_heap_array.begin(), _heap_array.end(),
                [element](const std::pair<int, size_t>& p) { return p.first == element; });
            if (it != _heap_array.end()) {
                it->second = priority;
                bubble_up(std::distance(_heap_array.begin(), it));
                push_down(std::distance(_heap_array.begin(), it));
            }
        }

        size_t DHeap::size() {
            return _heap_array.size();
        }

        void DHeap::bubble_up(size_t index) {
            while (index > 0) {
                size_t p = parent(index);
                if (compare(index, p)) {
                    std::swap(_heap_array[index], _heap_array[p]);
                    index = p;
                }
                else {
                    break;
                }
            }
        }

        void DHeap::push_down(size_t index) {
            while (true) {
                size_t min_index = index;
                for (size_t k = 1; k <= _d; ++k) {
                    size_t c = child(index, k);
                    if (c < _heap_array.size() && compare(c, min_index)) {
                        min_index = c;
                    }
                }
                if (min_index != index) {
                    std::swap(_heap_array[index], _heap_array[min_index]);
                    index = min_index;
                }
                else {
                    break;
                }
            }
        }

        size_t DHeap::parent(size_t index) const {
            return (index - 1) / _d;
        }

        size_t DHeap::child(size_t index, size_t k) const {
            return _d * index + k;
        }

        bool DHeap::compare(size_t a, size_t b) const {
            if (_isHighPriorityFirst) {
                return _heap_array[a].second > _heap_array[b].second;
            }
            else {
                return _heap_array[a].second < _heap_array[b].second;
            }
        }

    }

}

#endif //DSL_PRIORITY_QUEUE_H