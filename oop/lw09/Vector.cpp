#include "stdafx.h"
#include "Vector.h"

template <class T>
Vector<T>::Vector()
{
	used = 0;
	capacity = 10;
	data = new std::shared_ptr<VectorItem<T>>[capacity];
}

template<class T>
void Vector<T>::pushBack(std::shared_ptr<T> value)
{
	if (used == capacity) {
		increaseCapacity(used * 2);
	}
	std::shared_ptr<VectorItem<T>> tmp = std::make_shared<VectorItem<T>>(value);
	data[used] = tmp;
	if(used > 0)
		data[used - 1]->setNext(data[used]);
	used++;
}

template<class T>
void Vector<T>::print()
{
	for (int i = 0; i < used; i++) {
		data[i]->print();
	}
}

template<class T>
TIterator<VectorItem<T>, T> Vector<T>::begin()
{
	return TIterator<VectorItem<T>, T>(data[0]);
}

template<class T>
TIterator<VectorItem<T>, T> Vector<T>::end()
{
	return TIterator<VectorItem<T>, T>(nullptr);
}

template<class T>
bool Vector<T>::empty()
{
	return used == 0;
}

template<class T>
std::shared_ptr<VectorItem<T>> Vector<T>::get(size_t n)
{
	return data[n];
}

template<class T>
std::shared_ptr<T> Vector<T>::remove(size_t pos)
{
	std::shared_ptr<VectorItem<T>> tmp = data[pos];
	//if (pos != 0)
	//	data[pos - 1]->setNext(data[pos + 1]);
	for (int i = pos; i < used - 1; i++) {
		data[i] = data[i + 1];
	}
	used--;
	return tmp->getValue();
}

template <class T>
Vector<T>::~Vector()
{
}

template<class T>
void Vector<T>::increaseCapacity(size_t n)
{
	if (n <= capacity)
		return;
	std::shared_ptr<VectorItem<T>> *new_arr = new std::shared_ptr<VectorItem<T>>[n];
	for (size_t i = 0; i < capacity; ++i) {
		new_arr[i] = data[i];
	}
	capacity = n;
	data = new_arr;
}

#include <functional>
template class Vector<std::function<void(void)>>;