#pragma once
#include "TreeItem.h"

class Tree
{
public:
	Tree();
	std::shared_ptr<TreeItem> insert(std::shared_ptr<TreeItem> node, size_t key);
	void remove(size_t key);
	void remove(std::shared_ptr<TreeItem> tree, size_t key);
	bool empty();
	std::shared_ptr<TreeItem> find(std::shared_ptr<TreeItem> tree, size_t key);
	void Print();
	void Print(std::shared_ptr<TreeItem> tree, size_t depth);
	std::shared_ptr<Rectangle> rectangle(size_t key);
	friend std::ostream& operator<<(std::ostream& os, const Tree& obj);
	~Tree();
private:
	std::shared_ptr<TreeItem> root;
};

