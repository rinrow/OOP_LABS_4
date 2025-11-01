#pragma once
#include <concepts>
#include <iostream>

template<std::floating_point T>
class Point {
private:
    T x_, y_;

public:
    Point() : x_(0), y_(0) {}
    Point(T x, T y) : x_(x), y_(y) {}

    Point(const Point& other) : x_(other.x_), y_(other.y_) {}

    // Оператор присваивания копированием
    Point& operator=(const Point& other) {
        if (this != &other) {
            x_ = other.x_;
            y_ = other.y_;
        }
        return *this;
    }

    T x() const { return x_; }
    T y() const { return y_; }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << "(" << p.x_ << ", " << p.y_ << ")";
    }

    friend std::istream& operator>>(std::istream& is, Point& p) {
        return is >> p.x_ >> p.y_;
    }

    bool operator==(const Point& other) const {
        return x_ == other.x_ && y_ == other.y_;
    }

    Point operator+(const Point& other) const {
        return Point(x_ + other.x_, y_ + other.y_);
    }

    Point operator/(T divisor) const {
        return Point(x_ / divisor, y_ / divisor);
    }
};