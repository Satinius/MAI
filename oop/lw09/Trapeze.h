#ifndef TRAPEZE_H
#define TRAPEZE_H
#include <cstdlib>
#include <iostream>
#include "Figure.h"
class Trapeze :
	public Figure
{
public:
	Trapeze();
	Trapeze(double side_a, double side_b, double side_c, double side_d);
	Trapeze(std::istream &is);
	Trapeze(const Trapeze& orig);

	double square() override;
	void print() override;

	friend std::ostream& operator<<(std::ostream& os, const Trapeze& right);

	virtual ~Trapeze();
private:
	double side_a;
	double side_b;
	double side_c;
	double side_d;
};
#endif
