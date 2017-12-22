#include "stdafx.h"
#include "Tree.h"

template <class T> 
Tree<T>::Tree()
{
	this->root = nullptr;
}

template<class T>
TIterator<TreeItem<T>, T> Tree<T>::begin()
{
	return TIterator<TreeItem<T>, T>(root);
}

template<class T>
TIterator<TreeItem<T>, T> Tree<T>::end()
{
	return TIterator<TreeItem<T>, T>(nullptr);
}

template <class T>
std::shared_ptr<TreeItem<T>> Tree<T>::insert(std::shared_ptr<T> figure, size_t parentKey, size_t key)
{
	std::shared_ptr<TreeItem<T>> node = std::make_shared<TreeItem<T>>(figure, key);
	if (empty()) {
		root = node;
		root->setParent(nullptr);
		std::cout << "Tree was empty. Item was setted as root." << std::endl;
		return root;
	}
	std::shared_ptr<TreeItem<T>> parent = find(this->root, parentKey);
	if (!parent) {
		std::cout << "Parent with this key not found. Automatic insertion to the nearest place." << std::endl;
		if (root->getSon()) {
			std::shared_ptr<TreeItem<T>> tmp = root->getSon();
			while (tmp->getSibling())
				tmp = tmp->getSibling();
			tmp->setSibling(node);
			node->setParent(root);
			return tmp->getSibling();
		}
		else {
			root->setSon(node);
			node->setParent(root);
			return root->getSon();
		}
	}
	if (parent->getSon()) {
		std::shared_ptr<TreeItem<T>> tmp = parent->getSon();
		while (tmp->getSibling())
			tmp = tmp->getSibling();
		tmp->setSibling(node);
		return tmp->getSibling();
	}
	else {
		parent->setSon(node);
		node->setParent(parent);
		return parent->getSon();
	}
}

template<class T>
std::shared_ptr<TreeItem<T>> Tree<T>::getRoot()
{
	return root;
}

template <class T>
void Tree<T>::remove(size_t key)
{
	if (root->getKey() == key) {
		root = nullptr;
	}
	else {
		remove(root, key);
	}
}


template <class T>
void Tree<T>::remove(std::shared_ptr<TreeItem<T>> node, size_t key)
{
	if (node->getSon()) {
		if (node->getSon()->getKey() == key) {
			std::shared_ptr<TreeItem<T>> tr = node->getSon();
			node->setSon(node->getSon()->getSibling());
			tr->setSibling(nullptr);
			return;
		}
		else {
			remove(node->getSon(), key);
		}
	}
	if (node->getSibling()) {
		if (node->getSibling()->getKey() == key) {
			std::shared_ptr<TreeItem<T>> tr = node->getSibling();
			node->setSibling(node->getSibling()->getSibling());
			tr->setSibling(nullptr);
			return;
		}
		else {
			remove(node->getSibling(), key);
		}
	}
}

template <class T>
bool Tree<T>::empty()
{
	return this->root == nullptr;
}

template <class T>
std::shared_ptr<TreeItem<T>> Tree<T>::find(std::shared_ptr<TreeItem<T>> node, size_t key)
{
	std::shared_ptr<TreeItem<T>> tr = nullptr;
	if (node->getKey() == key)
		return node;
	if (node->getSon()) {
		tr = find(node->getSon(), key);
		if (tr != nullptr) {
			return tr;
		}
	}
	if (node->getSibling()) {
		tr = find(node->getSibling(), key);
		if (tr != nullptr) {
			return tr;
		}
	}
	return nullptr;
}

template <class T>
void Tree<T>::print()
{
	this->print(this->root, 0);
}

template <class T>
void Tree<T>::print(std::shared_ptr<TreeItem<T>> tree, size_t depth)
{
	if (tree)
		for (size_t i = 0; i < depth; i++)
			std::cout << "\t";
	tree->print();
	if (tree->getSon())
		print(tree->getSon(), depth + 1);
	if (tree->getSibling())
		print(tree->getSibling(), depth);
}

template<class T>
size_t Tree<T>::size()
{
	size_t size = 0;
	for (auto it : *this) {
		size++;
	}
	return size;
}

template <class T>
Tree<T>::~Tree()
{
}

template <class T>
std::ostream & operator<<(std::ostream & os, Tree<T> & obj)
{
	obj.print();
	return os;
}

#include "Figure.h"
#include "Rectangle.h"
template class Tree<Rectangle>;
template std::ostream& operator<<(std::ostream& os, const Tree<Rectangle>& tree);
template class Tree<Figure>;
template std::ostream& operator<<(std::ostream& os, const Tree<Figure>& tree);