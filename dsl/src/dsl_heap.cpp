#include"dsl_heap.h"

namespace rw {
    namespace dsl {
        Heap_element::Heap_element(int value) 
            :_value(value) {

        }

        Heap_element::~Heap_element()
        {

        }

        Heap_node::Heap_node(Shared_ptr<Heap_element> element,int n)
            :_element(element), _n(n) 
        {
        }

        Heap_node::Heap_node(Heap_element&& element, int n)
            :_element(make_shared<Heap_element>(element)), _n(n)
        {

        }

        Heap::Heap(int n) 
            :_n(n)
        {

        }

        Heap::~Heap()
        {

        }

    }

}