#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() {
        capacity_ = 4;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[capacity_];
    }

    explicit ABDQ(std::size_t capacity) {
        capacity_ = capacity;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[capacity];
    }
    ABDQ(const ABDQ& other) {
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->front_ = other.front_;
        this->back_ = other.back_;
        this->data_ = new T[capacity_];

        for (size_t i = 0; i < size_; i++) {
            this->data_[i] = other.data_[i];
        }
    }
    ABDQ(ABDQ&& other) noexcept {
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->front_ = other.front_;
        this->back_ = other.back_;
        this->data_ = other.data_;

        other.data_ = nullptr;
        other.capacity = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }
    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) {
            return *this;
        }

        T* temp = new T[other.capacity_];
        delete[] this->data_;

        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->front_ = other.front_;
        this->back_ = other.back_;
        this->data_ = temp;

        for (size_t i = 0; i < other.size_; i++) {
            this->data_[i] = other.data_[i];
        }
        return *this;

    }
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        delete[] this->data_;
        this->data_ = other.data_;
        this->size_ = other.size_;
        this->capacity_ = other.capacity_;
        this->front_ = other.front_;
        this->back_ = other.back_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;

        return *this;
    }
    ~ABDQ() override {
        delete[] data_;
        size_ = 0;
        capacity_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = nullptr;
    }

    // Insertion
    void pushFront(const T& item) override {
        if (capacity_ == 0) {
            T* temp = new T[1];      
            capacity_ = 1;   
            delete[] data_;
            data_ = temp;
        }
        else {
            if (size_ == capacity_) {
                capacity_*=2;
                T* temp = new T[capacity_ * SCALE_FACTOR];
                for (size_t i = 0; i < size_; i++) {
                    temp[i + 1] = data_[i];
                }
                delete[] data_;
                data_ = temp;
            }
        }
        data_[0] = item;
        size_++;
    }
    void pushBack(const T& item) override {
        if (capacity_ == 0) {
            T* temp = new T[1];      
            capacity_ = 1;   
            delete[] data_;
            data_ = temp;
        }
        else {
            if (size_ == capacity_) {
                capacity_*=2;
                T* temp = new T[capacity_ * SCALE_FACTOR];
                for (size_t i = 0; i < size_; i++) {
                    temp[i] = data_[i];
                }
                delete[] data_;
                data_ = temp;
            }
        }
        data_[size_] = item;
        size_++;
        back_++;
    }

    // Deletion
    T popFront() override {
        if (size_ > 0) {
            --size_;
            T tempVar = data_[front_];
            T* temp = new T[size_];
            for (size_t i = 1; i < size_; i++) {
                    temp[i] = data_[i];
            }
            delete[] data_;
            data_ = temp;
            return tempVar;
        }
        else {
            throw std::runtime_error("Out of range");
        }
    }
    T popBack() override {
        if (size_ > 0) {
            T tempVar = data_[back_];
            --size_;
            T* temp = new T[size_];
            for (size_t i = 0; i < size_; i++) {
                    temp[i] = data_[i];
            }
            delete[] data_;
            data_ = temp;
            --back_;
            return tempVar;
        }
        else {
            throw std::runtime_error("Out of range");
        }
    }

    // Access
    const T& front() const override {
        return data_[front_];
    }
    const T& back() const override {
        return data_[back_];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }

};
