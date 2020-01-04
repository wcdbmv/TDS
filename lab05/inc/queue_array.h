#pragma once

#include <iostream>
#include "iqueue.h"
#include "request.h"

template <typename T>
struct QueueArray : public IQueue<T> {
public:
	QueueArray(const size_t limit = LIMIT);
	~QueueArray() override;

	void push(const T data) override;
	T pop() override;
	T top() const override;

	bool is_full() const override;

	void clear() override;

	template <typename U>
	friend std::ostream& operator<<(std::ostream& os, const QueueArray<U>& qa);

	double avgtime() const;
	void updqueue(double up);
protected:
	T *array_;

	size_t pin_;
	size_t pout_;
	size_t limit_;

	static const size_t LIMIT = 4096;
};

#include "queue_array.hpp"
