#ifndef DSL_HEAP_H
#define DSL_HEAP_H

#include "dsl_core.h"
#include <iostream>
#include <vector>

namespace rw
{
    namespace dsl
    {

        template <class T>
        class IPriorityQueue
        {
        public:
            virtual ~IPriorityQueue() = 0;

        public:
            virtual T top() = 0;
            virtual T peek() = 0;
            virtual void insert(T element, size_t priority) = 0;
            virtual void remove(T element) = 0;
            virtual void update(T element, size_t priority) = 0;
            virtual size_t size() = 0;
        };

        class DHeap
            : public IPriorityQueue<int>
        {
        public:
            DHeap();
            ~DHeap();
        public:
            int top() override;
            int peek() override;
            void insert(int element, size_t priority) override;
            void remove(int element) override;
            void update(int element, size_t priority) override;
            size_t size() override;

        public:
            std::vector<size_t> heap_arrary;
        private:
            void bubble_up(size_t index);
            void push_down(size_t index);
            void insert();
            
        };

    }

}

#endif