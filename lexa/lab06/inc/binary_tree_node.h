#ifndef BINARY_TREE_NODE_H_
#define BINARY_TREE_NODE_H_

#include <cstddef>

template <typename T>
struct BinaryTreeNode {
	BinaryTreeNode* left;
	BinaryTreeNode* right;

	T key;
	std::size_t height;

	BinaryTreeNode(T key);
};

template <typename T>
std::size_t height_of(BinaryTreeNode<T>* node);

template <typename T>
BinaryTreeNode<T>* insert(BinaryTreeNode<T>* node, T key);

template <typename T>
BinaryTreeNode<T>* remove(BinaryTreeNode<T>* node, T key, int& counter);

template <typename T>
int find(const BinaryTreeNode<T>* node, T key, int counter=0);

template <typename T>
void clear(BinaryTreeNode<T>* node);

#endif // BINARY_TREE_NODE_H_
