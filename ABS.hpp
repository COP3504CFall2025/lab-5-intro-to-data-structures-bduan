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
        array_ = new T[capacity__];
    }
    explicit ABS(const size_t capacity) {
        capacity__ = capacity;
        curr_size__ = 0;
        array_ = new T[capacity__];
    }
    ABS(const ABS& other) {
        this->capacity__ = other.capacity__;
        this->curr_size__ = other.curr_size__;
        this->array_ = new T[other.capacity__];

        for (size_t i = 0; i < other.capacity__; i++) {
            this->array_[i] = other.array_[i];
        }
    }
    ABS& operator=(const ABS& rhs) {
        if (this == &rhs) {
            return *this;
        }

        T* temp = new T[rhs.capacity__];
        delete[] this->array_;

        this->capacity__ = rhs.capacity__;
        this->curr_size__ = rhs.curr_size__;
        this->array_ = temp;

        for (size_t i = 0; i < rhs.curr_size__; i++) {
            this->array_[i] = rhs.array_[i];
        }
        return *this;
    }
    ABS(ABS&& other) noexcept {
        this->capacity__ = other.capacity__;
        this->curr_size__ = other.curr_size__;
        this->array_ = other.array_;

        other.capacity__ = 0;
        other.curr_size__ = 0;
        other.array_ = nullptr;
    }
    ABS& operator=(ABS&& rhs) noexcept {
        if (this == &rhs) {
            return *this;
        }
        delete[] this->array_;
        this->capacity__ = rhs.capacity__;
        this->curr_size__ = rhs.curr_size__;
        this->array_ = rhs.array_;

        rhs.capacity__ = 0;
        rhs.curr_size__ = 0;
        rhs.array_ = nullptr;

        return *this;
    }
    ~ABS() noexcept override {
        delete[] array_;
        array_ = nullptr;
        capacity__ = 0;
        curr_size__ = 0;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size__;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity__;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

    // Push item onto the stack
    void push(const T& data) override {
        // code/concepts taken from iDynamArray lab
        if (curr_size__ == capacity__) {
            capacity__*=scale_factor_;
            T* temp = new T[capacity__];
            for (size_t i = 0; i < curr_size__; i++) {
                temp[i] = array_[i];
            }
            delete[] array_;
            array_ = temp;
        }
        array_[curr_size__] = data;
        curr_size__++;
    }

    T peek() const override {
        if (curr_size__ == 0) {
            throw std::runtime_error("empty array");
        }
        return array_[curr_size__ - 1];
    }

    T pop() override {
        if (curr_size__ > 0) {
            T tempVal = array_[curr_size__ - 1];
            --curr_size__;
            if (curr_size__ <= capacity__ / 4) {
                capacity__ /= 2;
            }
            T* temp = new T[capacity__];
            for (size_t i = 0; i < curr_size__; i++) {
                    temp[i] = array_[i];
            }
            delete[] array_;
            array_ = temp;
            return tempVal;
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
