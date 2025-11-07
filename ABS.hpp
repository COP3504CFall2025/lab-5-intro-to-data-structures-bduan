#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS() {
        capacity__ = 1;
        curr_size__ = 0;
        array_ = new T[capacity_];
    }
    explicit ABS(const size_t capacity) {
        capacity_ = capacity;
        curr_size__ = 0;
        array = new T[capacity_];
    }
    ABS(const ABS& other) {
        this->capacity_ = other.capacity_;
        this->curr_size__ = other.curr_size__;
        this->array_ = new T[other.capacity_];

        for (size_t i = 0; i < other.capacity_; i++) {
            this->array_[i] = other.array_[i];
        }
    }
    ABS& operator=(const ABS& rhs) {
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;
        this->array_ = other.array_;

        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.array_ = nullptr;

    }
    ABS(ABS&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        T* temp = new T[other.capacity_];
        delete this->array_;

        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;
        this->array_ = temp;

        for (size_t i = 0; i < other.capacity_; i++) {
            this->array_[i] = other.array_[i];
        }
        return *this;
    }
    ABS& operator=(ABS&& rhs) noexcept {
        if (this == &other) {
            return *this;
        }
        delete this->array_;
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;
        this->array_ = other.array_;

        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.array_ = nullptr;

        return *this;
    }
    ~ABS() noexcept override {
        delete[] array_;
        array_ = nullptr;
        capacity_ = 0;
        curr_size_ = 0;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxcapacity_() const noexcept {
        return capacity_;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

    // Push item onto the stack
    void push(const T& data) override {
        // code/concepts taken from iDynamArray lab
        if (capacity_ == 0) {
            T* temp = new T[1];      
            capacity_ = 1;   
        }
        else {
            if (curr_size_ == capacity_) {
                capacity_*=2;
                T* temp = new T[capacity_ * scale_factor_];
                for (size_t i = 0; i < curr_size_; i++) {
                    temp[i] = array_[i];
                }
            }
        }
        delete[] array_;
        array_ = temp;
        array_[curr_size_] = data;
        curr_size_++;
    }

    T peek() const override {
        return array_[curr_size_];
    }

    T pop() override {
        if (curr_size_ > 0) {
            --curr_size_;
            T* temp = new T[curr_size_];
            for (size_t i = 0; i < curr_size_; i++) {
                    temp[i] = array_[i];
            }
            delete[] array_;
            array_ = temp;
        }
        else {
            throw std::runtime_error("Out of range");
        }
    }

private:
    size_t capacity__;
    size_t curr_size__;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
