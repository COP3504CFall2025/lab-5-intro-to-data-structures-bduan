#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    // copied big 5 implementation from ABS
    ABQ() {
        capacity_ = 1;
        curr_size_ = 0;
        array_ = new T[capacity_];
    }
    explicit ABQ(const size_t capacity) {
        capacity_ = capacity;
        curr_size__ = 0;
        array = new T[capacity_];
    }
    ABQ(const ABQ& other) {
        this.capacity_ = other.capacity_;
        this.curr_size__ = other.curr_size__;
        this->array_ = new T[other.capacity_];

        for (int i = 0; i < other.capacity_; i++) {
            this->array_[i] = other->array_[i];
        }
    }
    ABQ& operator=(const ABQ& rhs) {
        this.capacity_ = other.capacity_;
        this.curr_size_ = other.curr_size_;
        this->array_ = other->array_;

        other.capacity_ = 0;
        other.curr_size_ = 0;
        other->array_ = nullptr;
    }
    ABQ(ABQ&& other) noexcept {
        if (this == other) {
            return *this;
        }

        T* temp = new T[other.capacity_];
        delete this->array_;

        this.capacity_ = other.capacity_;
        this.curr_size_ = other.curr_size_;
        this->array_ = temp;

        for (int i = 0; i < other.capacity_; i++) {
            this->array_[i] = other->array_[i];
        }
        return *this;
    }
    ABQ& operator=(ABQ&& rhs) noexcept {
        if (this == other) {
            return *this;
        }
        delete this->array_;
        this.capacity_ = other.capacity_;
        this.curr_size_ = other.curr_size_;
        this->array_ = other->array_;

        other.capacity_ = 0;
        other.curr_size_ = 0;
        other->array_ = nullptr;

        return *this;
    }
    ~ABQ() noexcept override {
        delete[] array_;
        array_ = nullptr;
        capacity_ = 0;
        curr_size_ = 0;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    }
    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

    // Insertion
    void enqueue(const T& data) override {
        if (capacity_ == 0) {
            T* temp = new T[1];      
            capacity_ = 1;   
        }
        else {
            if (curr_size_ == capacity_) {
                capacity_*=2;
                T* temp = new T[capacity_ * scale_factor_];
                for (int i = 0; i < curr_size_; i++) {
                    temp[i] = array_[i];
                }
            }
        }
        delete[] array_;
        array_ = temp;
        array_[curr_size_] = data;
        curr_size_++;
    }

    // Access
    T peek() const override {
        return array_[0];
    }

    // Deletion
    T dequeue() override {
        if (curr_size_ > 0) {
            --curr_size_;
            T* temp = new T[curr_size_];
            for (int i = 1; i < curr_size_; i++) {
                    temp[i] = array_[i];
            }
            delete[] array_;
            array_ = temp;
        }
        else {
            throw std::runtime_error("Out of range");
        }
    }

};
