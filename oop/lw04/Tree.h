#pragma once
#include "TreeItem.h"
#include <memory>

template <class T> class Tree
{
public:
	Tree();
	std::shared_ptr<TreeItem<T>> insert(std::shared_ptr<TreeItem<T>> node, size_t key);
	void remove(size_t key);
	void remove(std::shared_ptr<TreeItem<T>> tree, size_t key);
	bool empty();
	std::shared_ptr<TreeItem<T>> find(std::shared_ptr<TreeItem<T>> tree, size_t key);
	void Print();
	void Print(std::shared_ptr<TreeItem<T>> tree, size_t depth);
	template <class A> friend std::ostream& operator<<(std::ostream& os, const Tree<A> & obj);
	~Tree();
private:
	std::shared_ptr<TreeItem<T>> root;
};

