#pragma once

template <typename T>
struct Node {
public:
	T data;
	Node<T>* next;
public:
	Node(const T data = T(), Node<T>* next = nullptr);
};

#include "node.hpp"
