#pragma once
#include "Rectangle.h"
#include "Rhombus.h"
#include "Trapeze.h"
#include <memory>

template <class T> class TreeItem
{
public:
	TreeItem(const std::shared_ptr<T>& figure, size_t key);
	TreeItem(const TreeItem& orig);

	std::shared_ptr<TreeItem<T>> GetSon();
	std::shared_ptr<TreeItem<T>> GetSibling();
	void SetSon(std::shared_ptr<TreeItem<T>> son);
	void SetSibling(std::shared_ptr<TreeItem<T>> sibling);

	size_t GetKey() const;

	std::shared_ptr<T> GetFigure() const;
	template <class A> friend std::ostream& operator<<(std::ostream& os, const TreeItem<A>& obj);

	~TreeItem();
private:
	std::shared_ptr<TreeItem<T>> son;
	std::shared_ptr<TreeItem<T>> sibling;
	std::shared_ptr<T> figure;
	size_t key;
};

