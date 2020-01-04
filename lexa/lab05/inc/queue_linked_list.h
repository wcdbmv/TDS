#ifndef QUEUE_LINKED_LIST_H_
#define QUEUE_LINKED_LIST_H_

#include <iostream>
#include "iqueue.h"
#include "node.h"

template <typename T>
struct QueueLinkedList : public IQueue<T> {
public:
	QueueLinkedList();
	~QueueLinkedList() override;

	void push(const T data) override;
	T pop() override;
	T top() const override;

	bool is_full() const override;

	void clear() override;

	size_t vtop() const override;
	size_t vend() const override;

	template <typename U>
	friend std::ostream& operator<<(std::ostream& os, QueueLinkedList<U>& qll);

	double avgtime() const override;
	void updqueue(double up) override;
protected:
	Node<T>* prehead_;
	Node<T>* tail_;
};

#endif // QUEUE_LINKED_LIST_H_
