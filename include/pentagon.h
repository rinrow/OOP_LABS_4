#pragma once
#include "figure.h"
#include <cmath>
#include <array>

template<std::floating_point T>
class Pentagon : public Figure<T> {
private:
    std::array<std::unique_ptr<Point<T>>, 5> dots;

    Point<T> calculateVertex(const Point<T>& center, T radius, int ind) {
        T angle = 2 * M_PI * ind / 5;
        return Point<T>(
            center.x() + radius * std::cos(angle),
            center.y() + radius * std::sin(angle)
        );
    }

public:
    Pentagon() = default;

    Pentagon(const Point<T>& center, T radius) {
        for (int i = 0; i < 5; ++i) {
            dots[i] = std::make_unique<Point<T>>(calculateVertex(center, radius, i));
        }
    }

    Pentagon(const Pentagon& other) {
        for (size_t i = 0; i < dots.size(); ++i) {
            if (other.dots[i]) {
                dots[i] = std::make_unique<Point<T>>(*other.dots[i]);
            }
        }
    }

    Pentagon& operator=(const Pentagon& other) {
        if (this != &other) {
            for (size_t i = 0; i < dots.size(); ++i) {
                if (other.dots[i]) {
                    dots[i] = std::make_unique<Point<T>>(*other.dots[i]);
                }
            }
        }
        return *this;
    }

    Point<T> center() const override {
        T x = 0, y = 0;
        for (const auto& v : dots) {
            x += v->x();
            y += v->y();
        }
        return Point<T>(x / 5, y / 5);
    }

    void print(std::ostream& os) const override {
        os << "Pentagon vertices: ";
        for (const auto& v : dots) {
            os << *v << " ";
        }
        os << ", Center: " << center() << ", Area: " << static_cast<double>(*this);
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
        T side = std::sqrt(std::pow(dots[0]->x() - dots[1]->x(), 2) + 
                          std::pow(dots[0]->y() - dots[1]->y(), 2));
        return static_cast<double>(0.25 * std::sqrt(5 * (5 + 2 * std::sqrt(5))) * side * side);
    }

    bool operator==(const Figure<T>& other) const override {
        const Pentagon* other_pentagon = dynamic_cast<const Pentagon*>(&other);
        if (!other_pentagon) return false;
        
        for (size_t i = 0; i < 5; ++i) {
            if (*dots[i] != *other_pentagon->dots[i]) return false;
        }
        return true;
    }
};