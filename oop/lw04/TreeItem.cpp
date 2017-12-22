#include "stdafx.h"
#include "TreeItem.h"
#include <iostream>

template<class T>
TreeItem<T>::TreeItem(const std::shared_ptr<T>& figure, size_t key)
{
	this->figure = figure;
	this->key = key;
	this->sibling = nullptr;
	this->son = nullptr;
}

template <class T>
TreeItem<T>::TreeItem(const TreeItem<T>& orig)
{
	this->figure = orig.figure;
	this->son = orig.son;
	this->sibling = orig.sibling;
}

template <class T>
std::shared_ptr<TreeItem<T>> TreeItem<T>::GetSon()
{
	return this->son;
}

template <class T>
std::shared_ptr<TreeItem<T>> TreeItem<T>::GetSibling()
{
	return this->sibling;
}

template <class T>
void TreeItem<T>::SetSon(std::shared_ptr<TreeItem<T>> son)
{
	this->son = son;
}

template <class T>
void TreeItem<T>::SetSibling(std::shared_ptr<TreeItem<T>> sibling)
{
	this->sibling = sibling;
}

template <class T>
std::shared_ptr<T> TreeItem<T>::GetFigure() const
{
	return this->figure;
}

template <class T>
size_t TreeItem<T>::GetKey() const
{
	return key;
}

template <class T>
TreeItem<T>::~TreeItem()
{
	//std::cout << "TreeItem deleted" << std::endl;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const TreeItem<T>& obj)
{
	os << "[" << *obj.GetFigure() << "]" << ":"<< obj.GetKey() << std::endl;
	return os;
}

#include "Rectangle.h"
template class TreeItem<Rectangle>;
template std::ostream& operator<<(std::ostream& os, const TreeItem<Rectangle>& obj);