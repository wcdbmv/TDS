#pragma once

#include "iqueue.h"
#include "node.h"
#include "request.h"

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

	size_t vtop() const;

	template <typename U>
	friend std::ostream& operator<<(std::ostream& os, QueueLinkedList<U>& qll);

	double avgtime() const;
	void updqueue(double up);
protected:
	Node<T>* prehead_;
	Node<T>* tail_;
};

#include "queue_linked_list.hpp"
