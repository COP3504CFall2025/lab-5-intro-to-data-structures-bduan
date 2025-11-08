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
        curr_size_ = 0;
        array_ = new T[capacity_];
    }
    ABQ(const ABQ& other) {
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;
        this->array_ = new T[other.capacity_];

        for (size_t i = 0; i < other.curr_size_; i++) {
            this->array_[i] = other.array_[i];
        }
    }
    ABQ& operator=(const ABQ& rhs) {
        if (this == &rhs) {
            return *this;
        }

        T* temp = new T[rhs.capacity_];
        delete[] this->array_;

        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.curr_size_;
        this->array_ = temp;

        for (size_t i = 0; i < rhs.curr_size_; i++) {
            this->array_[i] = rhs.array_[i];
        }
        return *this;
    }
    ABQ(ABQ&& other) noexcept {
        this->capacity_ = other.capacity_;
        this->curr_size_ = other.curr_size_;
        this->array_ = other.array_;

        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.array_ = nullptr;
    }
    ABQ& operator=(ABQ&& rhs) noexcept {
        if (this == &rhs) {
            return *this;
        }
        delete[] this->array_;
        this->capacity_ = rhs.capacity_;
        this->curr_size_ = rhs.curr_size_;
        this->array_ = rhs.array_;

        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        rhs.array_ = nullptr;

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
            if (curr_size_ == capacity_) {
                capacity_*=scale_factor_;
                T* temp = new T[capacity_];
                for (size_t i = 0; i < curr_size_; i++) {
                    temp[i] = array_[i];
                }
            delete[] array_;
            array_ = temp;
            }
            array_[curr_size_] = data;
            curr_size_++;
    }

    // Access
    T peek() const override {
        if (curr_size_ == 0) {
            throw std::runtime_error("empty array");
        }
        return array_[0];
    }

    // Deletion
    T dequeue() override {
        if (curr_size_ > 0) {
            T tempVal = array_[0];
            --curr_size_;
            if (curr_size_ <= capacity_ / 4) {
                capacity_ /=2;
            }
            T* temp = new T[capacity_];
            for (size_t i = 0; i < curr_size_; i++) {
                    temp[i] = array_[i + 1];
            }
            delete[] array_;
            array_ = temp;
            return tempVal;
        }
        else {
            throw std::runtime_error("Out of range");
        }
    }

};
