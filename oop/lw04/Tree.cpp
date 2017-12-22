#include "stdafx.h"
#include "Tree.h"

template <class T> 
Tree<T>::Tree()
{
	this->root = nullptr;
}

template <class T>
std::shared_ptr<TreeItem<T>> Tree<T>::insert(std::shared_ptr<TreeItem<T>> node, size_t key)
{
	if (this->empty()) {
		this->root = node;
		std::cout << "Tree was empty. Item was setted as root." << std::endl;
		return this->root;
	}
	std::shared_ptr<TreeItem<T>> parent = find(this->root, key);
	if (!parent) {
		std::cout << "Parent with this key not found. Automatic insertion to the nearest place." << std::endl;
		if (root->GetSon()) {
			std::shared_ptr<TreeItem<T>> tmp = root->GetSon();
			while (tmp->GetSibling())
				tmp = tmp->GetSibling();
			tmp->SetSibling(node);
			return tmp->GetSibling();
		}
		else {
			root->SetSon(node);
			return root->GetSon();
		}
	}
	if (parent->GetSon()) {
		std::shared_ptr<TreeItem<T>> tmp = parent->GetSon();
		while (tmp->GetSibling())
			tmp = tmp->GetSibling();
		tmp->SetSibling(node);
		return tmp->GetSibling();
	}
	else {
		parent->SetSon(node);
		return parent->GetSon();
	}
}

template <class T>
void Tree<T>::remove(size_t key)
{
	if (root->GetKey() == key) {
		root = nullptr;
	}
	else {
		remove(root, key);
	}
}


template <class T>
void Tree<T>::remove(std::shared_ptr<TreeItem<T>> tree, size_t key)
{
	if (tree->GetSon()) {
		if (tree->GetSon()->GetKey() == key) {
			std::shared_ptr<TreeItem<T>> tr = tree->GetSon();
			tree->SetSon(tree->GetSon()->GetSibling());
			tr->SetSibling(nullptr);
			return;
		}
		else {
			remove(tree->GetSon(), key);
		}
	}
	if (tree->GetSibling()) {
		if (tree->GetSibling()->GetKey() == key) {
			std::shared_ptr<TreeItem<T>> tr = tree->GetSibling();
			tree->SetSibling(tree->GetSibling()->GetSibling());
			tr->SetSibling(nullptr);
			return;
		}
		else {
			remove(tree->GetSibling(), key);
		}
	}
}

template <class T>
bool Tree<T>::empty()
{
	return this->root == nullptr;
}

template <class T>
std::shared_ptr<TreeItem<T>> Tree<T>::find(std::shared_ptr<TreeItem<T>> tree, size_t key)
{
	std::shared_ptr<TreeItem<T>> tr = nullptr;
	if (tree->GetKey() == key)
		return tree;
	if (tree->GetSon()) {
		tr = find(tree->GetSon(), key);
		if (tr != nullptr) {
			return tr;
		}
	}
	if (tree->GetSibling()) {
		tr = find(tree->GetSibling(), key);
		if (tr != nullptr) {
			return tr;
		}
	}
	return nullptr;
}

template <class T>
void Tree<T>::Print()
{
	this->Print(this->root, 0);
}

template <class T>
void Tree<T>::Print(std::shared_ptr<TreeItem<T>> tree, size_t depth)
{
	if (tree)
		for (size_t i = 0; i < depth; i++)
			std::cout << "\t";
	std::cout << *tree << std::endl;
	if (tree->GetSon())
		Print(tree->GetSon(), depth + 1);
	if (tree->GetSibling())
		Print(tree->GetSibling(), depth);
}

template <class T>
Tree<T>::~Tree()
{
}

template <class T>
std::ostream & operator<<(std::ostream & os, Tree<T> & obj)
{
	obj.Print();
	return os;
}

#include "Tree.h"
template class Tree<Rectangle>;
template std::ostream& operator<<(std::ostream& os, const Tree<Rectangle>& tree);