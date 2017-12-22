#include "stdafx.h"
#include "TreeItem.h"
#include <iostream>

TreeItem::TreeItem(const std::shared_ptr<Rectangle>& rectangle, const std::shared_ptr<Rhombus>& rhombus, const std::shared_ptr<Trapeze>& trapeze, size_t key)
{
	this->rectangle = rectangle;
	this->rhombus = rhombus;
	this->trapeze = trapeze;
	this->sibling = nullptr;
	this->son = nullptr;
	this->key = key;
}

TreeItem::TreeItem(const TreeItem& orig)
{
	this->rectangle = orig.rectangle;
	this->son = orig.son;
	this->sibling = orig.sibling;
}

std::shared_ptr<TreeItem> TreeItem::GetSon()
{
	return this->son;
}

std::shared_ptr<TreeItem> TreeItem::GetSibling()
{
	return this->sibling;
}

void TreeItem::SetSon(std::shared_ptr<TreeItem> son)
{
	this->son = son;
}

void TreeItem::SetSibling(std::shared_ptr<TreeItem> sibling)
{
	this->sibling = sibling;
}

std::shared_ptr<Rectangle> TreeItem::GetRectangle() const
{
	return this->rectangle;
}

std::shared_ptr<Trapeze> TreeItem::GetTrapeze() const
{
	return this->trapeze;
}

std::shared_ptr<Rhombus> TreeItem::GetRhombus() const
{
	return this->rhombus;
}

size_t TreeItem::GetKey() const
{
	return key;
}


TreeItem::~TreeItem()
{
	//std::cout << "TreeItem deleted" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const TreeItem& obj)
{
	os << "[" << *obj.GetRectangle() << " " <<*obj.GetRhombus() << " " <<*obj.GetTrapeze() << "]" << ":"<< obj.GetKey() << std::endl;
	return os;
}
