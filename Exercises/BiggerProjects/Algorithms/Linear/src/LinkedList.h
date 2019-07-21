#ifndef AISDI_LINEAR_LINKEDLIST_H
#define AISDI_LINEAR_LINKEDLIST_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <iostream>

using size_type = std::size_t;

namespace aisdi{

    template <typename Type>
    class LinkedList
    {
        private:
            class Node;
            using node = Node;
            //Size of the list
            size_type size;
            node *first;
            node *sentinel;


        public:
            using difference_type = std::ptrdiff_t;
            using value_type = Type;
            using pointer = Type*;
            using reference = Type&;
            using const_pointer = const Type*;
            using const_reference = const Type&;

            class ConstIterator;
            class Iterator;
            using iterator = Iterator;
            using const_iterator = ConstIterator;

            LinkedList(): size(0){
                sentinel = new Node();
                first = sentinel;
            }

            LinkedList(std::initializer_list<Type> l): LinkedList(){
                //Range-based loop /Access by const reference
                for(const Type& item : l)
                    append(item);
            }

            //Copy the list from other
            LinkedList(const LinkedList& other): LinkedList(){
                for(auto item = other.begin(); item != other.end(); item++)
                    append(*item);
            }

            //Move and delete other with function std::move
            LinkedList(LinkedList&& other): size(0), first(nullptr), sentinel(nullptr){
                *this = std::move(other);
            }

            //Delete the list
            ~LinkedList(){
                if(sentinel){
                    erase(cbegin(), cend());
                    delete sentinel;
                }
            }

            LinkedList& operator=(const LinkedList& other){
                //We have to make sure, that this list is empty
                if(this != &other){
                    erase(cbegin(), cend());
                    for(auto item = other.begin(); item != other.end(); item++)
                        append(*item);
                }
                return *this;
            }

            LinkedList& operator=(LinkedList&& other){
                //We have to make sure, that this list is empty
                if(this != &other){
                    //Check if the collection was even created
                    if(sentinel)
                        erase(cbegin(), cend());

                    //Move and delete
                    sentinel = other.sentinel;
                    first = other.first;
                    size = other.size;

                    other.sentinel = nullptr;
                    other.first = nullptr;
                    other.size = 0;
                }
                return *this;
            }

            //Is list empty?
            bool isEmpty() const{ return first == sentinel; }

            //Return size of the list
            size_type getSize() const{ return size; }

