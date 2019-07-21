#ifndef AISDI_MAPS_TREEMAP_H
#define AISDI_MAPS_TREEMAP_H

#include <cstddef>
#include <forward_list>
#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace aisdi
{
    template <typename KeyType, typename ValueType>
    class TreeMap{
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
            class NullNode{
                public:
                    enum Color{BLACK, RED};

                    NullNode* map_parent;
                    NullNode* map_right;
                    NullNode* map_left;
                    Color map_color;

                    NullNode(): map_parent(this), map_right(this), map_left(this), map_color(Color::BLACK)
                    {}

                    virtual ~NullNode() = default;
            };

            class Node : public NullNode{
                public:
                    value_type map_value;

                    Node(const key_type& key, const mapped_type& value): NullNode(), map_value(key, value)
                    {}
            };

            NullNode* map_root;
            NullNode* map_nil;
            size_type map_size;

            void leftRotation(NullNode* foo){
                NullNode* bar = foo->map_right;
                foo->map_right = bar->map_left;

                if(bar->map_left != map_nil)
                    bar->map_left->map_parent = foo;

                bar->map_parent = foo->map_parent;

                if(foo->map_parent == map_nil){
                    map_root = bar;
                    map_nil->map_left = map_root;
                    map_nil->map_right = map_root;
                }
                else if(foo == foo->map_parent->map_left)
                    foo->map_parent->map_left = bar;
                else
                    foo->map_parent->map_right = bar;

                bar->map_left = foo;
                foo->map_parent = bar;
            }

            void rightRotation(NullNode* foo){
                NullNode* bar = foo->map_left;
                foo->map_left = bar->map_right;

                if(bar->map_right != map_nil)
                    bar->map_right->map_parent = foo;

                bar->map_parent = foo->map_parent;

                if(foo->map_parent == map_nil){
                    map_root = bar;
                    map_nil->map_left = map_root;
                    map_nil->map_right = map_root;
                }
                else if(foo == foo->map_parent->map_right)
                    foo->map_parent->map_right = bar;
                else
                    foo->map_parent->map_left = bar;

                bar->map_right = foo;
                foo->map_parent = bar;
            }

            void insertColors(NullNode* bar){
                NullNode* foo;

                while(bar->map_parent->map_color){
                    if(bar->map_parent == bar->map_parent->map_parent->map_left){
                        foo = bar->map_parent->map_parent->map_right;
                        if(foo->map_color){
                            bar->map_parent->map_color = NullNode::Color::BLACK;
                            foo->map_color = NullNode::Color::BLACK;
                            bar->map_parent->map_parent->map_color = NullNode::Color::RED;
                            bar = bar->map_parent->map_parent;
                        }
                        else{
                            if(bar == bar->map_parent->map_right){
                                bar = bar->map_parent;
                                leftRotation(bar);
                            }
                            bar->map_parent->map_color = NullNode::Color::BLACK;
                            bar->map_parent->map_parent->map_color = NullNode::Color::RED;
                            rightRotation(bar->map_parent->map_parent);
                        }
                    }
                    else{
                        foo = bar->map_parent->map_parent->map_left;
                        if(foo->map_color){
                            bar->map_parent->map_color = NullNode::Color::BLACK;
                            foo->map_color = NullNode::Color::BLACK;
                            bar->map_parent->map_parent->map_color = NullNode::Color::RED;
                            bar = bar->map_parent->map_parent;
                        }
                        else{
                            if(bar == bar->map_parent->map_left){
                                bar = bar->map_parent;
                                rightRotation(bar);
                            }
                            bar->map_parent->map_color = NullNode::Color::BLACK;
                            bar->map_parent->map_parent->map_color = NullNode::Color::RED;
                            leftRotation(bar->map_parent->map_parent);
                        }
                    }
                }
                map_root->map_color = NullNode::Color::BLACK;
            }

            NullNode* search(key_type key) const{
                NullNode* pointer = map_root;
                while(pointer != map_nil && static_cast<Node*>(pointer)->map_value.first != key)
                    if(key < static_cast<Node*>(pointer)->map_value.first)
                        pointer = pointer->map_left;
                    else
                        pointer = pointer->map_right;
                return pointer;
            }

            void insert(Node* node){
                NullNode* foo = map_root;
                NullNode* bar = map_nil;

                while(foo != map_nil){
                    bar = foo;
                    if(node->map_value.first < static_cast<Node*>(foo)->map_value.first)
                        foo = foo->map_left;
                    else
                        foo = foo->map_right;
                }
                node->map_parent = bar;

                if(bar == map_nil){
                    map_root = node;
                    map_nil->map_left = map_root;
                    map_nil->map_right = map_root;
                }
                else if(node->map_value.first < static_cast<Node*>(bar)->map_value.first)
                    bar->map_left = node;
                else
                    bar->map_right = node;

                node->map_left = map_nil;
                node->map_right = map_nil;
                node->map_color = Node::Color::RED;

                map_size++;
                insertColors(node);
            }

            void transplant(NullNode* foo, NullNode* bar){
                if(foo->map_parent == map_nil){
                    map_root = bar;
                    map_nil->map_left = map_root;
                    map_nil->map_right = map_root;
                }
                else if(foo == foo->map_parent->map_left)
                    foo->map_parent->map_left = bar;
                else
                    foo->map_parent->map_right = bar;
                bar->map_parent = foo->map_parent;
            }

            void deleteColors(NullNode* foo){
                NullNode* bar;
                while(foo != map_root && foo->map_color == NullNode::Color::BLACK){
                    if(foo == foo->map_parent->map_left){
                        bar = foo->map_parent->map_right;
                        if(bar->map_color){
                            bar->map_color = NullNode::Color::BLACK;
                            foo->map_parent->map_color = NullNode::Color::RED;
                            leftRotation(foo->map_parent);
                            bar = foo->map_parent->map_right;
                        }
                        if(bar->map_left->map_color == NullNode::Color::BLACK && bar->map_right->map_color == NullNode::Color::BLACK){
                            bar->map_color = NullNode::Color::RED;
                            foo = foo->map_parent;
                        }
                        else{
                            if(bar->map_right->map_color == Node::Color::BLACK){
                                bar->map_left->map_color = NullNode::Color::BLACK;
                                bar->map_color = NullNode::Color::RED;
                                rightRotation(bar);
                                bar = foo->map_parent->map_right;
                            }
                            bar->map_color = foo->map_parent->map_color;
                            foo->map_parent->map_color = NullNode::Color::BLACK;
                            bar->map_right->map_color = NullNode::Color::BLACK;
                            leftRotation(foo->map_parent);
                            foo = map_root;
                        }
                    }
                    else{
                        bar = foo->map_parent->map_left;
                        if(bar->map_color){
                            bar->map_color = NullNode::Color::BLACK;
                            foo->map_parent->map_color = NullNode::Color::RED;
                            rightRotation(foo->map_parent);
                            bar = foo->map_parent->map_left;
                        }
                        if(bar->map_right->map_color == NullNode::Color::BLACK && bar->map_left->map_color == NullNode::Color::BLACK){
                            bar->map_color = NullNode::Color::RED;
                            foo = foo->map_parent;
                        }
                        else{
                            if(bar->map_left->map_color == NullNode::Color::BLACK){
                                bar->map_right->map_color = NullNode::Color::BLACK;
                                bar->map_color = NullNode::Color::RED;
                                leftRotation(bar);
                                bar = foo->map_parent->map_left;
                            }
                            bar->map_color = foo->map_parent->map_color;
                            foo->map_parent->map_color = NullNode::Color::BLACK;
                            bar->map_left->map_color = NullNode::Color::BLACK;
                            rightRotation(foo->map_parent);
                            foo = map_root;
                        }
                    }
                }
                foo->map_color = NullNode::Color::BLACK;
            }

            void remove(NullNode* node){
                NullNode* original = node;
                NullNode* foo;
                NullNode* bar = node;
                auto barColor = bar->map_color;

                if(node->map_left == map_nil){
                    foo = node->map_right;
                    transplant(node, node->map_right);
                }
                else if(node->map_right == map_nil){
                    foo = node->map_left;
                    transplant(node, node->map_left);
                }
                else{
                    bar = node->map_right;

                    while(bar->map_left != map_nil)
                        bar = bar->map_left;

                    barColor = bar->map_color;
                    foo = bar->map_right;

                    if(bar->map_parent == node)
                        foo->map_parent = bar;
                    else{
                        transplant(bar, bar->map_right);
                        bar->map_right = node->map_right;
                        bar->map_right->map_parent = bar;
                    }

                    transplant(node, bar);
                    bar->map_left = node->map_left;
                    bar->map_left->map_parent = bar;
                    bar->map_color = node->map_color;
                }
                map_size--;
                if(barColor == Node::Color::BLACK)
                    deleteColors(foo);
                delete original;
            }

            void clear(){
                while(map_root != map_nil)
                    remove(map_root);
            }

        public:
            TreeMap(){
                map_nil = new NullNode();
                map_root = map_nil;
                map_size = 0;
            }

            ~TreeMap(){
                clear();
                delete map_nil;
            }

            TreeMap(std::initializer_list<value_type> list): TreeMap(){
                for(const value_type& value : list){
                    Node* foo = new Node(value.first, value.second);
                    insert(foo);
                }
            }

            TreeMap(const TreeMap& other): TreeMap(){
                for(auto i = other.begin(); i != other.end(); ++i){
                    Node* foo = new Node(i->first, i->second);
                    insert(foo);
                }
            }

            TreeMap(TreeMap&& other): map_root(nullptr), map_nil(nullptr), map_size(0){
                *this = std::move(other);
            }

            TreeMap& operator=(const TreeMap& other){
                if(this != &other){
                    clear();
                    for(auto i = other.begin(); i != other.end(); i++){
                        Node* foo = new Node(i->first, i->second);
                        insert(foo);
                    }
                }
                return *this;
            }

            TreeMap& operator=(TreeMap&& other){
                if(this != &other){
                    if(map_nil){
                        clear();
                        delete map_nil;
                    }

                    map_root = other.map_root;
                    map_nil = other.map_nil;
                    map_size = other.map_size;

                    other.map_root = nullptr;
                    other.map_nil = nullptr;
                    other.map_size = 0;
                }

                return *this;
            }

            bool isEmpty() const{ return !(map_size); }

            mapped_type& operator[](const key_type& key){
                NullNode* pointer = search(key);
                if(pointer == map_nil){
                    pointer = new Node(key, mapped_type{});
                    insert(static_cast<Node*>(pointer));
                }
                return static_cast<Node*>(pointer)->map_value.second;
            }

            const mapped_type& valueOf(const key_type& key) const{
                NullNode* foo = search(key);
                if(foo == map_nil)
                    throw std::out_of_range("Node with given key does not exist");

                return static_cast<Node*>(foo)->map_value.second;
            }

            mapped_type& valueOf(const key_type& key){
                //const_cast and static_cast to avoid code duplication
                const TreeMap<KeyType, ValueType>* x = static_cast<const TreeMap<KeyType, ValueType>*>(this);
                return const_cast<mapped_type&>(x->valueOf(key));
            }

            const_iterator find(const key_type& key) const{
                NullNode* foo = search(key);
                return const_iterator(*this, foo);
            }

            iterator find(const key_type& key){
                NullNode* foo = search(key);
                return iterator(*this, foo);
            }

            void remove(const key_type& key){
                NullNode* foo = search(key);
                if(foo == map_nil)
                    throw std::out_of_range("Node with given key does not exist");
                remove(foo);
            }

            void remove(const const_iterator& it){
                NullNode* foo = search(it->first);
                if(foo == map_nil)
                    throw std::out_of_range("Node with given key does not exist");
                remove(foo);
            }

            size_type getSize() const{ return map_size; }

            bool operator==(const TreeMap& other) const{
                if(this->getSize() != other.getSize())
                    return false;

                const_iterator foo = this->cbegin();
                const_iterator bar = other.cbegin();

                for(size_type i = 0; i<getSize(); i++){
                    if(foo->first != bar->first || foo->second != bar->second)
                        return false;

                    ++foo;
                    ++bar;
                }
                return true;
            }

            bool operator!=(const TreeMap& other) const{ return !(*this == other); }

            iterator begin(){
                NullNode* foo = map_root;
                while(foo->map_left != map_nil)
                    foo = foo->map_left;
                return iterator(*this, foo);
            }

            iterator end(){ return iterator(*this, map_root->map_parent); }

            const_iterator cbegin() const{
                NullNode* foo = map_root;
                while(foo->map_left != map_nil)
                    foo = foo->map_left;
                return const_iterator(*this, foo);
            }

            const_iterator cend() const{ return const_iterator(*this, map_root->map_parent); }

            const_iterator begin() const{ return cbegin(); }

            const_iterator end() const{ return cend(); }
    };

    template <typename KeyType, typename ValueType>
    class TreeMap<KeyType, ValueType>::ConstIterator{
        public:
            using reference = typename TreeMap::const_reference;
            using value_type = typename TreeMap::value_type;
            using pointer = const typename TreeMap::value_type*;
            using nullnode = typename TreeMap::NullNode;
            using node = typename TreeMap::Node;

        protected:
            const TreeMap& map;
            nullnode* map_pointer;

        public:
            explicit ConstIterator(const TreeMap& map, nullnode* pointer)
            :map(map), map_pointer(pointer)
            {}

            ConstIterator(const ConstIterator& other)
            :map(other.map), map_pointer(other.map_pointer)
            {}

            ConstIterator& operator++(){
                if(map_pointer == map.map_nil)
                    throw std::out_of_range("Next node does not exist");

                if(map_pointer->map_right != map.map_nil){
                    nullnode* foo = map_pointer->map_right;
                    while(foo->map_left != map.map_nil)
                        foo = foo->map_left;
                    map_pointer = foo;
                    return *this;
                }

                nullnode* bar = map_pointer->map_parent;
                nullnode* foo = map_pointer;

                while(bar != map.map_nil && foo == bar->map_right){
                    foo = bar;
                    bar = bar->map_parent;
                }

                map_pointer = bar;
                return *this;
            }

            ConstIterator operator++(int){
                ConstIterator tmp(*this);
                ++(*this);
                return tmp;
            }

            ConstIterator& operator--(){
                nullnode* minimum = map.map_root;
                while(minimum->map_left != map.map_nil)
                    minimum = minimum->map_left;

                if(map_pointer == minimum)
                    throw std::out_of_range("Previous node does not exist");

                if(map_pointer->map_left != map.map_nil){
                    nullnode* foo = map_pointer->map_left;
                    while(foo->map_right != map.map_nil)
                        foo = foo->map_right;
                    map_pointer = foo;
                    return *this;
                }

                nullnode* bar = map_pointer->map_parent;
                nullnode* foo = map_pointer;

                while(bar != map.map_nil && foo == bar->map_left){
                    foo = bar;
                    bar = bar->map_parent;
                }

                map_pointer = bar;
                return *this;
            }

            ConstIterator operator--(int){
                ConstIterator tmp(*this);
                --(*this);
                return tmp;
            }

            reference operator*() const{
                if(map_pointer == map.map_nil)
                    throw std::out_of_range("Iterator out of range");

                return static_cast<node*>(map_pointer)->map_value;
            }

            pointer operator->() const{ return &this->operator*(); }

            bool operator==(const ConstIterator& other) const{ return map_pointer == other.map_pointer; }

            bool operator!=(const ConstIterator& other) const{ return !(*this == other); }
    };

    template <typename KeyType, typename ValueType>
    class TreeMap<KeyType, ValueType>::Iterator : public TreeMap<KeyType, ValueType>::ConstIterator{
        public:
            using reference = typename TreeMap::reference;
            using pointer = typename TreeMap::value_type*;
            using nullnode = typename TreeMap::NullNode;

            explicit Iterator(const TreeMap& map, nullnode* pointer)
            : ConstIterator(map, pointer)
            {}

            Iterator(const ConstIterator& other)
            : ConstIterator(other)
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

#endif /* AISDI_MAPS_MAP_H */
