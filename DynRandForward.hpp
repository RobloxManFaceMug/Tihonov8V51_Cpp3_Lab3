#pragma once 
#include <memory>
#include <algorithm>

template <typename T>

class DynRandForward {
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

    DynRandForward();
    ~DynRandForward();
};

template<typename T> 
DynRandForward<T>::DynRandForward() : head(nullptr), count(0){}

template<typename T> 
DynRandForward<T>::~DynRandForward()
{
    while (head) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}