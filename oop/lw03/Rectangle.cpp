#include "stdafx.h"
#include <iostream>
#include <cmath>
#include "Rectangle.h"

Rectangle::Rectangle() : Rectangle(0, 0)
{
}

Rectangle::Rectangle(size_t i, size_t j) : side_a(i), side_b(j)
{
	//std::cout << "Rectangle created: " << side_a << ", " << side_b << std::endl;
}


Rectangle::Rectangle(const Rectangle& orig)
{
	//std::cout << "Rectangle copy created." << std::endl;
	side_a = orig.side_a;
	side_b = orig.side_b;
}

double Rectangle::Square()
{
	return side_a * side_b;
}

void Rectangle::Print()
{
	std::cout << "Rectangle with side a = " << side_a << ", side b = " << side_b << " square = " << this->Square() << std::endl;
}

Rectangle & Rectangle::operator=(const Rectangle & right)
{
	if (this == &right)
		return *this;
	//std::cout << "Rectangle copy created." << std::endl;
	side_a = right.side_a;
	side_b = right.side_b;
	
	return *this;
}

Rectangle::~Rectangle()
{
	//std::cout << "Rectangle deleted." << std::endl;
}


std::ostream & operator<<(std::ostream & os, const Rectangle & obj)
{
	os << "Rectangle with side a = " << obj.side_a << ", side b = " << obj.side_b;
	return os;
}

std::istream & operator>>(std::istream & is, Rectangle & right)
{
	is >> right.side_a;
	is >> right.side_b;
	if (right.side_a < 0 || right.side_b < 0) {
		std::cerr << "Error: sides must be >= 0." << std::endl;
		right.side_a = 0;
		right.side_b = 0;
	}
	return is;
}

bool operator==(const Rectangle & left, const Rectangle &right)
{
	return (left.side_a == right.side_a && left.side_b == right.side_b);
}
