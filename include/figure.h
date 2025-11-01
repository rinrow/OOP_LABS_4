#pragma once
#include "point.h"
#include <memory>
#include <iostream>
#include <vector>

template<std::floating_point T>
class Figure {
public:
    virtual ~Figure() = default;
    Figure() = default;

    virtual Point<T> center() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual explicit operator double() const = 0;
    virtual bool operator==(const Figure<T>& other) const = 0;

    // Конструктор копирования
    Figure(const Figure& other) : dots(other.dots.size()) {
        for (size_t i = 0; i < other.dots.size(); ++i) {
            if (other.dots[i]) {
                dots[i] = std::make_unique<Point<T>>(*other.dots[i]);
            }
        }
    }

    // Оператор присваивания копированием
    Figure& operator=(const Figure& other) {
        if (this != &other) {
            dots.resize(other.dots.size());
            for (size_t i = 0; i < other.dots.size(); ++i) {
                if (other.dots[i]) {
                    dots[i] = std::make_unique<Point<T>>(*other.dots[i]);
                }
            }
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
        fig.print(os);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Figure<T>& fig) {
        fig.read(is);
        return is;
    }

protected:
    std::vector<std::unique_ptr<Point<T>>> dots;

    // Общие методы для наследников
    Point<T> centerDefault() const {
        T x = 0, y = 0;
        for (const auto& vertex : dots) {
            x += vertex->x();
            y += vertex->y();
        }
        return Point<T>(x / dots.size(), y / dots.size());
    }

    double areaDefault() const {
        if (dots.empty()) return 0.0;
        
        double area = 0.0;
        int n = dots.size();
        for (int i = 0; i < n; ++i) {
            int j = (i + 1) % n;
            area += dots[i]->x() * dots[j]->y() - dots[j]->x() * dots[i]->y();
        }
        return std::abs(area) / 2.0;
    }
};