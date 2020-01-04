#ifndef IQUEUE_H_
#define IQUEUE_H_

#include <cstddef>

template <typename T>
struct IQueue {
public:
	IQueue();
	virtual ~IQueue() { }

	virtual void push(const T data) = 0;
	virtual T pop() = 0;
	virtual T top() const = 0;

	size_t size() const;
	bool is_empty() const;
	virtual bool is_full() const = 0;

	virtual void clear() = 0;

	virtual double avgtime() const = 0;
	virtual void updqueue(double up) = 0;

	// получить адреса элементов (работает только для списка)
	virtual size_t vtop() const = 0;
	virtual size_t vend() const = 0;
protected:
	size_t size_;
};

#endif // IQUEUE_H_
