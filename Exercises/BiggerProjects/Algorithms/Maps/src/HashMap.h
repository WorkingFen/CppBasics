#ifndef AISDI_MAPS_HASHMAP_H
#define AISDI_MAPS_HASHMAP_H

#include <algorithm>
#include <array>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <list>
#include <stdexcept>
#include <string>
#include <utility>

#define SIZE 16384

namespace aisdi{

    template <typename KeyType, typename ValueType>
    class HashMap{
        public:
            using key_type = KeyType;
            using mapped_type = ValueType;
            using value_type = std::pair<const key_type, mapped_type>;
            using size_type = std::size_t;
            using reference = value_type&;
            using const_reference = const value_type&;

            class ConstIterator;
            class Iterator;
            using iterator = Iterator;
            using const_iterator = ConstIterator;

        private:
            std::array<std::list<value_type>, SIZE> map_data;
            size_type map_size = 0;
            std::hash<key_type> hash_func;

        public:
            HashMap(){}

            HashMap(std::initializer_list<value_type> list): map_size(list.size()){
                for(const value_type& element : list){
                    const size_type index = hash_func(element.first)%SIZE;
                    map_data[index].emplace_back(element.first, element.second);
                }
            }

            HashMap(const HashMap& other){
                for(size_type i = 0; i<SIZE; i++){
                    if(!other.map_data[i].empty())
                        for(auto element : other.map_data[i])
                            map_data[i].emplace_back(element.first, element.second);
                }
                map_size = other.map_size;
            }

            HashMap(HashMap&& other){ *this = std::move(other); }

            HashMap& operator=(const HashMap& other){
                if(this != &other){
                    for(size_type i = 0; i<SIZE; i++){
                        map_data[i].clear();
                        if(!other.map_data[i].empty())
                            for(auto element : other.map_data[i])
                                map_data[i].emplace_back(element.first, element.second);
                    }
                    map_size = other.map_size;
                }
                return *this;
            }

            HashMap& operator=(HashMap&& other){
                if(this != &other){
                    map_data = std::move(other.map_data);
                    map_size = other.map_size;

                    other.map_size = 0;
                }
                return *this;
            }

            bool isEmpty() const{ return !(map_size); }

            mapped_type& operator[](const key_type& key){
                const size_type index = hash_func(key)%SIZE;

                for(auto iter = map_data[index].begin(); iter != map_data[index].end(); iter++){
                    if((*iter).first == key)
                        return (*iter).second;
                }

                map_data[index].emplace_back(key, mapped_type{});
                map_size++;
                return map_data[index].back().second;
            }

            const mapped_type& valueOf(const key_type& key) const{
                const size_type index = hash_func(key)%SIZE;

                for(auto iter = map_data[index].begin(); iter != map_data[index].end(); iter++){
                    if((*iter).first == key)
                        return (*iter).second;
                }

                throw std::out_of_range("Element with given key does not exist");
            }

            mapped_type& valueOf(const key_type& key){
                //const_cast and static_cast to avoid code duplication
                const HashMap<KeyType, ValueType>* x = static_cast<const HashMap<KeyType, ValueType>*>(this);
                return const_cast<mapped_type&>(x->valueOf(key));
            }

            const_iterator find(const key_type& key) const{
                const size_type index = hash_func(key)%SIZE;

                for(auto iter = map_data[index].begin(); iter != map_data[index].end(); iter++){
                    if((*iter).first == key)
                        return const_iterator(*this, index, iter);
                }

                return cend();
            }

            iterator find(const key_type& key){
                const size_type index = hash_func(key)%SIZE;

                for(auto iter = map_data[index].begin(); iter != map_data[index].end(); iter++){
                    if((*iter).first == key)
                        return iterator(*this, index, iter);
                }

                return end();
            }

            void remove(const key_type& key){
                const size_type index = hash_func(key)%SIZE;

                for(auto iter = map_data[index].begin(); iter != map_data[index].end(); iter++){
                    if((*iter).first == key){
                        map_data[index].erase(iter);
                        --map_size;
                        return;
                    }
                }

                throw std::out_of_range("Element with given key does not exist");
            }

            void remove(const const_iterator& it){
                const size_type index = hash_func(it->first)%SIZE;

                for(auto iter = map_data[index].begin(); iter != map_data[index].end(); iter++){
                    if((*iter).first == it->first){
                        map_data[index].erase(iter);
                        --map_size;
                        return;
                    }
                }

                throw std::out_of_range("Element with given key does not exist");
            }

            size_type getSize() const{ return map_size; }

            bool operator==(const HashMap& other) const{
                if(this->getSize() != other.getSize())
                    return false;

                const_iterator foo = this->cbegin();
                const_iterator bar = other.cbegin();

                for(size_type i = 0; i<this->getSize(); i++){
                    if(foo->first != bar->first || foo->second != bar->second)
                        return false;
                    foo++;
                    bar++;
                }
                return true;
            }

