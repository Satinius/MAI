#pragma once
#include "Rectangle.h"
#include "Rhombus.h"
#include "Trapeze.h"
#include <memory>
class TreeItem
{
public:
	TreeItem(const std::shared_ptr<Rectangle>& rectangle, const std::shared_ptr<Rhombus>& rhombus, const std::shared_ptr<Trapeze>& trapeze, size_t key);
	TreeItem(const TreeItem& orig);

	std::shared_ptr<TreeItem> GetSon();
	std::shared_ptr<TreeItem> GetSibling();
	void SetSon(std::shared_ptr<TreeItem> son);
	void SetSibling(std::shared_ptr<TreeItem> sibling);

	size_t GetKey() const;

	std::shared_ptr<Rectangle> GetRectangle() const;
	std::shared_ptr<Trapeze> GetTrapeze() const;
	std::shared_ptr<Rhombus> GetRhombus() const;
	friend std::ostream& operator<<(std::ostream& os, const TreeItem& obj);

	~TreeItem();
private:
	std::shared_ptr<TreeItem> son;
	std::shared_ptr<TreeItem> sibling;
	std::shared_ptr<Rectangle> rectangle;
	std::shared_ptr<Trapeze> trapeze;
	std::shared_ptr<Rhombus> rhombus;
	size_t key;
};

