// lw07.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cstdlib>
#include <iostream>
#include <memory>

#include "Rectangle.h"
#include "Tree.h"
#include "Vector.h"
#include "IRemoveCriteriaAll.h"
#include "IRemoveCriteriaByValue.h"

int main()
{
	Vector<Tree<Rectangle>, Rectangle> vec;
	vec.insertSubitem(std::make_shared<Rectangle>(1, 1), 1, 1);
	vec.insertSubitem(std::make_shared<Rectangle>(2, 1), 2, 1);
	vec.insertSubitem(std::make_shared<Rectangle>(3, 1), 3, 1);
	vec.insertSubitem(std::make_shared<Rectangle>(4, 1), 4, 1);
	vec.insertSubitem(std::make_shared<Rectangle>(5, 1), 5, 1);
	vec.insertSubitem(std::make_shared<Rectangle>(6, 1), 2, 1);
	vec.insertSubitem(std::make_shared<Rectangle>(7, 1), 2, 2);
	vec.insertSubitem(std::make_shared<Rectangle>(8, 1), 3, 2);

	vec.print();

	IRemoveCriteriaByValue<Rectangle> criteria(Rectangle(4, 1));
	IRemoveCriteriaAll<Rectangle> criteriaAll();
	
	vec.removeSubitem(&criteria);

	system("pause");
	
    return 0;
}

