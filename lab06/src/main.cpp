#include "interface.h"

#include <cstdio>

int main() {
	setbuf(stdout, nullptr);

	HashTable<int, MyHasher<int> > hash_table;
	AVLTreeNode<int>* avl_tree = nullptr;
	BinaryTreeNode<int>* binary_tree = nullptr;

	fill_structs(&hash_table, &avl_tree, &binary_tree);

	cls();

	while (true) {
		show_info();
		int action = read_action();
		switch (action) {
		case 1:
			print_structs(hash_table, avl_tree, binary_tree);
			break;
		case 2:
			insert_key(hash_table, &avl_tree, &binary_tree);
			break;
		case 3:
			remove_key(hash_table, &avl_tree, &binary_tree);
			break;
		case 0:
			return print_exit();
			break;
		default:
			print_error();
			break;
		}
	}
}

// int main() {
// 	AVLTreeNode<int>* root = new AVLTreeNode<int>(0);
// 	root = insert(root, 1);
// 	root = insert(root, 2);
// 	root = insert(root, 3);
// 	root = insert(root, 4);
// 	root = insert(root, 5);
// 	root = insert(root, 6);
// 	root = insert(root, 7);
// 	root = insert(root, 8);
// 	root = insert(root, 9);
// 	root = insert(root, 10);
// 	root = insert(root, 11);
// 	root = insert(root, 12);
// 	root = insert(root, 13);
// 	root = insert(root, 14);
// 	root = insert(root, 15);
// 	root = insert(root, 16);
// 	root = insert(root, 17);
// 	root = insert(root, 18);
// 	root = insert(root, 19);
// 	display(root, 1, 0, std::cout);
// 	delete root;
// }

// int main() {
// 	HashTable<int, MyHasher<int>> hash_table;
// 	hash_table.add(0);
// 	hash_table.add(1);
// 	hash_table.add(2);
// 	hash_table.add(3);
// 	hash_table.add(4);
// 	hash_table.add(5);
// 	hash_table.add(6);
// 	hash_table.add(7);
// 	hash_table.add(8);
// 	hash_table.add(9);
// 	hash_table.add(10);
// 	hash_table.add(11);
// 	hash_table.add(12);
// 	hash_table.add(13);
// 	hash_table.add(14);
// 	hash_table.add(15);
// 	hash_table.add(16);
// 	hash_table.add(17);
// 	hash_table.add(18);
// 	hash_table.add(19);
// 	hash_table.print();
// 	std::cout << hash_table.size() << " " << hash_table.has(3) << std::endl;
// }

// int main() {
// 	BinaryTreeNode<int>* root = new BinaryTreeNode<int>(10);
// 	root = insert(root, 5);
// 	root = insert(root, 15);
// 	root = insert(root, 2);
// 	root = insert(root, 7);
// 	root = insert(root, 12);
// 	root = insert(root, 17);
// 	root = insert(root, 1);
// 	root = insert(root, 0);
// 	root = insert(root, 3);
// 	root = insert(root, 4);
// 	root = insert(root, 6);
// 	root = insert(root, 8);
// 	root = insert(root, 9);
// 	root = insert(root, 11);
// 	root = insert(root, 13);
// 	root = insert(root, 14);
// 	root = insert(root, 18);
// 	root = insert(root, 16);
// 	root = insert(root, 19);
//
// 	int counter = 0;
// 	root = remove(root, 10, counter);
// 	root = remove(root, 11, counter);
// 	// root = remove(root, 12, counter);
// 	// root = remove(root, 13, counter);
// 	// root = remove(root, 14, counter);
// 	// root = remove(root, 15, counter);
// 	// root = remove(root, 16, counter);
// 	root = remove(root, 18, counter);
// 	// root = remove(root, 17, counter);
// 	// root = remove(root, 19, counter);
// 	// root = remove(root, 5, counter);
// 	root = remove(root, 6, counter);
// 	// root = remove(root, 7, counter);
// 	// root = remove(root, 8, counter);
// 	// root = remove(root, 9, counter);
// 	root = remove(root, 2, counter);
// 	// root = remove(root, 3, counter);
// 	// root = remove(root, 4, counter);
// 	root = remove(root, 1, counter);
//
// 	display(root, 1, 0, std::cout);
//
// 	std::cout << counter << std::endl;
// }
