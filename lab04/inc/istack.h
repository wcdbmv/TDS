#pragma once

#include <cstddef>
#include <cassert>
#include <iostream>

typedef long long unsigned llu;

template <typename T>
struct IStack {
public:
	IStack(const size_t limit = STD_LIMIT);
	virtual ~IStack() { }

	virtual void push(const T data) = 0;
	virtual T pop() = 0;
	virtual T top() const = 0;

	virtual void clear() = 0;

	size_t size() const;
	bool is_empty() const;
	bool is_full() const;

	virtual void print() const = 0;
	virtual llu vtop() const = 0;
protected:
	size_t size_;
	size_t limit_;

	static const size_t STD_LIMIT = 1024;
};

#include "istack.hpp"
