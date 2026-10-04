#pragma once 
#include<iostream>
#include<memory>

template <typename T>

class DynSec2 {
private:
    std::unique_ptr<T[]> data_;
    size_t size_;
    size_t capacity_;
    void allocate();
public:
    DynSec2();
    ~DynSec2();
    size_t size() const;
    void push_back(const T& value);
    void erace(size_t index);
    void push_front(const T& value);
    void insert(size_t index, const T &value);
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
};

template<typename T>
DynSec2<T>::DynSec2() : data_(nullptr), size_(0), capacity_(0){}

template<typename T>
DynSec2<T>::~DynSec2() {
}

template<typename T>// size
size_t DynSec2<T>::size() const {
    return size_;
}

template <typename T>// push_back
void DynSec2<T>::push_back(const T &value)
{
    if (size_ == capacity_) {
        allocate();
    }

    data_[size_] = value;
    ++size_;
}

template<typename T>
void DynSec2<T>::erace(size_t index) {
    if(size_ < index) {
        throw std::out_of_range("Out in size");
    }

    for(size_t i = index; i < size_ - 1; ++i) {
        data_[i] = std::move(data_[i+1]);
    }
    --size_;
}

template <typename T>// push_front
void DynSec2<T>::push_front(const T &value) {
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
void DynSec2<T>::insert(size_t index, const T &value) {
    if (index > size_) {
        throw std::out_of_range("Out in size");
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
T &DynSec2<T>::operator[](size_t index) {
    return data_[index];
}

template <typename T>
const T &DynSec2<T>::operator[](size_t index) const {
    return data_[index];
}

template<typename T>
void DynSec2<T>::allocate() {
    size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ + capacity_ / 2;
    std::unique_ptr<T[]> new_data = std::make_unique<T[]>(new_capacity);
    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = std::move(data_[i]);
    }

    data_ = std::move(new_data);
    capacity_ = new_capacity;

}