#ifndef RHOMBUS_H
#define RHOMBUS_H
#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Rhombus : public Figure
{
public:
	Rhombus();
	Rhombus(double side_a, double side_b);
	Rhombus(std::istream &is);
	Rhombus(const Rhombus& orig);

	double Square() override;
	void Print() override;

	virtual ~Rhombus();
private:
	double side_a;
	double side_b;
};
#endif // !RECTANGLE_H
