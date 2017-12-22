#include "stdafx.h"
#include "Tree.h"

Tree::Tree()
{
	this->root = nullptr;
}

std::shared_ptr<TreeItem> Tree::insert(std::shared_ptr<TreeItem> node, size_t key)
{
	if (this->empty()) {
		this->root = node;
		std::cout << "Tree was empty. Item was setted as root." << std::endl;
		return this->root;
	}
	std::shared_ptr<TreeItem> parent = find(this->root, key);
	if (!parent) {
		std::cout << "Parent with this square not found. Automatic insertion to the nearest place." << std::endl;
		if (root->GetSon()) {
			std::shared_ptr<TreeItem> tmp = root->GetSon();
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
		std::shared_ptr<TreeItem> tmp = parent->GetSon();
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
std::shared_ptr<Rectangle> Tree::rectangle(size_t key)
{
	std::shared_ptr<TreeItem> tmp = this->find(this->root, key);
	return tmp->GetRectangle();
}
void Tree::remove(size_t key)
{
	if (root->GetKey() == key) {
		root = nullptr;
	}
	else {
		remove(root, key);
	}
}

void Tree::remove(std::shared_ptr<TreeItem> tree, size_t key)
{
	if (tree->GetSon()) {
		if (tree->GetSon()->GetKey() == key) {
			std::shared_ptr<TreeItem> tr = tree->GetSon();
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
			std::shared_ptr<TreeItem> tr = tree->GetSibling();
			tree->SetSibling(tree->GetSibling()->GetSibling());
			tr->SetSibling(nullptr);
			return;
		}
		else {
			remove(tree->GetSibling(), key);
		}
	}
}

bool Tree::empty()
{
	return this->root == nullptr;
}

std::shared_ptr<TreeItem> Tree::find(std::shared_ptr<TreeItem> tree, size_t key)
{
	std::shared_ptr<TreeItem> tr = nullptr;
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

void Tree::Print()
{
	this->Print(this->root, 0);
}

void Tree::Print(std::shared_ptr<TreeItem> tree, size_t depth)
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


Tree::~Tree()
{
}

std::ostream & operator<<(std::ostream & os, Tree & obj)
{
	obj.Print();
	return os;
}
