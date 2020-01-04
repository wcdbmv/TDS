#include "interface.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include "colors.h"
#include "display.h"

void cls() {
	std::cout << CLS;
}

int clear_input() {
	int res = -1;
	char c;
	while ((++res, c = std::cin.get()) != '\n' && c != EOF)
		;
	return res;
}

void press_enter() {
	std::cout << DEFAULT FLASHING "<press Enter to continue>" DEFAULT << std::endl;
	if (getchar() != '\n')
		clear_input();
	std::cout << CANCEL_FLUSHING DEFAULT " " CLS DEFAULT;
}

void fill_structs(HashTable<int, MyHasher<int> >* hash_table,
                  AVLTreeNode<int>** avl_tree,
                  BinaryTreeNode<int>** binary_tree) {
	std::ifstream file("./data", std::ios::in);
	int n;
	while (file >> n) {
		hash_table->add(n);
		*avl_tree = insert(*avl_tree, n);
		*binary_tree = insert(*binary_tree, n);
	}
	file.close();
}

void show_info() {
	std::cout << DEFAULT CLS BOLD "Menu:" DEFAULT << std::endl;
	std::cout << "1. Show" << std::endl;
	std::cout << "2. Insert" << std::endl;
	std::cout << "3. Find" << std::endl;
	std::cout << "0. Exit" << std::endl;
}

int read_action() {
	int res = -1;
	std::cout << DEFAULT "\n>>> ";
	char c = std::cin.get();
	res = c - '0';
	if (c != '\n')
		if (clear_input())
			return -1;
	return res;
}

void print_structs(HashTable<int, MyHasher<int> >& hash_table,
                   AVLTreeNode<int>* avl_tree,
                   BinaryTreeNode<int>* binary_tree) {
	cls();
	std::cout << DEFAULT BOLD "Hash table:\n" DEFAULT;
	hash_table.print();
	std::cout << DEFAULT BOLD "AVL tree:\n" DEFAULT;
	display(avl_tree, 1, 0, std::cout);
	std::cout << DEFAULT BOLD "Binary tree:\n" DEFAULT;
	display(binary_tree, 1, 0, std::cout);
	press_enter();
}

#define ERR -927846

int input_key() {
	int d = ERR;

	std::cout << DEFAULT "\nInput key\n>>> " DEFAULT;
	int rc1 = scanf("%d", &d);
	int rc2 = clear_input();
	if (rc1 != 1 || rc2)
		return ERR;

	return d;
}

void insert_key(HashTable<int, MyHasher<int> >& hash_table,
                AVLTreeNode<int>** avl_tree,
                BinaryTreeNode<int>** binary_tree) {
	int key = input_key();
	if (key == ERR) {
		print_error();
		return;
	}

	if (find(*avl_tree, key) > 0) {
		print_error("Can't insert existed value");
		return;
	}

	hash_table.add(key);
	*avl_tree = insert(*avl_tree, key);
	*binary_tree = insert(*binary_tree, key);

	std::cout << DEFAULT GREEN_FG "\nInserted successful\n\n" DEFAULT;

	press_enter();
}

void find_key(HashTable<int, MyHasher<int> >& hash_table,
              AVLTreeNode<int>** avl_tree,
              BinaryTreeNode<int>** binary_tree) {
	int key = input_key();
	if (key == ERR) {
		print_error();
		return;
	}
	else if (find(*avl_tree, key) <= 0) {
		std::cout << DEFAULT RED_FG "\nThere is no such element\n" DEFAULT;
	}
	else {
		std::cout << DEFAULT GREEN_FG "\nFind successful\n" DEFAULT;
	}

	int a = 0, b = 0, c = 0;
	auto _a = std::chrono::steady_clock::now();
	a = hash_table.has(key);
	auto _b = std::chrono::steady_clock::now();
	b = find(*avl_tree, key);
	auto _c = std::chrono::steady_clock::now();
	c = find(*binary_tree, key);
	auto _d = std::chrono::steady_clock::now();

	auto d1 = std::chrono::duration_cast<std::chrono::nanoseconds>(_b - _a);
	auto d2 = std::chrono::duration_cast<std::chrono::nanoseconds>(_c - _b);
	auto d3 = std::chrono::duration_cast<std::chrono::nanoseconds>(_d - _c);

	auto d4 = (d1.count() + d2.count() + d3.count()) / 3;

	int size = count_of(*avl_tree);

	std::cout << DEFAULT "Comparisons:\n";
	std::cout << "Hash table: " << a << "\n";
	std::cout << "AVL tree: " << b << "\n";
	std::cout << "Binary tree: " << c << "\n";
	std::cout << "File: " << c + (b - a) / 2 << "\n";

	std::cout << "\nTime:\n";
	std::cout << "Hash table: " << d1.count() << "\n";
	std::cout << "AVL tree: " << d2.count() << "\n";
	std::cout << "Binary tree: " << d3.count() << "\n";
	std::cout << "File: " << d4 << "\n";

	std::cout << "\nMemory:\n";
	std::cout << "Hash table: " << (size + 1) * 8 << "\n";
	std::cout << "AVL tree: " << size * 16 + 4 << "\n";
	std::cout << "Binary tree: " << size * 16 + 4 << "\n\n";

	press_enter();
}

int print_exit() {
	std::cout << DEFAULT BOLD "\nI hope I was helpful. Thank you for using\n\n" DEFAULT;
	press_enter();
	cls();
	return 0;
}

void print_error(const char* msg) {
	if (!msg)
		std::cout << DEFAULT RED_FG "Invalid input\n\n" DEFAULT;
	else
		std::cout << DEFAULT RED_FG << msg << "\n\n" DEFAULT;
	press_enter();
}
