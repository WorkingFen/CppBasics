
#pragma once

#include <stdexcept>
#include <iostream>

namespace List {

    template <typename Type>
    class MyList
    {
        private:
            class Node;
            Node* first;
            Node* sentinel;
            int size;

        public:
            MyList() :size(0){
                sentinel = new Node();
                first = sentinel;
            }

            bool isEmpty() const{ return first == sentinel; }

            int size() const{ return size; }

            void push_back(const Type& item){
                Node *foo = new Node(item);

                if(isEmpty())
                    first = foo;
                else{
                    sentinel->prev->next = foo;
                    foo->prev = sentinel->prev;
                }

                foo->next = sentinel;
                sentinel->prev = foo;

                size++;
            }

            Type pop_front(){
                if(isEmpty())
                    throw std::logic_error("Colection already empty");

                Node *foo = first;
                first = foo->next;
                first->prev = first;

                Type data = *(foo->data);
                delete foo;

                size--;

                return data;
            }

            Type pop_back(){
                if(isEmpty())
                    throw std::logic_error("Colection already empty");

                Node *foo = sentinel->prev;
                foo->prev->next = sentinel;
                if(sentinel->prev == first){
                    sentinel->prev = sentinel;
                    first = sentinel;
                }
                else
                    sentinel->prev = foo->prev;

                Type data = *(foo->data);
                delete foo;

                size--;

                return data;
            }

            iterator end(){ return iterator(sentinel, sentinel, first); }
    };

    template <typename Type>
    class MyList<Type>::Node
    {
        public:
            Node *prev;
            Node *next;
            Type *data;
            char *dm;

            Node(){                                                 //Deafult constructor with default values
                prev = this;
                next = this;
                data = nullptr;
                dm = nullptr;
            }

            Node(const Type &item): Node(){                         //Constructor with item, as in append function of the list
                dm = new char[sizeof(Type)];                        //Allocate memory
                data = new(dm) Type(item);                          //New data in memory which was allocated before "dm": Placement new
            }

            ~Node(){                                                //Destructor
                if(dm != nullptr){
                    data->~Type();                                      //Delete data
                    delete[] dm;                                        //Deallocate memory
                }
            }
    };

    template <typename Type>
    class MyList<Type>::Iterator
    {
        public:
            MyList<Type>::Node *foo;
            MyList<Type>::Node *sentinel;
            MyList<Type>::Node *first;

            explicit Iterator(LinkedList<Type>::Node *foo, LinkedList<Type>::Node *sentinel, LinkedList<Type>::Node *first)
            : foo(foo), sentinel(sentinel), first(first){}
    };
}
