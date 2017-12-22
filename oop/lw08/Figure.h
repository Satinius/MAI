#ifndef FIGURE_H
#define FIGURE_H

class Figure {
public:
	virtual double square() = 0;
	virtual void print() = 0;
	virtual ~Figure() {};
};

#endif // !FIGURE_H
