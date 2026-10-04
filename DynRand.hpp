#pragma once
#include <iostream>
#include <memory>
#include <algorithm>

template<typename T>

class DynRand {
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
    DynRand();
    ~DynRand();
    size_t size() const;
    void push_back(const T& value);
    void push_front(const T& value);
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    void insert(size_t index, const T& value);
    void erase(size_t index); 
};

template<typename T>
DynRand<T>::DynRand() : head(nullptr), tail(nullptr), count(0){}

template <typename T>
DynRand<T>::~DynRand() {
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
size_t DynRand<T>::size() const {
    return count;
}

template<typename T>
void DynRand<T>::push_back(const T& value) {
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
void DynRand<T>::push_front(const T& value) {
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
T &DynRand<T>::operator[](size_t index){
    Node* curr = head;

    for (size_t i = 0; i < index; ++i) {
        curr = curr->next;
    }

    return curr->data;
}

template<typename T> 
const T &DynRand<T>::operator[](size_t index) const{
    Node* curr = head;

    for (size_t i = 0; i < index; ++i) {
        curr = curr->next;
    }

    return curr->data;
}

template<typename T>
void DynRand<T>::insert(size_t index, const T& value){

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
void DynRand<T>::erase(size_t index){

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