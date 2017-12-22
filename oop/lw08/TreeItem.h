#pragma once
#include "Rectangle.h"
#include "Rhombus.h"
#include "Trapeze.h"
#include "TAllocationBlock.h"
#include <memory>

template <class T> class TreeItem
{
public:
	TreeItem(const std::shared_ptr<T>& figure, size_t key);
	TreeItem(const TreeItem& orig);

	void * operator new (size_t size);
	void operator delete(void *p);

	std::shared_ptr<TreeItem<T>> getParent();
	std::shared_ptr<TreeItem<T>> getSon();
	std::shared_ptr<TreeItem<T>> getSibling();
	size_t getKey() const;
	std::shared_ptr<T> getFigure() const;

	void setParent(std::shared_ptr<TreeItem<T>> parent);
	void setSon(std::shared_ptr<TreeItem<T>> son);
	void setSibling(std::shared_ptr<TreeItem<T>> sibling);
	void setKey(size_t key);
	void setFigure(std::shared_ptr<T> figure);

	void print();

	
	template <class A> friend std::ostream& operator<<(std::ostream& os, const TreeItem<A>& obj);

	std::shared_ptr<TreeItem<T>> getNext();

	~TreeItem();
private:
	std::shared_ptr<TreeItem<T>> son;
	std::shared_ptr<TreeItem<T>> parent;
	std::shared_ptr<TreeItem<T>> sibling;
	std::shared_ptr<T> figure;
	size_t key;

	static TAllocationBlock treeitemAllocator;
};

