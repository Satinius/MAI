#pragma once
#include "TreeItem.h"

class Tree
{
public:
	Tree();
	TreeItem* insert(TreeItem *node, size_t key);
	void remove(size_t key);
	void remove(TreeItem* tree, size_t key);
	bool empty();
	TreeItem* find(TreeItem* tree, size_t key);
	void print();
	void print(TreeItem *tree, size_t depth);
	Rectangle data(size_t key);
	friend std::ostream& operator<<(std::ostream& os, const Tree& obj);
	~Tree();
private:
	TreeItem *root;
};

