#pragma once
#include <memory>
#include <stdexcept>

template<typename T>
class Array {
private:
    std::shared_ptr<T[]> data;
    size_t sz;
    size_t cap;

    void resize(size_t ncap) {
        std::shared_ptr<T[]> nd(std::make_shared<T[]>(ncap));
        
        for (size_t i = 0; i < sz; ++i) {
            nd[i] = std::move(data[i]);
        }
        
        data = std::move(nd);
        cap = ncap;
    }

public:
    Array() : sz(0), cap(0) {}
    
    Array(size_t initial_capacity) : sz(0), cap(initial_capacity) {
        data = std::shared_ptr<T[]>(new T[cap]);
    }

    void push_back(T&& value) {
        if (sz >= cap) {
            resize(cap == 0 ? 1 : cap * 2);
        }
        data[sz++] = std::move(value);
    }

    void erase(size_t index) {
        if (index >= sz) {
            throw std::out_of_range("Index out of range");
        }
        
        for (size_t i = index; i < sz - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --sz;
    }

    T& operator[](size_t index) {
        if (index >= sz) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= sz) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t size() const { return sz; }
    size_t capacity() const { return cap; }
    bool empty() const { return sz == 0; }

    class Iterator {
    private:
        T* ptr_;
    public:
        Iterator(T* ptr) : ptr_(ptr) {}
        T& operator*() { return *ptr_; }
        Iterator& operator++() { ++ptr_; return *this; }
        bool operator!=(const Iterator& other) { return ptr_ != other.ptr_; }
    };

    Iterator begin() { return Iterator(data.get()); }
    Iterator end() { return Iterator(data.get() + sz); }
};