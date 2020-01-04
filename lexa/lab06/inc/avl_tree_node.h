#ifndef AVL_TREE_NODE_H_
#define AVL_TREE_NODE_H_

#include <cstdint>

template <typename T>
struct AVLTreeNode {
	AVLTreeNode* left;
	AVLTreeNode* right;

	T key;
	std::uint8_t count;
	std::uint8_t height;

	AVLTreeNode(T key);

	int balance_factor() const;
	void update_fields();

	AVLTreeNode<T>* rotate_left();
	AVLTreeNode<T>* rotate_right();

	AVLTreeNode<T>* balance();
	AVLTreeNode<T>* balance(int& counter);

	AVLTreeNode<T>* _find_min();
	AVLTreeNode<T>* _remove_min(int& counter);
};

template <typename T>
std::uint8_t count_of(const AVLTreeNode<T>* node);

template <typename T>
std::uint8_t height_of(const AVLTreeNode<T>* node);

template <typename T>
AVLTreeNode<T>* insert(AVLTreeNode<T>* node, T key);

template <typename T>
AVLTreeNode<T>* remove(AVLTreeNode<T>* node, T key, int& counter);

template <typename T>
int find(const AVLTreeNode<T>* node, T key, int counter=0);

#endif // AVL_TREE_NODE_H_
