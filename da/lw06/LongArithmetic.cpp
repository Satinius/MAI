//
// Created by Mivallion on 14.03.2018.
//


#include "LongArithmetic.h"


int8_t LongArithmetic::cmp(LongNumber *a, LongNumber *b) {
    auto a_size = a->get_size();
    auto b_size = b->get_size();
    if (a_size != b_size) {
        return static_cast<int8_t>(a_size < b_size ? 1 : 2);
    }
    for (int i = a_size - 1; i >= 0; --i) {
        uint32_t cur_a = a->get_number(i);
        uint32_t cur_b = b->get_number(i);
        if (cur_a != cur_b) {
            return static_cast<int8_t>(cur_a < cur_b ? 1 : 2);
        }
    }
    return 0;
}

bool LongArithmetic::equal(LongNumber *a, LongNumber *b) {
    return cmp(a, b) == 0;
}

bool LongArithmetic::greater(LongNumber *a, LongNumber *b) {
    return cmp(a, b) == 2;
}

bool LongArithmetic::lower(LongNumber * a, LongNumber * b) {
    return cmp(a, b) == 1;
}

LongNumber * LongArithmetic::sub(LongNumber *a, LongNumber *b) {
    if (lower(a, b))
        throw std::invalid_argument("a is lower than b");
    uint32_t k = 0;
    uint32_t a_size = a->get_size();
    uint32_t b_size = b->get_size();
    uint32_t base = a->get_base();
    auto c = new LongNumber(base, a->get_number_size());
    c->resize(a_size);

    uint32_t i;
    for (i = 0; i < b_size; i++) {
        int32_t tmp = a->get_number(i) - b->get_number(i) - k;
        if (tmp < 0) {
            k = 1;
            tmp += base;
        } else {
            k = 0;
        }
        c->set_number(i, tmp);
    }
    for (; i < a_size; i++) {
        c->set_number(i, a->get_number(i) - k);
        k = 0;
    }
    return c;
}

LongNumber * LongArithmetic::sum(LongNumber *a, LongNumber *b) {
    uint32_t k = 0;
    uint32_t n = std::max(a->get_size(), b->get_size());
    uint32_t base = a->get_base();
    auto c = new LongNumber(base, a->get_number_size());
    c->resize(n + 1);
    for (uint32_t i = 0; i < n; i++) {
        uint32_t tmp = a->get_number(i) + b->get_number(i) + k;
        k = tmp / base;
        tmp %= base;
        c->set_number(i, tmp);
    }
    if (k > 0) {
        c->set_number(n, k);
    }
    return c;
}

LongNumber * LongArithmetic::multiply(LongNumber *a, LongNumber *b) {
    uint32_t k = 0;
    uint32_t base = a->get_base();
    auto c = new LongNumber(base, a->get_number_size());
    if (is_zero(a) || is_zero(b)) {
        c->clear();
        c->resize(1);
        return c;
    }
    if (is_one(a))
        return b;
    if (is_one(b))
        return a;
    uint32_t a_size = a->get_size();
    uint32_t b_size = b->get_size();
    c->resize(a_size + b_size + 1);
    for (size_t i = 0; i < a_size; i++) {
        k = 0;
        for (size_t j = 0; j < b_size || k; ++j) {
            uint32_t cur = c->get_number(i + j) + a->get_number(i) * (j < b_size ? b->get_number(j) : 0) + k;
            c->set_number(i + j, cur % base);
            k = cur / base;
        }
    }

    return c;
}

LongNumber * LongArithmetic::div(LongNumber *a, LongNumber *b) {

    if (is_zero(b))
        throw std::invalid_argument("divide by zero");
    //uint32_t k = 0;
    uint32_t base = a->get_base();
    uint32_t a_size = a->get_size();
    uint32_t b_size = b->get_size();

    auto cur = new LongNumber(base);
    auto res = new LongNumber(base);

    for (size_t i = a_size - 1; i >= 0; i--) {
        cur->resize(1);
        cur->set_number(0, a->get_number(i));

        uint32_t x = 0, l = 0, r = base;
    }

    return zero();
}

LongNumber * LongArithmetic::pow(LongNumber *a, LongNumber *b) {
    if (is_zero(a) && is_zero(b))
        throw std::invalid_argument("zero in pow zero");

    uint32_t base = a->get_base();
    auto c = new LongNumber(base, a->get_number_size());

    if (is_zero(a)) {
        c->clear();
        c->resize(1);
        return c;
    }
    if (is_zero(b)) {
        c->clear();
        c->resize(1);
        c->set_number(0, 1);
        return c;
    }

    return c;
}

LongNumber * LongArithmetic::zero() {
    return new LongNumber();
}

bool LongArithmetic::is_zero(LongNumber * a) {
    return a->get_size() == 1 && a->get_number(0) == 0;
}

bool LongArithmetic::is_one(LongNumber *a) {
    return (a->get_size() == 1 && a->get_number(0) == 1);
}
