#include "stdafx.h"
#include "Tree.h"

Tree::Tree()
{
	this->root = nullptr;
}

TreeItem * Tree::insert(TreeItem *node, size_t key)
{
	if (this->empty()) {
		this->root = node;
		std::cout << "Tree was empty. Item was setted as root." << std::endl;
		return this->root;
	}
	TreeItem * parent = find(this->root, key);
	if (!parent) {
		std::cout << "Parent with this square not found. Automatic insertion to the nearest place." << std::endl;
		if (root->getSon()) {
			TreeItem *tmp = root->getSon();
			while (tmp->getSibling())
				tmp = tmp->getSibling();
			tmp->setSibling(node);
			return tmp->getSibling();
		}
		else {
			root->setSon(node);
			return root->getSon();
		}
	}
	if (parent->getSon()) {
		TreeItem *tmp = parent->getSon();
		while (tmp->getSibling())
			tmp = tmp->getSibling();
		tmp->setSibling(node);
		return tmp->getSibling();
	}
	else {
		parent->setSon(node);
		return parent->getSon();
	}
}
Rectangle Tree::data(size_t key)
{
	TreeItem * tmp = this->find(this->root, key);
	Rectangle * shit = new Rectangle(0, 0);
	if (!tmp) {
		return *shit;
	}
	return tmp->getRectangle();
}
void Tree::remove(size_t key)
{
	if (root->getData() == key) {
		delete root;
		root = nullptr;
	}
	else {
		remove(root, key);
	}
}

void Tree::remove(TreeItem* tree, size_t key)
{
	if (tree->getSon()) {
		if (tree->getSon()->getData() == key) {
			TreeItem *tr = tree->getSon();
			tree->setSon(tree->getSon()->getSibling());
			tr->setSibling(nullptr);
			delete tr;
			return;
		}
		else {
			remove(tree->getSon(), key);
		}
	}
	if (tree->getSibling()) {
		if (tree->getSibling()->getData() == key) {
			TreeItem *tr = tree->getSibling();
			tree->setSibling(tree->getSibling()->getSibling());
			tr->setSibling(nullptr);
			delete tr;
			return;
		}
		else {
			remove(tree->getSibling(), key);
		}
	}
}

bool Tree::empty()
{
	return this->root == nullptr;
}

TreeItem* Tree::find(TreeItem* tree, size_t key)
{
	TreeItem *tr = nullptr;
	if (tree->getData() == key)
		return tree;
	if (tree->getSon()) {
		tr = find(tree->getSon(), key);
		if (tr != nullptr) {
			return tr;
		}
	}
	if (tree->getSibling()) {
		tr = find(tree->getSibling(), key);
		if (tr != nullptr) {
			return tr;
		}
	}
	return nullptr;
}

void Tree::print()
{
	this->print(this->root, 0);
}

void Tree::print(TreeItem *tree, size_t depth)
{
	if (tree)
		for (size_t i = 0; i < depth; i++)
			std::cout << "\t";
	//tree->getRectangle().print();
	std::cout << tree->getRectangle() << std::endl;
	if (tree->getSon())
		print(tree->getSon(), depth + 1);
	if (tree->getSibling())
		print(tree->getSibling(), depth);
}


Tree::~Tree()
{
	delete root;
}

std::ostream & operator<<(std::ostream & os, Tree & obj)
{
	obj.print();
	return os;
}
