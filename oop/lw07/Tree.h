#pragma once
#include "TreeItem.h"
#include "TIterator.h"
#include <memory>

template <class T> class Tree
{
public:
	Tree();

	TIterator<TreeItem<T>, T> begin();
	TIterator<TreeItem<T>, T> end();
	std::shared_ptr<TreeItem<T>> insert(std::shared_ptr<T> figure, size_t parentKey, size_t key);
	std::shared_ptr<TreeItem<T>> getRoot();
	void remove(size_t key);
	void remove(std::shared_ptr<TreeItem<T>> tree, size_t key);
	bool empty();
	std::shared_ptr<TreeItem<T>> find(std::shared_ptr<TreeItem<T>> tree, size_t key);
	void print(); 
	void print(std::shared_ptr<TreeItem<T>> tree, size_t depth);
	template <class A> friend std::ostream& operator<<(std::ostream& os, const Tree<A> & obj);
	size_t size();
	~Tree();
private:
	std::shared_ptr<TreeItem<T>> root;
};

