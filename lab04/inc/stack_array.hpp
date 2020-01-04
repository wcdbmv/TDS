template <typename T>
StackArray<T>::StackArray(const size_t limit)
	: IStack<T>(limit), array_(new T[limit]) { }

template <typename T>
StackArray<T>::~StackArray() {
	delete [] array_;
}

template <typename T>
void StackArray<T>::push(T data) {
	assert(!this->is_full());

	array_[this->size_++] = data;
}

template <typename T>
T StackArray<T>::pop() {
	assert(!this->is_empty());

	return array_[--this->size_];
}

template <typename T>
T StackArray<T>::top() const {
	assert(!this->is_empty());

	return array_[this->size_ - 1];
}


template <typename T>
void StackArray<T>::clear() {
	this->size_ = 0;
}


template <typename T>
void StackArray<T>::print() const {
	for (size_t i = 0; i != this->size(); ++i)
		std::cout << array_[i] << ' ';
}

template <typename T>
llu StackArray<T>::vtop() const {
	return 0;
}
