#pragma once
#include "figure.h"
#include <cmath>

template<std::floating_point T>
class Pentagon : public Figure<T> {
private:
    Point<T> calculateVertex(const Point<T>& center, T radius, int index) {
        T angle = 2 * M_PI * index / 5;
        return Point<T>(
            center.x() + radius * std::cos(angle),
            center.y() + radius * std::sin(angle)
        );
    }

public:
    Pentagon() = default;

    Pentagon(const Point<T>& center, T radius) {
        this->dots.resize(5);
        for (int i = 0; i < 5; ++i) {
            this->dots[i] = std::make_unique<Point<T>>(calculateVertex(center, radius, i));
        }
    }

    Point<T> center() const override {
        return this->centerDefault();
    }

    void print(std::ostream& os) const override {
        os << "Pentagon vertices: ";
        for (const auto& vertex : this->dots) {
            os << *vertex << " ";
        }
        os << ", Center: " << this->center() << ", Area: " << static_cast<double>(*this);
    }

    void read(std::istream& is) override {
        Point<T> center;
        T radius;
        std::cout << "Enter pentagon center (x y): ";
        is >> center;
        std::cout << "Enter radius: ";
        is >> radius;
        
        *this = Pentagon(center, radius);
    }

    explicit operator double() const override {
        return this->areaDefault();
    }

    bool operator==(const Figure<T>& other) const override {
        const Pentagon* other_pentagon = dynamic_cast<const Pentagon*>(&other);
        if (!other_pentagon || this->dots.size() != other_pentagon->dots.size()) {
            return false;
        }
        
        for (size_t i = 0; i < this->dots.size(); ++i) {
            if (*this->dots[i] != *other_pentagon->dots[i]) return false;
        }
        return true;
    }
};