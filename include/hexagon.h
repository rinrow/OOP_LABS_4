#pragma once
#include "figure.h"
#include <cmath>
#include <array>

template<std::floating_point T>
class Hexagon : public Figure<T> {
private:
    std::array<std::unique_ptr<Point<T>>, 6> dots;

    Point<T> calculateVertex(const Point<T>& center, T radius, int ind) {
        T angle = 2 * M_PI * ind / 6;
        return Point<T>(
            center.x() + radius * std::cos(angle),
            center.y() + radius * std::sin(angle)
        );
    }

public:
    Hexagon() = default;

    Hexagon(const Point<T>& center, T radius) {
        for (int i = 0; i < 6; ++i) {
            dots[i] = std::make_unique<Point<T>>(calculateVertex(center, radius, i));
        }
    }

    Hexagon(const Hexagon& other) {
        for (size_t i = 0; i < dots.size(); ++i) {
            if (other.dots[i]) {
                dots[i] = std::make_unique<Point<T>>(*other.dots[i]);
            }
        }
    }

    Hexagon& operator=(const Hexagon& other) {
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
        return Point<T>(x / 6, y / 6);
    }

    void print(std::ostream& os) const override {
        os << "Hexagon vertices: ";
        for (const auto& v : dots) {
            os << *v << " ";
        }
        os << ", Center: " << center() << ", Area: " << static_cast<double>(*this);
    }

    void read(std::istream& is) override {
        Point<T> center;
        T radius;
        std::cout << "Enter hexagon center (x y): ";
        is >> center;
        std::cout << "Enter radius: ";
        is >> radius;
        
        *this = Hexagon(center, radius);
    }

    explicit operator double() const override {
        T side = std::sqrt(std::pow(dots[0]->x() - dots[1]->x(), 2) + 
                          std::pow(dots[0]->y() - dots[1]->y(), 2));
        return static_cast<double>(3 * std::sqrt(3) * side * side / 2);
    }

    bool operator==(const Figure<T>& other) const override {
        const Hexagon* other_hexagon = dynamic_cast<const Hexagon*>(&other);
        if (!other_hexagon) return false;
        
        for (size_t i = 0; i < 6; ++i) {
            if (*dots[i] != *other_hexagon->dots[i]) return false;
        }
        return true;
    }
};