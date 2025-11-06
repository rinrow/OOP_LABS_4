#pragma once
#include "figure.h"
#include <cmath>

template<std::floating_point T>
class Hexagon : public Figure<T> {
private: 
    Point<T> calculateVertex(const Point<T>& center, T radius, int index) {
        T angle = 2 * M_PI * index / 6;
        return Point<T>(
            center.x() + radius * std::cos(angle),
            center.y() + radius * std::sin(angle)
        );
    }
public:
    Hexagon() = default;

    Hexagon(const Point<T>& center, T radius) {
        this->dots.resize(6);
        for (int i = 0; i < 6; ++i) {
            this->dots[i] = std::make_unique<Point<T>>(calculateVertex(center, radius, i));
        }
    }

    Point<T> center() const override {
        return this->centerDefault();
    }

    void print(std::ostream& os) const override {
        os << "Hexagon vertices: ";
        for (const auto& vertex : this->dots) {
            os << *vertex << " ";
        }
        os << ", Center: " << this->center() << ", Area: " << static_cast<double>(*this);
    }

    void read(std::istream& is) override {
        std::cout << " Enter Hexagon: 6 points\n";
        this->readPoints(is, 6);
        std::cout << "Hexagon created successfully!\n";
    }

    explicit operator double() const override {
        return this->areaDefault();
    }

    bool operator==(const Figure<T>& other) const override {
        const Hexagon* other_hexagon = dynamic_cast<const Hexagon*>(&other);
        if (!other_hexagon || this->dots.size() != other_hexagon->dots.size()) {
            return false;
        }
        
        for (size_t i = 0; i < this->dots.size(); ++i) {
            if (*this->dots[i] != *other_hexagon->dots[i]) return false;
        }
        return true;
    }
};