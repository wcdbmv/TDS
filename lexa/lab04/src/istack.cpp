#include "istack.h"

template <typename T>
IStack<T>::IStack(const std::size_t limit /* = STD_LIMIT */)
	: limit_(limit), size_(0) { }

template <typename T>
std::size_t IStack<T>::size() const {
	return size_;
}

template <typename T>
bool IStack<T>::full() const {
	return size_ == limit_;
}

template <typename T>
bool IStack<T>::empty() const {
	return !size_;
}

template struct IStack<int>;
template struct IStack<char>;
template struct IStack<double>;
