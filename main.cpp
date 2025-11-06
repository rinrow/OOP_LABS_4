#include <iostream>
#include <memory>
#include <typeinfo>
#include "./include/rhombus.h"
#include "./include/pentagon.h"
#include "./include/hexagon.h"
#include "./include/array.h"

template<typename T>
void print_figures_info(Array<std::shared_ptr<Figure<T>>>& figures) {
    double total_area = 0.0;
    
    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << "Figure " << i << ": " << *figures[i] << std::endl;
        total_area += static_cast<double>(*figures[i]);
    }

    std::cout << "Total area: " << total_area << std::endl << std::endl;
}

int main() {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    int choice;
    do {
        std::cout << "1. Add Rhombus\n";
        std::cout << "2. Add Pentagon\n";
        std::cout << "3. Add Hexagon\n";
        std::cout << "4. Print all figures\n";
        std::cout << "5. Delete figure by index\n";
        std::cout << "6. Calculate total area\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                auto rhombus = std::make_shared<Rhombus<double>>();
                std::cin >> *rhombus;
                figures.push_back(std::move(rhombus));
                break;
            }
            case 2: {
                auto pentagon = std::make_shared<Pentagon<double>>();
                std::cin >> *pentagon;
                figures.push_back(std::move(pentagon));
                break;
            }
            case 3: {
                auto hexagon = std::make_shared<Hexagon<double>>();
                std::cin >> *hexagon;
                figures.push_back(std::move(hexagon));
                break;
            }
            case 4:
                print_figures_info(figures);
                break;
            case 5: {
                size_t index;
                std::cout << "Enter index to delete: ";
                std::cin >> index;
                try {
                    figures.erase(index);
                    std::cout << "Figure deleted successfully\n";
                } catch (const std::out_of_range& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case 6: {
                double total_area = 0.0;
                for (size_t i = 0; i < figures.size(); ++i) {
                    total_area += static_cast<double>(*figures[i]);
                }
                std::cout << "Total area of all figures: " << total_area << std::endl;
                break;
            }
        }
    } while (choice != 0);
    
    // Демонстрация работы с Array для разных типов
    // std::cout << "\n--- Testing Array with different types ---\n";

    // Figure<int> ff; Ошибка!

    Array<Rhombus<double>> rhombus_array;
    rhombus_array.push_back(Rhombus<double>(Point<double>(0, 0), 4, 6));
    
    Array<std::shared_ptr<Figure<double>>> figure_ptr_array;
    figure_ptr_array.push_back(std::make_shared<Rhombus<double>>(Point<double>(1, 1), 3, 5));
    return 0;
}