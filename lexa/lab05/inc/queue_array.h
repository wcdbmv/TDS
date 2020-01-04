#ifndef QUEUE_ARRAY_H_
#define QUEUE_ARRAY_H_

#include <iostream>
#include "iqueue.h"

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

	double avgtime() const override;
	void updqueue(double up) override;

	size_t vtop() const override;
	size_t vend() const override;
protected:
	T *array_;

	size_t pin_;
	size_t pout_;
	size_t limit_;

	static const size_t LIMIT = 8192;
};

#endif // QUEUE_ARRAY_H_
