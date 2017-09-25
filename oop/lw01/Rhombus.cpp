#include <iostream>
#include <cmath>
#include "Rhombus.h"

Rhombus::Rhombus() : Rhombus(0, 0)
{
}

Rhombus::Rhombus(double i, double j) : side_a(i), side_b(j)
{
	std::cout << "Rhombus created: " << side_a << ", " << side_b << std::endl;
}

Rhombus::Rhombus(std::istream &is)
{
	is >> side_a;
	is >> side_b;
	if (side_a < 0 || side_b < 0) {
		std::cerr << "Error: sides must be >= 0." << std::endl;
		side_a = 0;
		side_b = 0;
	}
}

Rhombus::Rhombus(const Rhombus& orig)
{
	std::cout << "Rhombus copy created." << std::endl;
	side_a = orig.side_a;
	side_b = orig.side_b;
	if (side_a < 0 || side_b < 0) {
		std::cerr << "Error: sides must be >= 0." << std::endl;
		side_a = 0;
		side_b = 0;
	}
}

double Rhombus::Square()
{
	return side_a * side_b / 2;
}

void Rhombus::Print()
{
	std::cout << "a = " << side_a << " b = " << side_b << std::endl;
}

Rhombus::~Rhombus()
{
	std::cout << "Rhombus deleted." << std::endl;
}
