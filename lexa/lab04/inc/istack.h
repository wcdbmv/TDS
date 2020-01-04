#ifndef ISTACK_H_
#define ISTACK_H_

#include <cstddef>
#include <cstdint>

template <typename T>
struct IStack {
public:
	IStack(const std::size_t limit = STD_LIMIT);
	virtual ~IStack() { }

	virtual void push(const T data) = 0;
	virtual T pop() = 0;
	virtual T top() const = 0;

	virtual void clear() = 0;

	std::size_t size() const;
	bool empty() const;
	bool full() const;

	virtual void print() const = 0;
	virtual uint64_t vtop() const = 0;
protected:
	std::size_t limit_;
	std::size_t size_;

	static const std::size_t STD_LIMIT = 1024;
};

#endif // ISTACK_H_
