#pragma once 
#include <iostream>
#include <memory>
#include <algorithm>
#include <iterator>

template <class T, class Allocator = std::allocator<T>> class DynamicArray{
  public:
    using value_type = T;
    using allocator_type = Allocator;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    class EvilIterator {
        public:
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T*;
            using reference = T&;
            using iterator_category = std::forward_iterator_tag;
                
            EvilIterator(pointer ptr) : m_ptr(ptr) {}
                
            reference operator*() const { return *m_ptr; }
            pointer operator->() { return m_ptr; }
                
            EvilIterator& operator++() {
                m_ptr++;
                return *this;
            }
            
            EvilIterator operator++(int) {
                EvilIterator tmp = *this;
                ++(*this);
                return tmp;
            }
            
            friend bool operator==(const EvilIterator& a, const EvilIterator& b) {
                return a.m_ptr == b.m_ptr;
            }
            
            friend bool operator!=(const EvilIterator& a, const EvilIterator& b) {
                return a.m_ptr != b.m_ptr;
            }
            
            private:
                pointer m_ptr;
            // no idea if I really need to write all of these but better safe than sorry
            };
            
            
            T& operator[](int index) {
                return data_[index];
            }
            
            const T& operator[](int index) const {
            return data_[index];
            }
            
            
            DynamicArray(): data_(nullptr), size_(0), capacity_(0) {}
            
            ~DynamicArray() {
                allocator_type().deallocate(data_, capacity_);
            }
            
            void push_back(const T &value){
                CheckToAddSpace();
                data_[size_++] = value;
            }

    void insert(size_t index, const T &value) {
        if (index >= size_) {
            throw std::out_of_range("this position is out of range");
        }
        CheckToAddSpace();
        for (size_t i = size_; i > index ; --i) {
            data_[i] = std::move(data_[i-1]);
        }

        data_[index] = value;
        size_++;
    }

    void erase(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("this position is out of range");
        }
        data_[index].~T();
        if (index == size_) {
            --size_;
        }

        else {
            for(size_t i = index; i < size_-1; i++) {
                data_[i] = std::move(data_[i + 1]);
            }
            --size_;
        }
    }

    reference at(size_type index){
        if (index < size_){
            return data_[index];
        }
        else {
            std::cout << "out of range";
            return data_[0];
        }
    }

    size_type size() const {
        return size_;
    }

    EvilIterator begin() { return EvilIterator(data_); }

    EvilIterator end() { return EvilIterator(data_ + size_); }


    private:
    // Pointer to the container's elements
        T *data_;
    // Number of elements in the container
        size_type size_;
    // Allocated capacity of the container
        size_type capacity_;
    // Allocate more memory
        void CheckToAddSpace() {
            if (size_ == capacity_) {
                // If the container is full, allocate more memory
                size_type new_capacity = capacity_ ? 2 * capacity_ : 1;
                T *new_data = allocator_type().allocate(new_capacity);
                std::copy(data_, data_ + size_, new_data);
                allocator_type().deallocate(data_, capacity_);
                data_ = new_data;
                capacity_ = new_capacity;
            }
        }
};

// =========

template<typename T>

class List {
private:
    struct Node {
        T data;
        Node *prev;
        Node *next;
        Node(const T& val) : data(val), prev(nullptr), next(nullptr){}
    };

    Node* head;
    Node* tail;
    size_t count;

public:
    List();
    ~List();
    size_t size() const;
    void push_back(const T& value);
    void push_front(const T& value);
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    void insert(size_t index, const T& value);
    void erase(size_t index); 
};

template<typename T>
List<T>::List() : head(nullptr), tail(nullptr), count(0){}

template <typename T>
List<T>::~List() {
    Node *current = head;

    while (current != nullptr) {
        Node *next = current->next; 
        delete current;
        current = next;
    }

    head = tail = nullptr;
    count = 0;
}

template<typename T>
size_t List<T>::size() const {
    return count;
}

template<typename T>
void List<T>::push_back(const T& value) {
    Node* NewNode = new Node(value);

    if (head == nullptr) {
        head = tail = NewNode;
    }

    else {
        NewNode->prev = tail;
        tail->next = NewNode;
        tail = NewNode;
    }

    ++count;
}

template<typename T>
void List<T>::push_front(const T& value) {
    Node* NewNode = new Node(value);

    if (head == nullptr) {
        head = tail = NewNode;
    }

    else {
        NewNode->next = head;
        head->prev = NewNode;
        head = NewNode;
    }

    ++count;
}

template<typename T> 
T &List<T>::operator[](size_t index){
    Node* curr = head;

    for (size_t i = 0; i < index; ++i) {
        curr = curr->next;
    }

    return curr->data;
}

template<typename T> 
const T &List<T>::operator[](size_t index) const{
    Node* curr = head;

    for (size_t i = 0; i < index; ++i) {
        curr = curr->next;
    }

    return curr->data;
}

