#pragma once
#include <memory>
template <class T>
class VectorItem
{
public:
	VectorItem(std::shared_ptr<T> value);

	std::shared_ptr<T> getValue();
	std::shared_ptr<VectorItem<T>> setNext(std::shared_ptr<VectorItem<T>> next);
	std::shared_ptr<VectorItem<T>> getNext();
	void print();
	~VectorItem();
private:
	std::shared_ptr<T> _value;
	std::shared_ptr<VectorItem<T>> _next;
};

