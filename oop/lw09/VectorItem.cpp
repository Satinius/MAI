#include "stdafx.h"
#include "VectorItem.h"

template<class T>
VectorItem<T>::VectorItem(std::shared_ptr<T> value)
{
	_value = value;
}

template<class T>
std::shared_ptr<T> VectorItem<T>::getValue()
{
	return _value;
}

template<class T>
std::shared_ptr<VectorItem<T>> VectorItem<T>::setNext(std::shared_ptr<VectorItem<T>> next)
{
	_next = next;
	return next;
}

template<class T>
std::shared_ptr<VectorItem<T>> VectorItem<T>::getNext()
{
	return _next;
}

template<class T>
void VectorItem<T>::print()
{
	//getValue()->print();
}

template<class T>
VectorItem<T>::~VectorItem()
{
}

#include <functional>
template class VectorItem<std::function<void(void)>>;