            //Add new node as the last
            void append(const Type& item){
                node *foo = new Node(item);

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

            //Add new node as first
            void prepend(const Type& item){
                node *foo = new Node(item);

                if(isEmpty()){
                    first = foo;
                    first->next = sentinel;
                    sentinel->prev = first;
                }
                else{
                    foo->next = first;
                    first->prev = foo;
                    first = foo;
                }
                size++;
            }

            //Add new node
            void insert(const const_iterator& insertPosition, const Type& item){
                if(insertPosition == cbegin()){
                    prepend(item);
                    return;
                }

                if(insertPosition == cend()){
                    append(item);
                    return;
                }

                node *bar = insertPosition.foo;
                node *prev = bar->prev;

                node *foo = new Node(item);
                prev->next = foo;
                foo->prev = prev;
                foo->next = bar;
                bar->prev = foo;
                size++;
            }

            Type popFirst(){
                //Check if empty
                if(isEmpty())
                    throw std::logic_error("Colection already empty");

                node *foo = first;
                first = foo->next;
                first->prev = first;

                Type data = *(foo->data);
                delete foo;

                size--;

                return data;
            }

            Type popLast(){
                //Check if empty
                if(isEmpty())
                    throw std::logic_error("Colection already empty");

                node *foo = sentinel->prev;
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

            void erase(const const_iterator& position){
                //While std::logic_error, it seemed to be wrong
                if(isEmpty())
                    throw std::out_of_range("Collection already empty");
                if(position == cend())
                    throw std::out_of_range("There is no valid node");
                if(position == cbegin()){
                    popFirst();
                    return;
                }
                if(position == --cend()){
                    popLast();
                    return;
                }

                node* bar = position.foo;
                bar->next->prev = bar->prev;
                bar->prev->next = bar->next;

                delete bar;
                size--;
            }

            void erase(const const_iterator& firstIncluded, const const_iterator& lastExcluded){
                //While std::logic_error, it seemed to be wrong
                if(firstIncluded.foo == lastExcluded.foo)
                    //throw std::out_of_range("There is nothing to be done");
                    return;

                node *foo = firstIncluded.foo;
                node *last = lastExcluded.foo;
                node *next;

                if(foo == first){
                    while(foo != last){
                        next = foo->next;
                        delete foo;
                        size--;
                        foo = next;
                    }

                    first = foo;
                    foo->prev = first;
                }
                else{
                    node *bar = foo->prev;

                    while(foo != last){
                        next = foo->next;
                        delete foo;
                        size--;
                        foo = next;
                    }

                    bar->next = last;
                    last->prev = bar;
                }

            }

            iterator begin(){ return iterator(first, sentinel, first); }

            iterator end(){ return iterator(sentinel, sentinel, first); }

            const_iterator cbegin() const{ return const_iterator(first, sentinel, first); }

            const_iterator cend() const{ return const_iterator(sentinel, sentinel, first); }

            const_iterator begin() const{ return cbegin(); }

            const_iterator end() const{ return cend(); }
    };

    template <typename Type>
    class LinkedList<Type>::Node
    {
        public:
            ///Maybe better if this data were in private?
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
    class LinkedList<Type>::ConstIterator
    {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type = typename LinkedList::value_type;
            using difference_type = typename LinkedList::difference_type;
            using pointer = typename LinkedList::const_pointer;
            using reference = typename LinkedList::const_reference;

            LinkedList<Type>::Node *foo;
            LinkedList<Type>::Node *sentinel;
            LinkedList<Type>::Node *first;

            explicit ConstIterator(LinkedList<Type>::Node *foo, LinkedList<Type>::Node *sentinel, LinkedList<Type>::Node *first)
            : foo(foo), sentinel(sentinel), first(first){}

            //Pointer to data in node
            reference operator*() const{
                if(foo == sentinel)
                    throw std::out_of_range("There is no valid node");

                return *(foo->data);
            }

            ConstIterator& operator++(){
                if(foo == sentinel)
                    throw std::out_of_range("The next node does not exist");

                foo = foo->next;
                return *this;
            }

            ConstIterator operator++(int){
                ConstIterator result(foo, sentinel, first);
                ++(*this);
                return result;
            }

            ConstIterator& operator--(){
                if(foo == first)
                    throw std::out_of_range("The previous node does not exist");

                foo = foo->prev;
                return *this;
            }

            ConstIterator operator--(int){
                ConstIterator result(foo, sentinel, first);
                --(*this);
                return result;
            }

            ConstIterator operator+(difference_type d) const{
                ConstIterator result(foo, sentinel, first);
                for(auto i = 0; i<d; i++)
                    ++result;
                return result;
            }

            ConstIterator operator-(difference_type d) const{
                ConstIterator result(foo, sentinel, first);
                for(auto i = 0; i<d; i++)
                    --result;
                return result;
            }

            bool operator==(const ConstIterator& other) const{ return this->foo == other.foo; }

            bool operator!=(const ConstIterator& other) const{ return !(*this == other); }
    };

    template <typename Type>
    class LinkedList<Type>::Iterator : public LinkedList<Type>::ConstIterator
    {
        public:
            using pointer = typename LinkedList::pointer;
            using reference = typename LinkedList::reference;

            explicit Iterator(LinkedList<Type>::Node *foo, LinkedList<Type>::Node *sentinel, LinkedList<Type>::Node *first)
            : ConstIterator(foo, sentinel, first){}

            Iterator(const ConstIterator& other): ConstIterator(other){}

            Iterator& operator++(){
                ConstIterator::operator++();
                return *this;
            }

            Iterator operator++(int){
                auto result = *this;
                ConstIterator::operator++();
                return result;
            }

            Iterator& operator--(){
                ConstIterator::operator--();
                return *this;
            }

            Iterator operator--(int){
                auto result = *this;
                ConstIterator::operator--();
                return result;
            }

            Iterator operator+(difference_type d) const{
                return ConstIterator::operator+(d);
            }

            Iterator operator-(difference_type d) const{
                return ConstIterator::operator-(d);
            }

            reference operator*() const{
                // ugly cast, yet reduces code duplication.
                return const_cast<reference>(ConstIterator::operator*());
            }
    };

}

#endif // AISDI_LINEAR_LINKEDLIST_H