template<typename T>
void List<T>::insert(size_t index, const T& value){

    if (index > count) {
        throw std::out_of_range("Of range");
    }
     
    Node* curr = head;
    for (size_t i = 0; i < index; ++i) {
        curr = curr->next;
    }

    Node* NewNode = new Node(value);

    NewNode -> next = curr;
    NewNode -> prev = curr->prev;
    curr->prev->next = NewNode;
    curr->prev = NewNode;
     
    ++count;
}

template<typename T>
void List<T>::erase(size_t index){

    if (count <= index) {
        throw std::out_of_range("Out in size");
    }

    Node* curr = head;
    for (size_t i = 0; i < index; ++i) {
        curr = curr->next;
    }

    Node *prevNode = curr->prev;
    Node *nextNode = curr->next;

    if (prevNode != nullptr) {
        prevNode->next = nextNode;
    }
    else {
        head = nextNode;
    }

    if (nextNode != nullptr) {
        nextNode->prev = prevNode;

    }
    else {
        tail = prevNode;
    }
    
    delete curr;
    --count;
}

// =========

template <typename T>

class NewDynamicArray {
private:
    std::unique_ptr<T[]> data_;
    size_t size_;
    size_t capacity_;
    void allocate();
public:
    NewDynamicArray();
    ~NewDynamicArray();
    size_t size() const;
    void push_back(const T& value);
    void erase(size_t index);
    void push_front(const T& value);
    void insert(size_t index, const T &value);
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
};

template<typename T>
NewDynamicArray<T>::NewDynamicArray() : data_(nullptr), size_(0), capacity_(0){}

template<typename T>
NewDynamicArray<T>::~NewDynamicArray() {
}

template<typename T>
size_t NewDynamicArray<T>::size() const {
    return size_;
}

template <typename T>
void NewDynamicArray<T>::push_back(const T &value)
{
    if (size_ == capacity_) {
        allocate();
    }

    data_[size_] = value;
    ++size_;
}

template<typename T>
void NewDynamicArray<T>::erase(size_t index) {
    if (index >= size_) {
        throw std::out_of_range("this position is out of range");
    }
    data_[index].~T();
    if (index == size_) {
        --size_;
    }

    else {
        for(size_t i = index; i < size_-1; i++) {
            data_[i] = std::move(data_[i + 1]);
        }
        --size_;
    }
}

template <typename T>
void NewDynamicArray<T>::push_front(const T &value) {
    if (size_ == capacity_) {
        allocate();
    }

    for (size_t i = size_; i > 0; --i) {
        data_[i] = std::move(data_[i - 1]);   
    }  

    data_[0] = value;
    ++size_;
}

template <typename T>
void NewDynamicArray<T>::insert(size_t index, const T &value) {
    if (index > size_) {
        throw std::out_of_range("index out of range");
    }
    if (size_ == capacity_) {
        allocate();
    }

    for (size_t i = size_; i > index; --i) {
        data_[i] = std::move(data_[i - 1]);
    }

    data_[index] = value;
    ++size_;
}

template <typename T>
T &NewDynamicArray<T>::operator[](size_t index) {
    return data_[index];
}

template <typename T>
const T &NewDynamicArray<T>::operator[](size_t index) const {
    return data_[index];
}

template<typename T>
void NewDynamicArray<T>::allocate() {
    size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ + capacity_ / 2;
    std::unique_ptr<T[]> new_data = std::make_unique<T[]>(new_capacity);
    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = std::move(data_[i]);
    }

    data_ = std::move(new_data);
    capacity_ = new_capacity;

}

// =========

template<typename T>

class NewList {
private:
    struct Node {
        T data;
        Node *prev;
        Node *next;
        Node(const T& val) : data(val), prev(nullptr), next(nullptr){}
    };

    Node* head;
    Node* tail;
    size_t count;

public:
    NewList();
    ~NewList();
    size_t size() const;
    void push_back(const T& value);
    void push_front(const T& value);
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    void insert(size_t index, const T& value);
    void erase(size_t index); 
};

template<typename T>
NewList<T>::NewList() : head(nullptr), tail(nullptr), count(0){}

template <typename T>
NewList<T>::~NewList() {
    Node *current = head;

    while (current != nullptr) {
        Node *next = current->next; 
        delete current;
        current = next;
    }

    head = tail = nullptr;
    count = 0;
}

template<typename T>
size_t NewList<T>::size() const{
    return count;
}

template<typename T>
void NewList<T>::push_back(const T& value){
    Node* NewNode = new Node(value);

    if (head == nullptr) {
        head = tail = NewNode;
    }

    else {
        NewNode->prev = tail;
        tail->next = NewNode;
        tail = NewNode;
    }

    ++count;
}

