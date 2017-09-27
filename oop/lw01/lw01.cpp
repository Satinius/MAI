// lw01.cpp: определяет точку входа для консольного приложения.
//

#include <cstdlib>
#include "Rectangle.h"
#include "Trapeze.h"
#include "Rhombus.h"

// Для прямоугольника задаются просто две стороны
// Для трапеции задается верхняя-нижняя-левая-правая стороны
// Для ромба задаются длины его диагоналей
int main(int argc, char** argv)
{
	std::cout << "Enter sides of rectangle: " << std::endl;
	Figure *rectangle = new Rectangle(std::cin);
	rectangle->Print();
	std::cout << rectangle->Square() << std::endl;
	delete rectangle;

	std::cout << "Enter sides of trapeze: " << std::endl;
	Figure *trapeze = new Trapeze(std::cin);
	trapeze->Print();
	std::cout << trapeze->Square() << std::endl;
	delete trapeze;
	
	std::cout << "Enter diagonales of rhombus: " << std::endl;
	Figure *rhombus = new Rhombus(std::cin);
	rhombus->Print();
	std::cout << rhombus->Square() << std::endl;
	delete rhombus;
    return 0;
}
