#pragma once

#include <memory>

#include "VectorItem.h"
#include "TIterator.h"
#include "IRemoveCriteria.h"
template <class Container, class T>
class Vector
{
public:
	Vector();

	void pushBack(std::shared_ptr<Container> value);
	void print();

	void insertSubitem(std::shared_ptr<T> item, size_t key, size_t parentKey);
	void removeSubitem(IRemoveCriteria<T> * criteria);


	TIterator<VectorItem<Container>, Container> begin();
	TIterator<VectorItem<Container>, Container> end();

	bool empty();

	std::shared_ptr<VectorItem<Container>> get(size_t n);

	std::shared_ptr<Container> remove(size_t pos);

	~Vector();
private:
	void increaseCapacity(size_t n);
	std::shared_ptr<VectorItem<Container>> *data;
	size_t capacity;
	size_t used;
};

