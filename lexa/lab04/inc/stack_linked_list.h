#ifndef STACK_LINKED_LIST_H_
#define STACK_LINKED_LIST_H_

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
	StackLinkedList();
	StackLinkedList(StackLinkedList const*);
	~StackLinkedList() override;

	void push(T data) override;
	T pop() override;
	T top() const override;

	void clear() override;
	void print() const override;

	uint64_t vtop() const override;
protected:
	Node<T> *head_;
	Node<T> *tail_;

	Node<T> *get_node(const std::size_t index); // const
};

#endif // STACK_LINKED_LIST_H_
