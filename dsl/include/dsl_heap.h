#ifndef DSL_HEAP_H
#define DSL_HEAP_H

#include"dsl_core.h"
#include<iostream>

namespace rw {
    namespace dsl {

        class Heap_element {
        public:
            Heap_element(int value);
            ~Heap_element();
        private:
            int _value;
        public:
            int get_value() const { return _value; }
            int set_value(int value) { _value = value; }
        public:
            void print() {
                std::cout << "value: " << _value << std::endl;
            }
        };

        class Heap_node {
        public:
            Heap_node(Shared_ptr<Heap_element> element,int n);
            Heap_node(Heap_element && element,int n);
            ~Heap_node(){}
        private:
            Shared_ptr<Heap_element> _element;
            int _n;
        private:
            Shared_ptr<Heap_node> _parent;
            Vector<Shared_ptr<Heap_node>> _children;
        public:
            Shared_ptr<Heap_node> lhs() const { return _children[0]; }
            Shared_ptr<Heap_node> rhs() const { return _children[1]; }

        public:
            Shared_ptr<Heap_element> get_element() const { return _element; }
            void set_element(Shared_ptr<Heap_element> element) { _element = element; }
            Shared_ptr<Heap_node> get_parent() const { return _parent; }
        public:
            void appendChild(Shared_ptr<Heap_node> child) { _children.push_back(child); }
        public:
            void print() {
                _element->print();
                std::cout << "chilren:" ;
                for (const auto & item : _children) {
                    item->get_element()->print();
                }

            }
        };
        
        class Heap {
        public:
            Heap(int n);
            ~Heap();
        private:
            int _n;
        private:
            Shared_ptr<Heap_node> _root;
        public:
            Shared_ptr<Heap_node> top() const;
            Shared_ptr<Heap_node> peek() const;
            void insert(Shared_ptr<Heap_element> element);
            void remove(Shared_ptr<Heap_element> element);

        };


    }

}


#endif