#include "stdafx.h"
#include "Vector.h"

template <class Container, class T>
Vector<Container, T>::Vector()
{
	used = 0;
	capacity = 10;
	data = new std::shared_ptr<VectorItem<Container>>[capacity];
}

template <class Container, class T>
void Vector<Container, T>::pushBack(std::shared_ptr<Container> value)
{
	if (used == capacity) {
		increaseCapacity(used * 2);
	}
	std::shared_ptr<VectorItem<Container>> tmp = std::make_shared<VectorItem<Container>>(value);
	data[used] = tmp;
	if(used > 0)
		data[used - 1]->setNext(data[used]);
	used++;
}

template <class Container, class T>
void Vector<Container, T>::print()
{
	for (int i = 0; i < used; i++) {
		data[i]->print();
	}
}

template<class Container, class T>
void Vector<Container, T>::insertSubitem(std::shared_ptr<T> item, size_t key, size_t parentKey)
{
	bool inserted = false;
	if (used != 0) {
		for (auto i : *this) {
			if (i->size() < 5) {
				i->insert(item, parentKey, key);
				inserted = true;
			}
		}
	}

	if (!inserted) {
		std::shared_ptr<Container> ptr = std::make_shared<Container>();
		ptr->insert(item, parentKey, key);
		pushBack(ptr);
	}
}

template<class Container, class T>
void Vector<Container, T>::removeSubitem(IRemoveCriteria<T>* criteria)
{
	for (auto i : *this) {
		auto tmp = i->getRoot();
		while (tmp != nullptr) {
			if (criteria->isIt(&*(tmp->getValue()))) {
				size_t key = tmp->getKey();
				i->remove(key);
				break;
			}
			tmp = tmp->getNext();
		}
	}
}

template <class Container, class T>
TIterator<VectorItem<Container>, Container> Vector<Container, T>::begin()
{
	return TIterator<VectorItem<Container>, Container>(data[0]);
}

template <class Container, class T>
TIterator<VectorItem<Container>, Container> Vector<Container, T>::end()
{
	return TIterator<VectorItem<Container>, Container>(nullptr);
}

template <class Container, class T>
bool Vector<Container, T>::empty()
{
	return used == 0;
}

template <class Container, class T>
std::shared_ptr<VectorItem<Container>> Vector<Container, T>::get(size_t n)
{
	return data[n];
}

template <class Container, class T>
std::shared_ptr<Container> Vector<Container, T>::remove(size_t pos)
{
	std::shared_ptr<VectorItem<Container>> tmp = data[pos];
	//if (pos != 0)
	//	data[pos - 1]->setNext(data[pos + 1]);
	for (int i = pos; i < used - 1; i++) {
		data[i] = data[i + 1];
	}
	used--;
	return tmp->getValue();
}

template <class Container, class T>
Vector<Container, T>::~Vector()
{
}

template <class Container, class T>
void Vector<Container, T>::increaseCapacity(size_t n)
{
	if (n <= capacity)
		return;
	std::shared_ptr<VectorItem<Container>> *new_arr = new std::shared_ptr<VectorItem<Container>>[n];
	for (size_t i = 0; i < capacity; ++i) {
		new_arr[i] = data[i];
	}
	capacity = n;
	data = new_arr;
}

#include "Tree.h"
#include "Rectangle.h"
template class Vector<Tree<Rectangle>, Rectangle>;
//#include <functional>
//template class Vector<std::function<void(void)>>;