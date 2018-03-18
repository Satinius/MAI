//
// Created by Mivallion on 14.03.2018.
//

#ifndef LW06_LONGARITHMETIC_H
#define LW06_LONGARITHMETIC_H

#include <stdexcept>
#include <cstdlib>
#include "LongNumber.h"

class LongArithmetic {
public:
    static LongNumber * sum(LongNumber *a, LongNumber *b);
    static LongNumber * sub(LongNumber *a, LongNumber *b);
    static LongNumber * multiply(LongNumber *a, LongNumber *b);
    static LongNumber * div(LongNumber *a, LongNumber *b);
    static LongNumber * pow(LongNumber *a, LongNumber *b);

    static bool equal(LongNumber *a, LongNumber *b);
    static bool greater(LongNumber *a, LongNumber *b);
    static bool lower(LongNumber *a, LongNumber *b);


private:
    static int8_t cmp(LongNumber *a, LongNumber *b);
    static LongNumber * zero();
    static bool is_zero(LongNumber * a);
    static bool is_one(LongNumber * a);
};


#endif //LW06_LONGARITHMETIC_H
