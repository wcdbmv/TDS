template <typename T>
IStack<T>::IStack(const size_t limit)
	: limit_(limit), size_(0) { }

template <typename T>
size_t IStack<T>::size() const {
	return size_;
}

template <typename T>
bool IStack<T>::is_full() const {
	return size_ == limit_;
}

template <typename T>
bool IStack<T>::is_empty() const {
	return !size_;
}
