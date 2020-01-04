#include "node.h"

#include "request.h"

template <typename T>
Node<T>::Node(const T data, Node<T>* next)
	: data(data)
	, next(next)
	{ }

template struct Node<Request>;
