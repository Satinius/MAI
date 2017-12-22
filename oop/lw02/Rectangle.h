#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Rectangle : public Figure
{
public:
	Rectangle();
	Rectangle(size_t side_a, size_t side_b);
	Rectangle(const Rectangle& orig);
	size_t Square() override;
	void print() override;
	friend std::ostream& operator<<(std::ostream& os, const Rectangle& right);
	friend std::istream& operator>>(std::istream& is, Rectangle& right);
	friend bool operator==(const Rectangle& left, const Rectangle& right);
	Rectangle& operator=(const Rectangle& right);
	virtual ~Rectangle();
private:
	size_t side_a;
	size_t side_b;
};
#endif // !RECTANGLE_H
