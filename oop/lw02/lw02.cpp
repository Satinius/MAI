// lw02.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>

#include "tree.h"
#include "rectangle.h"


int main(int argc, char** argv)
{
	Tree *tree = new Tree();
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
			size_t size_a, size_b, key;
			if (!(std::cin >> size_a >> size_b >> key)) {
				std::cout << "Incorrect value." << std::endl;
				continue;
			}
			TreeItem * newNode = new TreeItem(Rectangle(size_a, size_b));
			tree->insert(newNode, key);
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
			tree = new Tree();
			std::cout << "The tree was deleted." << std::endl;
		}
		else if (action == "print" || action == "p") {
			if (!tree->empty()) {
				tree->print();
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