template<typename T>
void NewList<T>::push_front(const T& value){
    Node* NewNode = new Node(value);

    if (head == nullptr) {
        head = tail = NewNode;
    }

    else {
        NewNode->next = head;
        head->prev = NewNode;
        head = NewNode;
    }

    ++count;
}

template<typename T> 
T &NewList<T>::operator[](size_t index){
    Node* curr = head;

    for (size_t i = 0; i < index; ++i) {
        curr = curr->next;
    }

    return curr->data;
}

template<typename T> 
const T &NewList<T>::operator[](size_t index) const{
    Node* curr = head;

    for (size_t i = 0; i < index; ++i) {
        curr = curr->next;
    }

    return curr->data;
}

template<typename T>
void NewList<T>::insert(size_t index, const T& value){

    if (index > count) {
        throw std::out_of_range("index out of range");
    }
    
    Node* curr = head;
    for (size_t i = 0; i < index; ++i) {
        curr = curr->next;
    }

    Node* NewNode = new Node(value);

    NewNode -> next = curr;
    NewNode -> prev = curr->prev;
    curr->prev->next = NewNode;
    curr->prev = NewNode;
    
    ++count;
}

template<typename T>
void NewList<T>::erase(size_t index){

    if (count <= index) {
        throw std::out_of_range("index out of range");
    }

    Node* curr = head;
    for (size_t i = 0; i < index; ++i) {
        curr = curr->next;
    }

    Node *prevNode = curr->prev;
    Node *nextNode = curr->next;

    if (prevNode != nullptr) {
        prevNode->next = nextNode;
    }
    else {
        head = nextNode;
    }

    if (nextNode != nullptr) {
        nextNode->prev = prevNode;

    }
    else {
        tail = prevNode;
    }
    
    delete curr;
    --count;
}

// =========

template <typename T>

class ForwardList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr){}
        Node(T&& val) : data(std::move(val)), next(nullptr){}
    };

    Node* head;
    size_t count;

public: 
    class iterator {
    private:
        Node *curr_node;
    public:
        iterator() : curr_node(nullptr) {}

        explicit iterator(Node *node) : curr_node(node) {}

        T &operator*() const {
            return curr_node->data;
        }

        T *operator->() const {
            return &curr_node->data;
        }

        iterator &operator++() {
            curr_node = curr_node->next;
            return *this;
        }

        iterator operator++(int) {
            iterator h = *this;
            curr_node = curr_node->next;
            return h;
        }

        bool operator ==(const iterator& other) const {
            return curr_node == other.curr_node;
        }
        
        bool operator !=(const iterator& other) const {
            return curr_node != other.curr_node;
        }

    };

    ForwardList();
    ~ForwardList();
    void clear();
    ForwardList(ForwardList &&other) noexcept;
    ForwardList &operator=(ForwardList &&other) noexcept;
    iterator begin();
    iterator end();
    void push_front(T &&val);
    void push_front(const T &val);
    void push_back(T &&val);
    void push_back(const T &val);
};

template<typename T> 
ForwardList<T>::ForwardList() : head(nullptr), count(0){}

template<typename T> 
ForwardList<T>::~ForwardList()
{
    while (head) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

template<typename T> 
ForwardList<T>::ForwardList(ForwardList&& other) noexcept : head(other.head), count(other.count){
    other.head = nullptr;
    other.count = 0;
}

template <typename T>
ForwardList<T> &ForwardList<T>::operator=(ForwardList &&other) noexcept
{
    if (this != &other)
    {
        clear();
        head = other.head;
        count = other.count;
        other.head = nullptr;
        other.count = 0;
    }
    return *this;
}

template <typename T>
typename ForwardList<T>::iterator ForwardList<T>::begin()
{
    return iterator(head);
}

template <typename T>
typename ForwardList<T>::iterator ForwardList<T>::end()
{
    return iterator(nullptr);
}

template <typename T>
void ForwardList<T>::push_front(T&& val)
{
    Node* node = new Node(std::move(val));
    node->next = head;
    head = node;
    ++count;
}

template <typename T>
void ForwardList<T>::push_front(const T& val)
{
    Node* node = new Node(val);
    node->next = head;
    head = node;
    ++count;
}

template <typename T>
void ForwardList<T>::push_back(T&& val)
{
    Node* node = new Node(std::move(val));

    if (!head)
    {
        head = node;
    }
    else
    {
        Node* cur = head;
        while (cur->next)
            cur = cur->next;
        cur->next = node;
    }
    ++count;
}

template <typename T>
void ForwardList<T>::push_back(const T& val)
{
    Node* node = new Node(val);

    if (!head)
    {
        head = node;
    }
    else
    {
        Node* cur = head;
        while (cur->next)
            cur = cur->next;
        cur->next = node;
    }
    ++count;
}

template <typename T>
void ForwardList<T>::clear()
{
    while (head)
    {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    count = 0;
}