#include "binary_tree_node.h"

#include <stack>

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(T key)
	: left(nullptr)
	, right(nullptr)
	, key(key)
	, height(1)
	{ }

// template <typename T>
// template <typename TAction>
// void BinaryTreeNode<T>::traverse(TAction action) {
// 	std::stack<BinaryTreeNode<T>*>* nodes = new std::stack<BinaryTreeNode<T>*>;
// 	nodes->push(this);
// 	while (!nodes->empty()) {
// 		BinaryTreeNode<T>* node = nodes->top();
// 		nodes->pop();
//
// 		if (node->right)
// 			nodes->push(node->right);
// 		if (node->left)
// 			nodes->push(node->left);
//
// 		action(node);
// 	}
//
// 	delete nodes;
// }

template <typename T>
void clear(BinaryTreeNode<T>* node) {
	std::stack<BinaryTreeNode<T>*>* nodes = new std::stack<BinaryTreeNode<T>*>;
	nodes->push(node);
	while (!nodes->empty()) {
		BinaryTreeNode<T>* curr = nodes->top();
		nodes->pop();

		if (curr->right)
			nodes->push(curr->right);
		if (curr->left)
			nodes->push(curr->left);

		delete curr;
	}

	delete nodes;
}

template <typename T>
std::size_t height_of(BinaryTreeNode<T>* node) {
	return node ? node->height : 0;
}

template <typename T>
BinaryTreeNode<T>* insert(BinaryTreeNode<T>* node, T key) {
	if (!node)
		return new BinaryTreeNode<T>(key);

	if (key < node->key)
		node->left = insert(node->left, key);
	else
		node->right = insert(node->right, key);

	node->height = std::max(height_of(node->left), height_of(node->right)) + 1;

	return node;
}

template <typename T>
BinaryTreeNode<T>* min_node(BinaryTreeNode<T>* node) {
	BinaryTreeNode<T>* curr = node;
	while (curr->left)
		curr = curr->left;

	return curr;
}

template <typename T>
BinaryTreeNode<T>* remove(BinaryTreeNode<T>* node, T key, int& counter) {
	if (!node) {
		counter = -counter;
		return node;
	}

	if (++counter, (key < node->key))
		node->left = remove(node->left, key, counter);
	else if (++counter, (key > node->key))
		node->right = remove(node->right, key, counter);
	else {
		BinaryTreeNode<T>* tmp;
		if (!node->left) {
			tmp = node->right;
			delete node;
			return tmp;
		}
		else if (!node->right) {
			tmp = node->left;
			delete node;
			return tmp;
		}

		tmp = min_node(node->right);
		node->key = tmp->key;
		node->right = remove(node->right, tmp->key, counter);
	}

	node->height = std::max(height_of(node->left), height_of(node->right)) + 1;
	return node;
}

template <typename T>
int find(const BinaryTreeNode<T>* node, T key, int counter /* = 0 */) {
	if (!node)
		return -counter;
	if (++counter, (key == node->key))
		return counter;
	if (++counter, (key < node->key))
		return find(node->left, key, counter);
	return find(node->right, key, counter);
}

#include <iostream>

void _impl_binary_tree_node() {
	BinaryTreeNode<int>* node = new BinaryTreeNode<int>(0);
	int counter = 0;
	node = insert(node, 1);
	node = insert(node, 2);
	node = insert(node, 3);
	node = insert(node, 4);
	node = remove(node, 1, counter);
	int a = find(node, 5) + 1;
	std::cout << height_of(node) << a << std::endl;
	clear(node);
}
