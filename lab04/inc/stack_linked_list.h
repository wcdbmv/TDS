#pragma once

#include "istack.h"

template <typename T>
struct Node {
	T data;
	Node<T> *next;

	Node();
	Node(T data);
};

template <typename T>
struct StackLinkedList : public IStack<T> {
public:
	StackLinkedList(const size_t limit = IStack<T>::STD_LIMIT);
	~StackLinkedList();

	void push(T data) override;
	T pop() override;
	T top() const override;

	void clear() override;
	void print() const override;

	llu vtop() const override;
protected:
	Node<T> *head_;
	Node<T> *tail_;

	Node<T> *get_node(const size_t index); // const
};

#include "stack_linked_list.hpp"
