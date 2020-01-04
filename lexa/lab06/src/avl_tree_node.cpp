#include "avl_tree_node.h"

#include <algorithm>

template <typename T>
AVLTreeNode<T>::AVLTreeNode(T key)
	: left(nullptr)
	, right(nullptr)
	, key(key)
	, count(1)
	, height(1)
	{ }

template <typename T>
std::uint8_t count_of(const AVLTreeNode<T>* node) {
	return node ? node->count : 0;
}

template <typename T>
std::uint8_t height_of(const AVLTreeNode<T>* node) {
	return node ? node->height : 0;
}

template <typename T>
int AVLTreeNode<T>::balance_factor() const {
	return height_of(right) - height_of(left);
}

template <typename T>
void AVLTreeNode<T>::update_fields() {
	count = count_of(left) + count_of(right) + 1;
	height = std::max(height_of(left), height_of(right)) + 1;
}

template <typename T>
AVLTreeNode<T>* AVLTreeNode<T>::rotate_left() {
	AVLTreeNode* node = right;
	right = right->left;
	node->left = this;

	this->update_fields();
	node->update_fields();

	return node;
}

template <class T>
AVLTreeNode<T>* AVLTreeNode<T>::rotate_right() {
	AVLTreeNode* node = left;
	left = left->right;
	node->right = this;

	this->update_fields();
	node->update_fields();

	return node;
}

template <class T>
AVLTreeNode<T>* AVLTreeNode<T>::balance() {
	update_fields();

	if (balance_factor() == 2) {
		if (right->balance_factor() < 0)
			right = right->rotate_right();
		return rotate_left();
	}
	if (balance_factor() == -2) {
		if (left->balance_factor() > 0)
			left = left->rotate_left();
		return rotate_right();
	}

	return this;
}

template <class T>
AVLTreeNode<T>* AVLTreeNode<T>::balance(int& counter) {
	update_fields();

	if (++counter, (balance_factor() == 2)) {
		if (++counter, (right->balance_factor() < 0))
			right = right->rotate_right();
		return rotate_left();
	}
	if (++counter, (balance_factor() == -2)) {
		if (++counter, (left->balance_factor() > 0))
			left = left->rotate_left();
		return rotate_right();
	}

	return this;
}

template <typename T>
AVLTreeNode<T>* insert(AVLTreeNode<T>* node, T key) {
	if (!node)
		return new AVLTreeNode<T>(key);
	if (key < node->key)
		node->left = insert(node->left, key);
	else
		node->right = insert(node->right, key);
	return node->balance();
}

template <typename T>
AVLTreeNode<T>* AVLTreeNode<T>::_find_min() {
	return left ? left->_find_min() : this;
}

template <typename T>
AVLTreeNode<T>* AVLTreeNode<T>::_remove_min(int& counter) {
	if (!left)
		return right;
	left = left->_remove_min(counter);
	return balance(counter);
}

template <typename T>
AVLTreeNode<T>* remove(AVLTreeNode<T>* node, T key, int& counter) {
	if (!node) {
		counter = -counter;
		return nullptr;
	}
	if (++counter, (key == node->key)) {
		AVLTreeNode<T>* left = node->left;
		AVLTreeNode<T>* right = node->right;
		delete node;
		if (!right)
			return left;
		node = right->_find_min();
		node->right = right->_remove_min(counter);
		node->left = left;
	}
	else if (++counter, (key < node->key))
		node->left = remove(node->left, key, counter);
	else
		node->right = remove(node->right, key, counter);

	if (counter <= 0)
		return node->balance();
	return node->balance(counter);
}

template <typename T>
int find(const AVLTreeNode<T>* node, T key, int counter) {
	if (!node)
		return -counter;
	if (++counter, (key == node->key))
		return counter;
	if (++counter, (key < node->key))
		return find(node->left, key, counter);
	return find(node->right, key, counter);
}

void _impl_avl_tree_node() {
	AVLTreeNode<int>* node = new AVLTreeNode<int>(0);
	int counter = find(node, 0);
	node = insert(node, (int) height_of(node));
	node = remove(node, (int) find(node, (int) count_of(node)), counter);
	delete node;
}
