#include "stdafx.h"
#include <iostream>
#include <string>

#include "Tree.h"
#include "Rectangle.h"
#include "Trapeze.h"
#include "Rhombus.h"

int main(int argc, char** argv)
{
	Tree<Rectangle> *tree = new Tree<Rectangle>();
	std::string action;

	std::cout << "Type 'h' or 'help' to get help." << std::endl;
	while (!std::cin.eof()) {
		std::cin.clear();
		std::cin.sync();
		std::cin >> action;

		if (action == "q" || action == "quit") {
			break;
		}
		else if (action == "insert" || action == "ins") {
			std::cout << "Enter 2 rectangle sides, element key, parent key: " << std::endl;
			size_t rectangle_side_a, rectangle_side_b, new_key, ins_key;
			if (!(std::cin >> rectangle_side_a >> rectangle_side_b >> new_key >> ins_key)) {
				std::cout << "Incorrect value." << std::endl;
				continue;
			}
			tree->insert(std::shared_ptr<TreeItem<Rectangle>>(new TreeItem<Rectangle>(std::shared_ptr<Rectangle>(new Rectangle(rectangle_side_a, rectangle_side_b)), new_key)), ins_key);
		}
		else if (action == "remove" || action == "r") {
			size_t square;
			if (!(std::cin >> square) && square >= 0) {
				std::cout << "Incorrect value." << std::endl;
				continue;
			}
			tree->remove(square);
		}

		else if (action == "destroy" || action == "d") {
			delete tree;
			tree = new Tree<Rectangle>();
			std::cout << "The tree was deleted." << std::endl;
		}
		else if (action == "print" || action == "p") {
			if (!tree->empty()) {
				tree->Print();
			}
			else {
				std::cout << "The tree is empty." << std::endl;
			}
		}
		else if (action == "help" || action == "h") {
			std::cout << "'q' or 'quit' - exit the program." << std::endl;
			std::cout << "'r' or 'remove s' - remove the rectangle with area s." << std::endl;
			std::cout << "'d' or 'destroy' - delete the tree." << std::endl;
			std::cout << "'p' or 'print' - output the tree." << std::endl;
			std::cout << "'ins' or 'insert s' - insert a rectangle into the tree." << std::endl;
			std::cout << "'h 'or' help '- display the help." << std::endl;
		}
		action = " ";
	}

	delete tree;
	system("pause");
	return 0;
}