            bool operator!=(const HashMap& other) const{ return !(*this == other); }

            iterator begin(){
                if(!isEmpty())
                    for(size_type i = 0; i<SIZE; i++)
                        if(!map_data[i].empty())
                            return iterator(*this, i, map_data[i].begin());
                return iterator(*this, 0, map_data[0].begin(), true);
            }

            iterator end(){ return iterator(*this, SIZE-1, map_data[SIZE-1].end(), true); }

            const_iterator cbegin() const{
                if(!isEmpty())
                    for(size_type i = 0; i<SIZE; i++)
                        if(!map_data[i].empty())
                            return const_iterator(*this, i, map_data[i].begin());
                return const_iterator(*this, 0, map_data[0].begin(), true);
            }

            const_iterator cend() const{ return const_iterator(*this, SIZE-1, map_data[SIZE-1].end(), true); }

            const_iterator begin() const{ return cbegin(); }

            const_iterator end() const{ return cend(); }
    };

    template <typename KeyType, typename ValueType>
    class HashMap<KeyType, ValueType>::ConstIterator
    {
        public:
            using reference = typename HashMap::const_reference;
            using value_type = typename HashMap::value_type;
            using pointer = const typename HashMap::value_type*;
            using size_type = typename HashMap::size_type;
            using list_iterator = typename std::list<std::pair<const KeyType, ValueType>>::const_iterator;

        protected:
            const HashMap &map;
            size_type map_index;
            list_iterator list_element;
            bool list_sentinel;

        public:
            explicit ConstIterator(const HashMap& map, size_type index, list_iterator element, bool sentinel = false)
            :map(map), map_index(index), list_element(element), list_sentinel(sentinel)
            {}

            ConstIterator(const ConstIterator& other)
            : map(other.map), map_index(other.map_index), list_element(other.list_element), list_sentinel(other.list_sentinel)
            {}

            ConstIterator& operator++(){
                if(list_sentinel)
                    throw std::out_of_range("There is no valid element");

                list_iterator tmp = ++list_element;
                if(tmp != map.map_data[map_index].end()){
                    ++list_element;
                    return *this;
                }

                for(size_type i = map_index+1; i<SIZE; ++i){
                    if(!map.map_data[i].empty()){
                        list_element = map.map_data[i].begin();
                        map_index = i;
                        return *this;
                    }
                }

                map_index = SIZE-1;
                list_element = map.map_data[SIZE-1].end();
                list_sentinel = true;
                return *this;
            }

            ConstIterator operator++(int){
                ConstIterator tmp(*this);
                ++(*this);
                return tmp;
            }

            ConstIterator& operator--(){
                if(list_element != map.map_data[map_index].begin()){
                    --list_element;
                    list_sentinel = false;
                    return *this;
                }

                if(map_index==0)
                    throw std::out_of_range("Previous iterator does not exist");

                for(size_type i = 0; i<=map_index-1; ++i){
                    if(!map.map_data[i].empty()){
                        list_element = --(map.map_data[i].end());
                        map_index = i;
                        list_sentinel = false;
                        return *this;
                    }
                }

                throw std::out_of_range("Previous iterator does not exist");
            }

            ConstIterator operator--(int){
                ConstIterator tmp(*this);
                --(*this);
                return tmp;
            }

            reference operator*() const{
                if(list_sentinel)
                    throw std::out_of_range("Iterator does not have any value");
                return *(list_element);
            }

            pointer operator->() const{ return &this->operator*(); }

            bool operator==(const ConstIterator& other) const{
                if(&map== &(other.map)){
                    if(list_sentinel == other.list_sentinel)
                        return true;
                    return map_index == other.map_index && list_element == other.list_element;
                }
                return false;
            }

            bool operator!=(const ConstIterator& other) const{ return !(*this == other); }
    };

    template <typename KeyType, typename ValueType>
    class HashMap<KeyType, ValueType>::Iterator : public HashMap<KeyType, ValueType>::ConstIterator
    {
        public:
            using reference = typename HashMap::reference;
            using pointer = typename HashMap::value_type*;
            using list_iterator = typename std::list<std::pair<const KeyType, ValueType>>::iterator;

            explicit Iterator(const HashMap& map, size_type index, list_iterator element, bool sentinel = false)
            : ConstIterator(map, index, element, sentinel)
            {}

            Iterator(const ConstIterator& other)
            :ConstIterator(other)
            {}

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

            pointer operator->() const{ return &this->operator*(); }

            reference operator*() const{
                // ugly cast, yet reduces code duplication.
                return const_cast<reference>(ConstIterator::operator*());
            }
    };
}

#endif /* AISDI_MAPS_HASHMAP_H */
