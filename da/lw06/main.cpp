#include <iostream>
#include "LongArithmetic.h"
#include "LongNumber.h"

int main() {
    auto a = new LongNumber(10000);
    auto b = new LongNumber(10000);
    char operation;
    bool cont = true;
    while (cont) {
        try {
            a->input();
            b->input();
            std::cin >> operation;
            std::cin.ignore();
            if (operation == '+') {
                LongArithmetic::sum(a, b)->print();
            } else if (operation == '-') {
                LongArithmetic::sub(a, b)->print();
            } else if (operation == '*') {
                LongArithmetic::multiply(a, b)->print();
            } else if (operation == '/') {
                LongArithmetic::div(a, b)->print();
            } else if (operation == '^') {
                LongArithmetic::pow(a, b)->print();
            } else if (operation  == '>') {
                std::cout << (LongArithmetic::greater(a, b) ? "True" : "False") << std::endl;
            } else if (operation  == '=') {
                std::cout << (LongArithmetic::equal(a, b) ? "True" : "False") << std::endl;
            } else if (operation  == '<') {
                std::cout << (LongArithmetic::lower(a, b) ? "True" : "False") << std::endl;
            }
            a->clear();
            b->clear();
        }
        catch (const std::length_error& e) {
            cont = false;
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Error" << std::endl;
            a->clear();
            b->clear();
        }
    }
    return 0;
}