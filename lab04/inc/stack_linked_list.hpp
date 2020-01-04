template <typename T>
Node<T>::Node()
	: next(nullptr) { }

template <typename T>
Node<T>::Node(T data)
	: data(data), next(nullptr) { }

template <typename T>
StackLinkedList<T>::StackLinkedList(const size_t limit)
	: IStack<T>(limit), head_(nullptr), tail_(nullptr) { }

template <typename T>
StackLinkedList<T>::~StackLinkedList() {
	clear();
}

template <typename T>
Node<T> *StackLinkedList<T>::get_node(const size_t index) {
	if (index < 0 || (size_t) index >= this->size_)
		return nullptr;

	size_t i = 0;
	Node<T> *curr = head_;
	while (i < index && curr) {
		curr = curr->next;
		++i;
	}

	return curr;
}

template <typename T>
void StackLinkedList<T>::push(T data) {
	assert(!this->is_full());

	Node<T> *node = new Node<T>(data);

	if (this->size_++)
		tail_ = tail_->next = node;
	else
		tail_ = head_ = node;
}

template <typename T>
T StackLinkedList<T>::pop() {
	assert(!this->is_empty());

	T ret = tail_->data;
	if (this->size_ == 1) {
		delete tail_;
		head_ = tail_ = nullptr;
	}
	else {
		Node<T> *pretail_ = get_node(this->size_ - 2);
		delete tail_;
		pretail_->next = nullptr;
		tail_ = pretail_;
	}

	--this->size_;

	return ret;
}

template <typename T>
T StackLinkedList<T>::top() const {
	assert(!this->is_empty());

	return tail_->data;
}

template <typename T>
void StackLinkedList<T>::clear() {
	Node<T> *tmp;
	while (head_) {
		tmp = head_;
		head_ = head_->next;
		delete tmp;
	}
	tail_ = head_;
	this->size_ = 0;
}


template <typename T>
void StackLinkedList<T>::print() const {
	Node<T> *curr = head_;
	while (curr) {
		std::cout << curr->data << ' ';
		curr = curr->next;
	}
}

template <typename T>
llu StackLinkedList<T>::vtop() const {
	return (llu) tail_;
}
