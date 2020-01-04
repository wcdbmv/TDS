#include "display.h"

#include <string>
#include <iomanip>
#include <sstream>
#include <deque>

#include "avl_tree_node.h"
#include "binary_tree_node.h"

void show_line(const char* c, int p, int s) {
	int t = s, i;
	for (i = 0; i != p; ++i) {
		printf((t & 1) ? "\u2502  " : "   ");
		t /= 2;
	}
	printf("%s", c);
}

template <typename TNode>
void show_tree(TNode* wood, int p, int s) {
	if (!wood)
		return;
	printf("%d\n", wood->key);

	if (wood->left) {
		show_line("\u2502\n", p, s);
		show_line("L: ", p, s);
		show_tree(wood->left, p + 1, s + (!!wood->right << p));
	}
	if (wood->right) {
		show_line("\u2502\n", p, s);
		show_line("R: ", p, s);
		show_tree(wood->right, p + 1, s);
	}
}

template <typename TNode>
void display_vertically(TNode* root, std::ostream& out) {
	show_tree(root, 0, 0);
}

std::string int_to_string(int value) {
	std::ostringstream ss;
	ss << value;
	return ss.str();
}

template <typename Node>
void print_branches(int branch_len,
                    int node_space_len,
                    int start_len,
                    int nodes_in_this_level,
                    const std::deque<Node*>& nodes_queue,
                    std::ostream& out) {
	auto iter = nodes_queue.begin();
	for (int i = 0; i != nodes_in_this_level / 2; ++i) {
		out << std::setw(i ? node_space_len - 2 : start_len -1) << ""
		    << ((*iter++) ? "\u2571" : " ");
		out << std::setw(2 * branch_len + 2) << ""
		    << ((*iter++) ? "\u2572" : " ");
	}
	out << std::endl;
}

template <typename Node>
void print_nodes(int branch_len,
                 int node_space_len,
                 int start_len,
                 int nodes_in_this_level,
                 const std::deque<Node*>& nodes_queue,
                 std::ostream& out) {
	auto iter = nodes_queue.begin();
	for (int i = 0; i != nodes_in_this_level; ++i, ++iter) {
		out << std::setw(i ? node_space_len : start_len) << ""
		    << std::setfill(*iter && (*iter)->left ? '_' : ' ');
		out << std::setw(branch_len + 2)
		    << (*iter ? int_to_string((*iter)->key) : "");
		out << std::setfill(*iter && (*iter)->right ? '_' : ' ')
		    << std::setw(branch_len) << "" << std::setfill(' ');
	}
	out << std::endl;
}

template <typename Node>
void print_leaves(int indent_space,
                  int level,
                  int nodes_in_this_level,
                  const std::deque<Node*>& nodes_queue,
                  std::ostream& out) {
	auto iter = nodes_queue.begin();
	for (int i = 0; i != nodes_in_this_level; ++i, ++iter) {
		out << std::setw(i ? 2 * level + 2 : indent_space + 2)
		    << (*iter ? int_to_string((*iter)->key) : "");
	}
	out << std::endl;
}

template <typename TNode>
void display(TNode* root, int level, int indent_space, std::ostream& out) {
	int h = height_of(root);
	if (h > 6) {
		display_vertically(root, out);
		return;
	}
	int nodes_in_this_level = 1;
	int branch_len = (((1 << h) - 1) << 1) - (3 - level) * (1 << (h - 1));
	int node_space_len = 2 + (level + 1) * (1 << h);
	int start_len = branch_len + (3 - level) + indent_space;
	std::deque<TNode*> nodes_queue;

	nodes_queue.push_back(root);
	for (int i = 1; i != h; ++i) {
		print_branches(branch_len, node_space_len, start_len,
		               nodes_in_this_level, nodes_queue, out);
		branch_len = branch_len / 2 - 1;
		node_space_len = node_space_len / 2 + 1;
		start_len = branch_len + (3 - level) + indent_space;
		print_nodes(branch_len, node_space_len, start_len, nodes_in_this_level,
		            nodes_queue, out);

		for (int j = 0; j != nodes_in_this_level; ++j) {
			TNode* curr = nodes_queue.front();
			nodes_queue.pop_front();
			if (curr) {
				nodes_queue.push_back(curr->left);
				nodes_queue.push_back(curr->right);
			}
			else {
				nodes_queue.push_back(NULL);
				nodes_queue.push_back(NULL);
			}
		}

		nodes_in_this_level <<= 1;
	}
	print_branches(branch_len, node_space_len, start_len, nodes_in_this_level,
	               nodes_queue, out);
	print_leaves(indent_space, level, nodes_in_this_level, nodes_queue, out);
}

void _impl_display() {
	AVLTreeNode<int>* avl_tree_node = new AVLTreeNode<int>(0);
	BinaryTreeNode<int>* binary_tree_node = new BinaryTreeNode<int>(0);
	display(avl_tree_node, 1, 0, std::cout);
	display(binary_tree_node, 1, 0, std::cout);
	avl_tree_node = insert(avl_tree_node, 1);
	display(avl_tree_node, 1, 0, std::cout);
	display_vertically(binary_tree_node, std::cout);
	show_tree(binary_tree_node, 0, 0);
	avl_tree_node = insert(avl_tree_node, 2);
	std::cout << avl_tree_node->height;
	delete avl_tree_node;
	delete binary_tree_node;
}
