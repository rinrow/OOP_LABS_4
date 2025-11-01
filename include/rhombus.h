#pragma once
#include "figure.h"
#include <cmath>
#include <array>

template<std::floating_point T>
class Rhombus : public Figure<T> {
private:
    std::array<std::unique_ptr<Point<T>>, 4> dots;

public:
    Rhombus() = default;

    Rhombus(const Point<T>& center, T horizontal_diagonal, T vertical_diagonal) {
        dots[0] = std::make_unique<Point<T>>(center.x(), center.y() + vertical_diagonal / 2);
        dots[1] = std::make_unique<Point<T>>(center.x() + horizontal_diagonal / 2, center.y());
        dots[2] = std::make_unique<Point<T>>(center.x(), center.y() - vertical_diagonal / 2);
        dots[3] = std::make_unique<Point<T>>(center.x() - horizontal_diagonal / 2, center.y());
    }

    Rhombus(const Rhombus& other) {
        for (size_t i = 0; i < dots.size(); ++i) {
            if (other.dots[i]) {
                dots[i] = std::make_unique<Point<T>>(*other.dots[i]);
            }
        }
    }

    Rhombus& operator=(const Rhombus& other) {
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
        return Point<T>(x / 4, y / 4);
    }

    void print(std::ostream& os) const override {
        os << "Rhombus vertices: ";
        for (const auto& v : dots) {
            os << *v << " ";
        }
        os << ", Center: " << center() << ", Area: " << static_cast<double>(*this);
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
        T d1 = std::sqrt(std::pow(dots[0]->x() - dots[2]->x(), 2) + 
                         std::pow(dots[0]->y() - dots[2]->y(), 2));
        T d2 = std::sqrt(std::pow(dots[1]->x() - dots[3]->x(), 2) + 
                         std::pow(dots[1]->y() - dots[3]->y(), 2));
        return static_cast<double>(d1 * d2 / 2);
    }

    bool operator==(const Figure<T>& other) const override {
        const Rhombus* other_rhombus = dynamic_cast<const Rhombus*>(&other);
        if (!other_rhombus) return false;
        
        for (size_t i = 0; i < 4; ++i) {
            if (*dots[i] != *other_rhombus->dots[i]) return false;
        }
        return true;
    }
};