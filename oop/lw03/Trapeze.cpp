#include "stdafx.h"
#include <iostream>
#include <cmath>
#include "Trapeze.h"


Trapeze::Trapeze():Trapeze(0, 0, 0, 0)
{
}

Trapeze::Trapeze(double i, double j, double k, double l) : side_a(i), side_b(j),
 														   side_c(k), side_d(l)
{
	//std::cout << "Trapeze created: " << side_a << ", " << side_b << ", " <<
	// side_c << ", " << side_d << std::endl;
	if (side_a > side_b)
 		std::swap(side_a, side_b);
 	if (side_a < 0 || side_b < 0 || side_c < 0 || side_d < 0) {
 		std::cerr << "Error: sides must be >= 0." << std::endl;
 		side_a = 0;
 		side_b = 0;
 		side_c = 0;
 		side_d = 0;
 	}
}

Trapeze::Trapeze(std::istream& is)
{
	is >> side_a;
	is >> side_b;
	is >> side_c;
	is >> side_d;
	if (side_a > side_b)
		std::swap(side_a, side_b);
	if (side_a < 0 || side_b < 0 || side_c < 0 || side_d < 0) {
		std::cerr << "Error: sides must be >= 0." << std::endl;
		side_a = 0;
		side_b = 0;
		side_c = 0;
		side_d = 0;
	}
}

Trapeze::Trapeze(const Trapeze& orig)
{
	side_a = orig.side_a;
	side_b = orig.side_b;
	side_c = orig.side_c;
	side_d = orig.side_d;
	std::cout << "Trapeze copy created." << std::endl;
}

double Trapeze::Square()
{
	if (side_a + side_b + side_c > side_d && side_a + side_b + side_d > side_c &&
		side_a + side_c + side_d > side_b)
		return (side_a + side_b) / 2 * sqrt(side_c * side_c -
			pow((pow((side_b - side_a), 2) + side_c * side_c - side_d * side_d)/
			(2 * (side_b - side_a)), 2));
	else {
		std::cout << "This figure is not trapeze." << std::endl;
		return 0;
	}
}

void Trapeze::Print()
{
	std::cout << "a = " << side_a << " b = " << side_b << " c = " << side_c
	<< " d = " << side_d << std::endl;
}

Trapeze::~Trapeze()
{
	//std::cout << "Trapeze deleted." << std::endl;
}

std::ostream & operator<<(std::ostream & os, const Trapeze & right)
{
	os << "Trapeze with side a = " << right.side_a << ", side b = " << right.side_b << ", side c = " << right.side_c << ", side d = " << right.side_c;
	return os;
}
