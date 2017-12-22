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
	this->parent = nullptr;
}

template <class T> TAllocationBlock
TreeItem<T>::treeitemAllocator(sizeof(TreeItem<T>), 100);

template <class T>
TreeItem<T>::TreeItem(const TreeItem<T>& orig)
{
	this->figure = orig.figure;
	this->son = orig.son;
	this->sibling = orig.sibling;
	this->parent = orig.parent;
}

template<class T>
void * TreeItem<T>::operator new(size_t size)
{
	return treeitemAllocator.allocate();
}

template<class T>
void TreeItem<T>::operator delete(void * p)
{
	treeitemAllocator.deallocate(p);
}

template<class T>
std::shared_ptr<TreeItem<T>> TreeItem<T>::getParent()
{
	return this->parent;
}

template <class T>
std::shared_ptr<TreeItem<T>> TreeItem<T>::getSon()
{
	return this->son;
}

template <class T>
std::shared_ptr<TreeItem<T>> TreeItem<T>::getSibling()
{
	return this->sibling;
}

template<class T>
void TreeItem<T>::setParent(std::shared_ptr<TreeItem<T>> parent)
{
	this->parent = parent;
}

template <class T>
void TreeItem<T>::setSon(std::shared_ptr<TreeItem<T>> son)
{
	this->son = son;
}

template <class T>
void TreeItem<T>::setSibling(std::shared_ptr<TreeItem<T>> sibling)
{
	this->sibling = sibling;
	sibling->parent = this->parent;
}

template <class T>
std::shared_ptr<T> TreeItem<T>::getFigure() const
{
	return this->figure;
}

template <class T>
void TreeItem<T>::setKey(size_t key)
{
	this->key = key;
}

template <class T>
size_t TreeItem<T>::getKey() const
{
	return key;
}

template<class T>
void TreeItem<T>::print()
{
	figure->print();
	std::cout << " : " << key << " : " << std::endl;
}

template<class T>
std::shared_ptr<TreeItem<T>> TreeItem<T>::getNext()
{
	std::shared_ptr<TreeItem<T>> tmp;
	if (this->getSon()) {
		return getSon();
	}
	else if (this->getSibling()) {
		return getSibling();
 	} else if (this->getParent()) {
		tmp = this->getParent();
		
		while (tmp && !(tmp->getSibling())) {
			tmp = tmp->getParent();
		}
		if (!tmp)
			return nullptr;
		tmp = tmp->getSibling();
		return tmp;
	}
	return nullptr;
}

template <class T>
TreeItem<T>::~TreeItem()
{
	//std::cout << "TreeItem deleted" << std::endl;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const TreeItem<T>& obj)
{
	//os << "[" << *obj.getFigure() << "]" << ":"<< obj.getKey() << std::endl;
	return os;
}

#include "TreeItem.h"
template class TreeItem<Figure>;
template std::ostream& operator<<(std::ostream& os, const TreeItem<Figure>& obj);