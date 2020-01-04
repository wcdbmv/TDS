#ifndef STACK_ARRAY_H_
#define STACK_ARRAY_H_

#include "istack.h"

template <typename T>
struct StackArray : public IStack<T> {
public:
	StackArray(std::size_t const limit = IStack<T>::STD_LIMIT);
	StackArray(StackArray<T> const*);
	~StackArray() override;

	void push(const T data) override;
	T pop() override;
	T top() const override;

	void clear() override;
	void print() const override;

	uint64_t vtop() const override;
protected:
	T *array_;
};

#endif // STACK_ARRAY_H_
