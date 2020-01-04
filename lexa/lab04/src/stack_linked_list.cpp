#include "stack_linked_list.h"

#include <iostream>
#include <cassert>
#include <climits>

template <typename T>
Node<T>::Node()
	: next(nullptr) { }

template <typename T>
Node<T>::Node(T data)
	: data(data), next(nullptr) { }

template <typename T>
StackLinkedList<T>::StackLinkedList()
	: IStack<T>(INT_MAX), head_(nullptr), tail_(nullptr) { }

template <typename T>
StackLinkedList<T>::StackLinkedList(StackLinkedList const* stack) {
	IStack<T>::limit_ = INT_MAX;
	IStack<T>::size_ = stack->size_;

	if (!IStack<T>::size_) {
		tail_ = head_ = nullptr;
		return;
	}

	tail_ = head_ = new Node<T>(stack->head_->data);

	for (Node<T>* run = stack->head_->next; run; run = run->next)
		tail_ = tail_->next = new Node<T>(run->data);
}

template <typename T>
StackLinkedList<T>::~StackLinkedList() {
	clear();
}

template <typename T>
Node<T> *StackLinkedList<T>::get_node(const std::size_t index) {
	if (index < 0 || (std::size_t) index >= IStack<T>::size_)
		return nullptr;

	std::size_t i = 0;
	Node<T> *curr = head_;
	while (i < index && curr) {
		curr = curr->next;
		++i;
	}

	return curr;
}

template <typename T>
void StackLinkedList<T>::push(T data) {
	Node<T> *node = new Node<T>(data);

	if (IStack<T>::size_++)
		tail_ = tail_->next = node;
	else
		tail_ = head_ = node;
}

template <typename T>
T StackLinkedList<T>::pop() {
	assert(!IStack<T>::empty());

	T ret = tail_->data;
	if (IStack<T>::size_ == 1) {
		delete tail_;
		head_ = tail_ = nullptr;
	}
	else {
		Node<T> *pretail_ = get_node(IStack<T>::size_ - 2);
		delete tail_;
		pretail_->next = nullptr;
		tail_ = pretail_;
	}

	--IStack<T>::size_;

	return ret;
}

template <typename T>
T StackLinkedList<T>::top() const {
	assert(!IStack<T>::empty());

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
	IStack<T>::size_ = 0;
}


template <typename T>
void StackLinkedList<T>::print() const {
	if (IStack<T>::empty()) {
		std::cout << "<empty>";
		return;
	}
	Node<T> *curr = head_;
	while (curr) {
		std::cout << curr->data << ' ';
		curr = curr->next;
	}
}

template <typename T>
uint64_t StackLinkedList<T>::vtop() const {
	return (uint64_t) tail_;
}

template struct StackLinkedList<int>;
template struct StackLinkedList<char>;
template struct StackLinkedList<double>;
