#include "iqueue.h"

#include "request.h"

template <typename T>
IQueue<T>::IQueue()
	: size_(0)
	{ }

template <typename T>
size_t IQueue<T>::size() const {
	return size_;
}

template <typename T>
bool IQueue<T>::is_empty() const {
	return !size_;
}

template struct IQueue<Request>;
