#pragma once

#include "istack.h"

template <typename T>
struct StackArray : public IStack<T> {
public:
	StackArray(const size_t limit = IStack<T>::STD_LIMIT);
	~StackArray();

	void push(const T data) override;
	T pop() override;
	T top() const override;

	void clear() override;
	void print() const override;

	llu vtop() const override;
protected:
	T *array_;
};

#include "stack_array.hpp"
