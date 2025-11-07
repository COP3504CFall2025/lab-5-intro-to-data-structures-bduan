#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() : list(LinkedList()){}

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.addHead(item);
    }
    void pushBack(const T& item) override {
        list.addTail(item);
    }

    // Core Removal Operations - remember to throw error if there is nothing to pop
    T popFront() override {
        if (list.getHead() == nullptr) {
            throw std::runtime_error("Nothing to pop");
        }
        else {
            T temp = list.getHead();
            list.removeHead();
            return temp;
        }
    }
    T popBack() override {
        if (list.getTail() == nullptr) {
            throw std::runtime_error("Nothing to pop");
        }
        else {
            T temp = list.getTail();
            list.removeTail();
            return temp;
        }
    }

    // Element Accessors
    const T& front() const override {
        return list.getHead();
    }
    const T& back() const override {
        return list.getTail();
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};






