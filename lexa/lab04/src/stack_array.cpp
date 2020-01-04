#include "stack_array.h"

#include <iostream>
#include <cassert>

template <typename T>
StackArray<T>::StackArray(const std::size_t limit /* = IStack<T>::STD_LIMIT */)
	: IStack<T>(limit), array_(new T[limit]) { }

template <typename T>
StackArray<T>::StackArray(StackArray<T> const* stack) {
	IStack<T>::limit_ = stack->limit_;
	IStack<T>::size_ = stack->size_;

	array_ = new T[IStack<T>::limit_];
	for (std::size_t i = 0; i != IStack<T>::size_; ++i)
		array_[i] = stack->array_[i];
}

template <typename T>
StackArray<T>::~StackArray() {
	delete [] array_;
}

template <typename T>
void StackArray<T>::push(T data) {
	assert(!IStack<T>::full());

	array_[this->size_++] = data;
}

template <typename T>
T StackArray<T>::pop() {
	assert(!IStack<T>::empty());

	return array_[--this->size_];
}

template <typename T>
T StackArray<T>::top() const {
	assert(!IStack<T>::empty());

	return array_[this->size_ - 1];
}

template <typename T>
void StackArray<T>::clear() {
	IStack<T>::size_ = 0;
}

template <typename T>
void StackArray<T>::print() const {
	if (IStack<T>::empty())
		std::cout << "<empty>";
	else
		for (std::size_t i = 0; i != IStack<T>::size(); ++i)
			std::cout << array_[i] << ' ';
}

template <typename T>
uint64_t StackArray<T>::vtop() const {
	return 0;
}

template struct StackArray<int>;
template struct StackArray<char>;
template struct StackArray<double>;
