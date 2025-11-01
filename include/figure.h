#pragma once
#include "point.h"
#include <memory>
#include <iostream>

template<std::floating_point T>
class Figure {
public:
    virtual ~Figure() = default;

    virtual Point<T> center() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual explicit operator double() const = 0;
    virtual bool operator==(const Figure<T>& other) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
        fig.print(os);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Figure<T>& fig) {
        fig.read(is);
        return is;
    }
};