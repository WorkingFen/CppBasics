#ifndef AISDI_LINEAR_VECTOR_H
#define AISDI_LINEAR_VECTOR_H

#define INIT_SIZE 32 // Number in binary numeral system

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace aisdi{

    template <typename Type>
    class Vector
    {
        private:
            size_t size;
            size_t vector_capacity;
            char* dm;
            Type* vector_begin;
            Type* follow_on;

        public:
            using difference_type = std::ptrdiff_t;
            using size_type = std::size_t;
            using value_type = Type;
            using pointer = Type*;
            using reference = Type&;
            using const_pointer = const Type*;
            using const_reference = const Type&;

            class ConstIterator;
            class Iterator;
            using iterator = Iterator;
            using const_iterator = ConstIterator;

            Vector():Vector(INIT_SIZE){}

            Vector(size_t capacity): size(0), vector_capacity(capacity){
                dm = new char[sizeof(Type)*(vector_capacity+1)];                    //Allocate memory
                vector_begin = reinterpret_cast<Type*>(dm);                       //Memory should have been cast as Type
                follow_on = vector_begin;
            }

            //We should make sure that the initialized size is enough
            Vector(std::initializer_list<Type> l): Vector(checkCapacity(l.size())){
                for(const Type& item : l)                                         //Range-based loop
                    append(item);
            }

            //Copy the vector from other
            Vector(const Vector& other): Vector(checkCapacity(other.size)){
                for(auto item = other.begin(); item != other.end(); item++)
                    append(*item);
            }

            //Move and delete other with function std::move
            Vector(Vector&& other)
            : size(0), vector_capacity(0), dm(nullptr), vector_begin(nullptr), follow_on(nullptr){
                *this = std::move(other);
            }

            //Delete the vector
            ~Vector(){
                if(dm){
                    erase(cbegin(), cend());
                    delete[] dm;
                }
            }

            Vector& operator=(const Vector& other){
                //We have to make sure, that this list is empty
                if(this != &other){
                    erase(cbegin(), cend());
                    for(auto item = other.begin(); item != other.end(); item++)
                        append(*item);
                }
                return *this;
            }

            Vector& operator=(Vector&& other){
                //We have to make sure, that this list is empty
                if(this != &other){
                    if(dm){
                        erase(cbegin(), cend());
                        delete[] dm;
                    }

                    //Move and delete
                    size = other.size;
                    vector_capacity = other.vector_capacity;
                    dm = other.dm;
                    vector_begin = other.vector_begin;
                    follow_on = other.follow_on;

                    other.size = 0;
                    other.vector_capacity = 0;
                    other.dm = nullptr;
                    other.vector_begin = nullptr;
                    other.follow_on = nullptr;
                }
                return *this;
            }

            //Is vector empty?
            bool isEmpty() const{ return vector_begin == follow_on; }

            //Return size of the vector
            size_type getSize() const{ return size; }

            void append(const Type& item){
                if(size == vector_capacity)
                    increaseSize(size+1);                               //Anyway, it would be bigger than +1
                new (follow_on) Type(item);                             //Placement new of course
                ++follow_on;
                ++size;
            }

            void prepend(const Type& item){
                if(isEmpty()){
                    append(item);
                    return;
                }

                if(size == vector_capacity)
                    increaseSize(size+1);

                Type* foo = follow_on;
                Type* bar = follow_on-1;

                while(bar != vector_begin){
                    new(foo) Type(*bar);
                    bar->~Type();
                    --foo;
                    --bar;
                }
                new(foo) Type(*bar);
                bar->~Type();

                new(vector_begin) Type(item);
                ++follow_on;
                ++size;
            }

            void insert(const const_iterator& insertPosition, const Type& item){
                if(insertPosition == cbegin()){
                    prepend(item);
                    return;
                }

                if(insertPosition == cend()){
                    append(item);
                    return;
                }

                if(size == vector_capacity)
                    increaseSize(size+1);

                Type* foo = follow_on;
                Type* bar = follow_on-1;

                while(bar != insertPosition.foo){
                    new(foo) Type(*bar);
                    bar->~Type();
                    --foo;
                    --bar;
                }
                new(foo) Type(*bar);
                bar->~Type();

                new(insertPosition.foo) Type(item);
                ++follow_on;
                ++size;

            }

            Type popFirst(){
                //Check if empty
                if(isEmpty())
                    throw std::logic_error("Colection already empty");

                Type poped = *vector_begin;
                vector_begin->~Type();
                Type* foo = vector_begin;
                Type* bar = vector_begin+1;

                while(bar != follow_on){
                    new(foo) Type(*bar);
                    bar->~Type();
                    ++foo;
                    ++bar;
                }
                --follow_on;
                --size;
                return poped;
            }

            Type popLast(){
                //Check if empty
                if(isEmpty())
                    throw std::logic_error("Colection already empty");

                Type foo = *(follow_on-1);
                (follow_on-1)->~Type();
                --follow_on;
                --size;
                return foo;
            }

            void erase(const const_iterator& position){
                //While std::logic_error, it seemed to be wrong
                if(isEmpty())
                    throw std::out_of_range("Collection already empty");
                if(position == cend())
                    throw std::out_of_range("There is no valid element");

                position.foo->~Type();

                Type* foo = position.foo;
                Type* bar = position.foo + 1;

                while(bar != follow_on){
                    new(foo) Type(*bar);
                    bar->~Type();
                    ++foo;
                    ++bar;
                }
                --follow_on;
                --size;
            }

            void erase(const const_iterator& firstIncluded, const const_iterator& lastExcluded){
                //While std::logic_error, it seemed to be wrong
                /*if(isEmpty())
                    throw std::out_of_range("Collection already empty");*/
                if(firstIncluded.foo == lastExcluded.foo)
                    //throw std::out_of_range("There is nothing to be done");
                    return;

                difference_type range = lastExcluded.foo - firstIncluded.foo;

                Type* foo = lastExcluded.foo;
                Type* bar = firstIncluded.foo;

                while(foo != follow_on){
                    bar->~Type();
                    new(bar) Type(*foo);
                    foo->~Type();
                    ++foo;
                    ++bar;
                }
                while(bar != lastExcluded.foo){
                    bar->~Type();
                    ++bar;
                }

                follow_on -= range;
                size -= range;
            }

            size_t checkCapacity(size_t size){
                size_t new_capacity = INIT_SIZE;

                while(new_capacity <= size)
                    new_capacity <<=1;
                return new_capacity;
            }

            void increaseSize(size_t new_size){
                size_t new_capacity = checkCapacity(new_size);

                vector_capacity = new_capacity;

                char* new_dm = new char[sizeof(Type)*(vector_capacity+1)];

                Type* original_begin = vector_begin;
                Type* original_follow_on = follow_on;

                vector_begin = reinterpret_cast<Type*>(new_dm);
                follow_on = vector_begin + (original_follow_on - original_begin);

                //Move to new vector
                if(size>0){
                    Type* foo = original_begin;
                    Type* bar = vector_begin;

                    while(foo!=original_follow_on){
                        new(bar) Type(*foo);                        //Allocate elements to new memory: placement new
                        foo->~Type();
                        ++foo;
                        ++bar;
                    }
                }

                delete[] dm;
                dm = new_dm;
            }

            iterator begin(){ return const_iterator(vector_begin, vector_begin, follow_on); }

            iterator end(){ return const_iterator(follow_on, vector_begin, follow_on); }

            const_iterator cbegin() const{ return const_iterator(vector_begin, vector_begin, follow_on); }

            const_iterator cend() const{ return const_iterator(follow_on, vector_begin, follow_on); }

            const_iterator begin() const{ return cbegin(); }

            const_iterator end() const{ return cend(); }
    };

    template <typename Type>
    class Vector<Type>::ConstIterator
    {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type = typename Vector::value_type;
            using difference_type = typename Vector::difference_type;
            using pointer = typename Vector::const_pointer;
            using reference = typename Vector::const_reference;

            Type* foo;
            Type* vector_begin;
            Type* follow_on;

            explicit ConstIterator(Type* foo, Type* vector_begin, Type* follow_on)
            : foo(foo), vector_begin(vector_begin), follow_on(follow_on){}

            reference operator*() const{
                if(foo == follow_on)
                    throw std::out_of_range("There is no valid position");

                return *foo;
            }

            ConstIterator& operator++(){
                if(foo == follow_on)
                    throw std::out_of_range("The next position does not exist");

                ++foo;
                return *this;
            }

            ConstIterator operator++(int){
                ConstIterator result(foo, vector_begin, follow_on);
                ++(*this);
                return result;
            }

            ConstIterator& operator--(){
                if(foo == vector_begin)
                    throw std::out_of_range("The previous position does not exist");

                --foo;
                return *this;
            }

            ConstIterator operator--(int){
                ConstIterator result(foo, vector_begin, follow_on);
                --(*this);
                return result;
            }

            ConstIterator operator+(difference_type d) const{
                difference_type distance = follow_on - foo;

                if(d>distance)
                    throw std::out_of_range("Position does not exist");

                ConstIterator result(foo+d, vector_begin, follow_on);
                return result;
            }

            ConstIterator operator-(difference_type d) const{
                difference_type distance = foo - vector_begin;

                if(d>distance)
                    throw std::out_of_range("Position does not exist");

                ConstIterator result(foo-d, vector_begin, follow_on);
                return result;
            }

            bool operator==(const ConstIterator& other) const{ return this->foo == other.foo; }

            bool operator!=(const ConstIterator& other) const{ return !(*this == other); }
    };

    template <typename Type>
    class Vector<Type>::Iterator : public Vector<Type>::ConstIterator
    {
        public:
            using pointer = typename Vector::pointer;
            using reference = typename Vector::reference;

            explicit Iterator(Type* foo, Type* vector_begin, Type* follow_on): ConstIterator(foo, vector_begin, follow_on){}

            Iterator(const ConstIterator& other): ConstIterator(other) {}

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

#endif // AISDI_LINEAR_VECTOR_H
