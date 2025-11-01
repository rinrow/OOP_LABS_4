#include <gtest/gtest.h>
#include "../include/point.h"
#include "../include/figure.h"
#include "../include/rhombus.h"
#include "../include/pentagon.h"
#include "../include/hexagon.h"
#include "../include/array.h"
#include <cmath>
#include <memory>
#include <sstream>

// ==================== ТЕСТЫ ДЛЯ POINT ====================

TEST(PointTest, DefaultConstructor) {
    Point<double> p;
    EXPECT_DOUBLE_EQ(p.x(), 0.0);
    EXPECT_DOUBLE_EQ(p.y(), 0.0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<double> p(3.5, 2.7);
    EXPECT_DOUBLE_EQ(p.x(), 3.5);
    EXPECT_DOUBLE_EQ(p.y(), 2.7);
}

TEST(PointTest, EqualityOperator) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(1.0, 2.0);
    Point<double> p3(1.0, 3.0);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(PointTest, StreamOutput) {
    Point<double> p(1.5, 2.5);
    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "(1.5, 2.5)");
}

// ==================== ТЕСТЫ ДЛЯ RHOMBUS ====================

TEST(RhombusTest, ConstructorAndArea) {
    Rhombus<double> rhombus(Point<double>(0, 0), 4.0, 6.0);
    
    // Проверяем площадь (d1 * d2 / 2 = 4 * 6 / 2 = 12)
    EXPECT_DOUBLE_EQ(static_cast<double>(rhombus), 12.0);
}

TEST(RhombusTest, CenterCalculation) {
    Rhombus<double> rhombus(Point<double>(2, 3), 4.0, 6.0);
    auto center = rhombus.center();
    
    EXPECT_DOUBLE_EQ(center.x(), 2.0);
    EXPECT_DOUBLE_EQ(center.y(), 3.0);
}

// ==================== ТЕСТЫ ДЛЯ PENTAGON ====================

TEST(PentagonTest, ConstructorAndArea) {
    Pentagon<double> pentagon(Point<double>(0, 0), 1.0);
    double area = static_cast<double>(pentagon);
    
    // Площадь должна быть положительной
    EXPECT_GT(area, 0.0);
}

TEST(PentagonTest, CenterCalculation) {
    Pentagon<double> pentagon(Point<double>(5, 5), 2.0);
    auto center = pentagon.center();
    
    EXPECT_DOUBLE_EQ(center.x(), 5.0);
    EXPECT_DOUBLE_EQ(center.y(), 5.0);
}

// ==================== ТЕСТЫ ДЛЯ HEXAGON ====================

TEST(HexagonTest, ConstructorAndArea) {
    Hexagon<double> hexagon(Point<double>(0, 0), 1.0);
    double area = static_cast<double>(hexagon);
    
    // Площадь должна быть положительной
    EXPECT_GT(area, 0.0);
}

TEST(HexagonTest, CenterCalculation) {
    Hexagon<double> hexagon(Point<double>(3, 4), 2.0);
    auto center = hexagon.center();
    
    EXPECT_DOUBLE_EQ(center.x(), 3.0);
    EXPECT_DOUBLE_EQ(center.y(), 4.0);
}

// ==================== ТЕСТЫ ДЛЯ ARRAY ====================

TEST(ArrayTest, DefaultConstructor) {
    Array<int> arr;
    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr.capacity(), 0);
    EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, PushBackAndAccess) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, EraseElement) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    
    arr.erase(1); // Удаляем второй элемент
    
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
}

TEST(ArrayTest, OutOfRangeAccess) {
    Array<int> arr;
    arr.push_back(1);
    
    EXPECT_THROW(arr[1], std::out_of_range);
    EXPECT_THROW(arr[100], std::out_of_range);
}

TEST(ArrayTest, EraseOutOfRange) {
    Array<int> arr;
    arr.push_back(1);
    
    EXPECT_THROW(arr.erase(1), std::out_of_range);
    EXPECT_THROW(arr.erase(100), std::out_of_range);
}

TEST(ArrayTest, WithFigures) {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    auto rhombus = std::make_shared<Rhombus<double>>(Point<double>(0, 0), 4.0, 6.0);
    auto pentagon = std::make_shared<Pentagon<double>>(Point<double>(0, 0), 1.0);
    auto hexagon = std::make_shared<Hexagon<double>>(Point<double>(0, 0), 1.0);
    
    figures.push_back(std::move(rhombus));
    figures.push_back(std::move(pentagon));
    figures.push_back(std::move(hexagon));
    
    EXPECT_EQ(figures.size(), 3);
    
    // Проверяем, что фигуры создались корректно
    EXPECT_GT(static_cast<double>(*figures[0]), 0);
    EXPECT_GT(static_cast<double>(*figures[1]), 0);
    EXPECT_GT(static_cast<double>(*figures[2]), 0);
}

// ==================== ТЕСТЫ НА ПОЛИМОРФИЗМ ====================

TEST(PolymorphismTest, FigurePointers) {
    std::shared_ptr<Figure<double>> rhombus = 
        std::make_shared<Rhombus<double>>(Point<double>(0, 0), 4.0, 6.0);
    std::shared_ptr<Figure<double>> pentagon = 
        std::make_shared<Pentagon<double>>(Point<double>(0, 0), 1.0);
    std::shared_ptr<Figure<double>> hexagon = 
        std::make_shared<Hexagon<double>>(Point<double>(0, 0), 1.0);
    
    // Проверяем, что можем вызывать виртуальные методы через базовый указатель
    EXPECT_NO_THROW(rhombus->center());
    EXPECT_NO_THROW(pentagon->center());
    EXPECT_NO_THROW(hexagon->center());
    
    EXPECT_NO_THROW(static_cast<double>(*rhombus));
    EXPECT_NO_THROW(static_cast<double>(*pentagon));
    EXPECT_NO_THROW(static_cast<double>(*hexagon));
}

TEST(PolymorphismTest, TotalAreaCalculation) {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    auto rhombus1 = std::make_shared<Rhombus<double>>(Point<double>(0, 0), 2.0, 2.0); // площадь = 2
    auto rhombus2 = std::make_shared<Rhombus<double>>(Point<double>(0, 0), 4.0, 6.0); // площадь = 12
    
    figures.push_back(std::move(rhombus1));
    figures.push_back(std::move(rhombus2));
    
    double total_area = 0.0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total_area += static_cast<double>(*figures[i]);
    }
    
    EXPECT_NEAR(total_area, 14.0, 0.0001);
}

// ==================== ТЕСТЫ НА ПРЕОБРАЗОВАНИЕ ТИПОВ ====================

TEST(TypeConversionTest, DoubleConversion) {
    Rhombus<double> rhombus(Point<double>(0, 0), 4.0, 6.0);
    double area = static_cast<double>(rhombus);
    
    EXPECT_DOUBLE_EQ(area, 12.0);
    EXPECT_TRUE(area > 0);
}

// ==================== ТЕСТЫ НА ИСКЛЮЧЕНИЯ ====================

TEST(ExceptionTest, ArrayBounds) {
    Array<int> arr;
    
    EXPECT_THROW(arr[0], std::out_of_range);
    EXPECT_THROW(arr.erase(0), std::out_of_range);
    
    arr.push_back(1);
    
    EXPECT_NO_THROW(arr[0]);
    EXPECT_THROW(arr[1], std::out_of_range);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}