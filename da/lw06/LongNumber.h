//
// Created by Mivallion on 14.03.2018.
//

#ifndef LW06_LONGNUMBER_H
#define LW06_LONGNUMBER_H


#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <iomanip>
class LongNumber {
public:

    explicit LongNumber(uint32_t _number_system, uint32_t _number_size)
    {
        base = _number_system;
        size = 0;
        number_size = _number_size;
    }

    explicit LongNumber(uint32_t _number_system)
    {
        base = _number_system;
        size = 0;
        number_size = 0;
    }

    explicit LongNumber()
    {
        base = 0;
        size = 0;
        numbers.push_back(0);
    }

    uint32_t get_number_size() {
        if (number_size != 0)
            return number_size;
        uint32_t capacity = 0;
        for (int i = 1; i < base; i *= 10) {
            capacity++;
        }
        return capacity;
    }


    ~LongNumber() = default;

    uint32_t get_size() {
        return size;
    }

    uint32_t get_base() {
        return base;
    }

    uint32_t get_number(uint32_t idx)
    {
        return numbers[idx];
    }

    void set_number(uint32_t idx, uint32_t value)
    {
        numbers[idx] = value;
    }

    void resize(uint32_t new_size)
    {
        size = new_size;
        numbers.resize(new_size);
    }

    void input() {
        std::string str;
        std::getline(std::cin, str);
        if(!std::cin)
            throw std::length_error("EOF");
        uint32_t zeros_count = 0;
        for (auto i = str.begin(); *i == '0'; ++i, zeros_count++) {}
        if (zeros_count == str.length())
            zeros_count--;
        str.erase(0, zeros_count);
        size = str.length();
        number_size = get_number_size();
        uint32_t vector_size = size / number_size;
        if (size % number_size != 0)
            vector_size++;
        for (int i = 0; i < vector_size; i++) {
            numbers.push_back(0);
            uint32_t k = 1;
            for (uint32_t j = 0; (i * number_size + j) < size && j < number_size; ++j) {
                numbers[i] += (str[size - i * number_size - j - 1] - '0') * k;
                k = k * 10;
            }
        }
        size = vector_size;
    }

    void clear() {
        size = 0;
        numbers.clear();
    }

    bool empty() {
        return size == 0;
    }

    void print() {
        if (size == 1) {
            std::cout << numbers[0] << std::endl;
            return;
        }
        char s[32];
        for (auto i = numbers.rbegin(); i != numbers.rend(); ++i) {
            int len = sprintf(s, "%d", *i);
            if (i != numbers.rbegin())
                std::cout << std::setfill('0') << std::setw(number_size + 1 - len) <<*i << "|";
            else
                if (*i != 0)
                    std::cout <<*i << "|";
        }
        std::cout << std::endl;
    }
private:
    uint32_t size;
    uint32_t number_size{};
    uint32_t base;
    std::vector<uint32_t> numbers;


};


#endif //LW06_LONGNUMBER_H
