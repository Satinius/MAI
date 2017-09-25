#include <iostream>
#include <cmath>
#include "Rectangle.h"

Rectangle::Rectangle() : Rectangle(0, 0)
{
}

Rectangle::Rectangle(double i, double j) : side_a(i), side_b(j)
{
	std::cout << "Rectangle created: " << side_a << ", " << side_b << std::endl;
}

Rectangle::Rectangle(std::istream &is)
{
	is >> side_a;
	is >> side_b;
	if (side_a < 0 || side_b < 0) {
		std::cerr << "Error: sides must be >= 0." << std::endl;
		side_a = 0;
		side_b = 0;
	}
}

Rectangle::Rectangle(const Rectangle& orig)
{
	std::cout << "Rectangle copy created." << std::endl;
	side_a = orig.side_a;
	side_b = orig.side_b;
	if (side_a < 0 || side_b < 0) {
		std::cerr << "Error: sides must be >= 0." << std::endl;
		side_a = 0;
		side_b = 0;
	}
}

double Rectangle::Square()
{
	return side_a * side_b;
}

void Rectangle::Print()
{
	std::cout << "a = " << side_a << " b = " << side_b << std::endl;
}

Rectangle::~Rectangle()
{
	std::cout << "Rectangle deleted." << std::endl;
}
