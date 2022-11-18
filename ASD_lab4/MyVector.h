#pragma once
#ifndef MyVector_h__
#define MyVector_h__

#include <iostream>

template<typename T>
class Vector {
public:
    Vector() {
        arr_ = new T[1];
        capacity_ = 1;
    }
    bool isEmpty() const {
        return size_ == 0;
    }
    size_t size() const {
        return size_;
    }
    size_t capacity() const {
        return capacity_;
    }
    void addMemory() {
        capacity_ *= 2;
        T* tmp = arr_;
        arr_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) arr_[i] = tmp[i];
        delete[] tmp;
    }
    void pushBack(const T& value) {
        if (size_ >= capacity_) addMemory();
        arr_[size_++] = value;
    }
    void remove(size_t index) {
        for (size_t i = index + 1; i < size_; ++i) {
            arr_[i - 1] = arr_[i];
        }
        --size_;
    }
    T& operator[](size_t index) {
        return arr_[index];
    }

    const T& operator[](size_t index) const {
        return arr_[index];
    }
    ~Vector() {
        delete[] arr_;
    }
    friend std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
        for (size_t i = 0; i < vec.size(); ++i) os << vec[i] << " ";
        return os;
    }
private:
    T* arr_;
    size_t size_{};
    size_t capacity_{};
};

#endif // !MyVector_h__
