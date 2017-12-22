#pragma once

#include <memory>

#include "VectorItem.h"
#include "TIterator.h"

template <class T> 
class Vector
{
public:
	Vector();

	void pushBack(std::shared_ptr<T> Value);
	void print();

	TIterator<VectorItem<T>, T> begin();
	TIterator<VectorItem<T>, T> end();

	bool empty();

	std::shared_ptr<VectorItem<T>> get(size_t n);

	std::shared_ptr<T> remove(size_t pos);

	~Vector();
private:
	void increaseCapacity(size_t n);
	std::shared_ptr<VectorItem<T>> *data;
	size_t capacity;
	size_t used;
};

