// lw09.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <future>
#include <functional>
#include <random>
#include <thread>

#include "Tree.h"
#include "Vector.h"
#include "Figure.h"
#include "Rectangle.h"

int main()
{
	Tree<Rectangle> treeRect;
	typedef std::function<void(void) > command;
	Vector<command> vecCmd;

	

	command cmdInsert = [&]() {
		std::cout << "Creating random tree" << std::endl;
		std::default_random_engine generator(time(NULL));
		std::uniform_int_distribution<int> distribution(1, 20);
		for (int i = 0; i < 10; i++) {
			int side_a = distribution(generator);
			int side_b = distribution(generator);
			std::shared_ptr<Rectangle> ptr = std::make_shared<Rectangle>(side_a, side_b);
			int key = distribution(generator);
			treeRect.insert(ptr, 0, key);
		}
	};

	command cmdPrint = [&]() {
		std::cout << "Printing tree" << std::endl;
		treeRect.print();
	};

	command removeIfEqualN = [&]() {
		if (treeRect.empty()) {
			std::cout << "Tree is empty" << std::endl;

		}
		else {
			size_t n;
			std::cout << "Enter N: ";
			std::cin >> n;
			treeRect.remove(n);
		}
	};

	vecCmd.pushBack(std::shared_ptr<command>(&cmdInsert, [](command*){}));
	vecCmd.pushBack(std::shared_ptr<command>(&cmdPrint, [](command*) {}));
	vecCmd.pushBack(std::shared_ptr<command>(&removeIfEqualN, [](command*) {}));
	vecCmd.pushBack(std::shared_ptr<command>(&cmdPrint, [](command*) {}));

	while (!vecCmd.empty()) {
		std::shared_ptr<command> cmd = vecCmd.remove(0);
		std::future<void> ft = std::async(*cmd);
		ft.get();

	}
	system("pause");
    return 0;
}

