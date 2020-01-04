#ifndef NODE_H_
#define NODE_H_

template <typename T>
struct Node {
public:
	T data;
	Node<T>* next;
public:
	Node(const T data = T(), Node<T>* next = nullptr);
};

#endif // NODE_H_
