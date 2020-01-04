#include "queue_array.h"

#include <cassert>
#include "request.h"

template <typename T>
QueueArray<T>::QueueArray(const size_t limit)
	: IQueue<T>()
	, array_(new T[limit]) // need check for zero ?
	, pin_(0)
	, pout_(0)
	, limit_(limit)
	{ }

template <typename T>
QueueArray<T>::~QueueArray() {
	delete[] array_;
}

template <typename T>
void QueueArray<T>::push(const T data) {
	assert(!is_full());

	array_[pout_] = data;
	pout_ = (pout_ + 1) % limit_;
	++IQueue<T>::size_;
}

template <typename T>
T QueueArray<T>::pop() {
	assert(!IQueue<T>::is_empty());

	T ret = array_[pin_];
	pin_ = (pin_ + 1) % limit_;
	--IQueue<T>::size_;
	return ret;
}

template <typename T>
T QueueArray<T>::top() const {
	assert(!IQueue<T>::is_empty());

	return array_[pin_];
}

template <typename T>
bool QueueArray<T>::is_full() const {
	return IQueue<T>::size_ == limit_;
}

template <typename T>
void QueueArray<T>::clear() {
	IQueue<T>::size_ = pin_ = pout_ = 0;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const QueueArray<T>& qa) {
	if (qa.size_) {
		if (qa.pin_ < qa.pout_)
			for (size_t i = qa.pin_; i != qa.pout_; ++i)
				std::cout << qa.array_[i] << ' ';
		else {
			for (size_t i = qa.pin_; i != qa.limit_; ++i)
				std::cout << qa.array_[i] << ' ';
			for (size_t i = 0; i != qa.pout_; ++i)
				std::cout << qa.array_[i] << ' ';
		}
	}
	return os;
}

template <typename T>
double QueueArray<T>::avgtime() const {
	double sum = 0.0;
	if (!IQueue<T>::size_)
		return sum;
	for (size_t i = 0; i != IQueue<T>::size_; ++i)
		sum += array_[i].time;
	return sum / IQueue<T>::size_;
}

template <typename T>
void QueueArray<T>::updqueue(double up) {
	for (size_t i = 0; i != IQueue<T>::size_; ++i)
		array_[i].time += up;
}

template <typename T>
size_t QueueArray<T>::vtop() const {
	return 0;
}

template <typename T>
size_t QueueArray<T>::vend() const {
	return 0;
}

template struct QueueArray<Request>;
