#include <iostream>
#include <iterator>
#include <stdexcept>
#include "DynRand.hpp"
#include "DynRand2.hpp"
#include "DynRandForward.hpp"
#include "DynSec2.hpp"

template <class T, class Allocator = std::allocator<T>> class DynSec{
  public:
    using value_type = T;
    using allocator_type = Allocator;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

 
    T& operator[](int index) {
        return data_[index];
    }


    DynSec(): data_(nullptr), size_(0), capacity_(0) {}

    ~DynSec() {
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
        for(size_t i = index; i < size_-1; i++)
        {
            data_[i] = std::move(data_[i + 1]);
        }
        --size_;
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

int main() {
    std::cout << "-Dynamic sequential memory container-" << std::endl;
    DynSec<int> Container;
    Container.push_back(0);
    Container.push_back(1);
    Container.push_back(2);
    Container.push_back(3);
    Container.push_back(4);
    Container.push_back(5);
    Container.push_back(6);
    Container.push_back(7);
    Container.push_back(8);
    Container.push_back(9);
    for (size_t i = 0; i < Container.size(); i++) {
        std::cout << Container[i] << " ";
    }

    std::cout << std::endl << Container.size() << std::endl;

    Container.erase(2);
    Container.erase(3);
    Container.erase(4);
    for (size_t i = 0; i < Container.size(); i++) {
        std::cout << Container[i] << " ";
    }
    std::cout << std::endl;

    Container.insert(0, 10);
    for (size_t i = 0; i < Container.size(); i++) {
        std::cout << Container[i] << " ";
    }
    std::cout << std::endl;

    Container.insert(4, 20);
    for (size_t i = 0; i < Container.size(); i++) {
        std::cout << Container[i] << " ";
    }
    std::cout << std::endl;

    Container.push_back(30);
    for (size_t i = 0; i < Container.size(); i++) {
        std::cout << Container[i] << " ";
    }
    std::cout << std::endl;


    std::cout << "-Dynamic random memory container-" << std::endl;
    DynRand<int> Container2;
    Container2.push_back(0);
    Container2.push_back(1);
    Container2.push_back(2);
    Container2.push_back(3);
    Container2.push_back(4);
    Container2.push_back(5);
    Container2.push_back(6);
    Container2.push_back(7);
    Container2.push_back(8);
    Container2.push_back(9);
    for (size_t i = 0; i < Container2.size(); i++) {
        std::cout << Container2[i] << " ";
    }

    std::cout << std::endl << Container2.size() << std::endl;

    Container2.erase(2);
    Container2.erase(3);
    Container2.erase(4);
    for (size_t i = 0; i < Container2.size(); i++) {
        std::cout << Container2[i] << " ";
    }
    std::cout << std::endl;
    
    Container2.push_front(10);
    for (size_t i = 0; i < Container2.size(); i++) {
        std::cout << Container2[i] << " ";
    }
    std::cout << std::endl;

    Container2.insert(4, 20);
    for (size_t i = 0; i < Container2.size(); i++) {
        std::cout << Container2[i] << " ";
    }
    std::cout << std::endl;

    Container2.push_back(30);
    for (size_t i = 0; i < Container2.size(); i++) {
        std::cout << Container2[i] << " ";
    }
    std::cout << std::endl;
}