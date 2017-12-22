#pragma once
#include "Rectangle.h"
class TreeItem
{
public:
	TreeItem(const Rectangle& data);
	TreeItem(const TreeItem& orig);
	TreeItem* getSon();
	TreeItem* getSibling();
	TreeItem* setSon(TreeItem* son);
	TreeItem* setSibling(TreeItem* sibling);
	size_t getData();
	Rectangle TreeItem::getRectangle() const;
	friend std::ostream& operator<<(std::ostream& os, const TreeItem& obj);
	~TreeItem();
private:
	TreeItem *sibling;
	TreeItem *son;
	Rectangle data;
};

