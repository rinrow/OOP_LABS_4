#pragma once
#include "figure.h"
#include <cmath>

template<std::floating_point T>
class Rhombus : public Figure<T> {
public:
    Rhombus() = default;

    Rhombus(const Point<T>& center, T horizontal_diagonal, T vertical_diagonal) {
        this->dots.resize(4);
        this->dots[0] = std::make_unique<Point<T>>(center.x(), center.y() + vertical_diagonal / 2);
        this->dots[1] = std::make_unique<Point<T>>(center.x() + horizontal_diagonal / 2, center.y());
        this->dots[2] = std::make_unique<Point<T>>(center.x(), center.y() - vertical_diagonal / 2);
        this->dots[3] = std::make_unique<Point<T>>(center.x() - horizontal_diagonal / 2, center.y());
    }

    Point<T> center() const override {
        return this->centerDefault();
    }

    void print(std::ostream& os) const override {
        os << "Rhombus vertices: ";
        for (const auto& vertex : this->dots) {
            os << *vertex << " ";
        }
        os << ", Center: " << this->center() << ", Area: " << static_cast<double>(*this);
    }

    void read(std::istream& is) override {
        Point<T> center;
        T horizontal, vertical;
        std::cout << "Enter rhombus center (x y): ";
        is >> center;
        std::cout << "Enter horizontal diagonal length: ";
        is >> horizontal;
        std::cout << "Enter vertical diagonal length: ";
        is >> vertical;
        
        *this = Rhombus(center, horizontal, vertical);
    }

    explicit operator double() const override {
        return this->areaDefault();
    }

    bool operator==(const Figure<T>& other) const override {
        const Rhombus* other_rhombus = dynamic_cast<const Rhombus*>(&other);
        if (!other_rhombus || this->dots.size() != other_rhombus->dots.size()) {
            return false;
        }
        
        for (size_t i = 0; i < this->dots.size(); ++i) {
            if (*this->dots[i] != *other_rhombus->dots[i]) return false;
        }
        return true;
    }
};