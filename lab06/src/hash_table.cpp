#include "hash_table.h"

#include <iostream>

int my_hash(const int &elem, int m) {
	return (elem % m + m) % m;
}

int get_next_simple(int n) {
	for (int i = n + 1;; ++i) {
		bool is_prime = true;
		for (int j = 2; j * j <= i; ++j) {
			if (!(i % j)) {
				is_prime = false;
				break;
			}
		}
		if (is_prime)
			return i;
	}
}

template <typename T>
int MyHasher<T>::operator()(const T& elem, int m) const {
	return my_hash(elem, m);
}

template <typename T, typename THash>
HashTable<T, THash>::HashTable()
	: table(new Node*[BINS_COUNT])
	, table_size(BINS_COUNT) {
	for (int i = 0; i != BINS_COUNT; ++i)
		table[i] = nullptr;
}

template <typename T, typename THash>
HashTable<T, THash>::~HashTable() {
	clear();
}

template <typename T, typename THash>
void HashTable<T, THash>::clear() {
	delete[] table;
}

template <typename T, typename THash>
bool HashTable<T, THash>::add(const T& elem) {
	if (has(elem) > 0)
		return false;

	const int key = hash(elem, table_size);
	table[key] = new Node(elem, table[key]);

	return true;
}

template <typename T, typename THash>
int HashTable<T, THash>::remove(const T& elem) {
	int counter = 0;
	const int key = hash(elem, table_size);

	Node* parent = table[key];
	if (!parent)
		return -counter;

	if (++counter, (parent->elem == elem)) {
		table[key] = parent->next;
		parent->next = nullptr;
		delete parent;
		if (counter > MAX_COMP_NUM)
			rehash();
		return counter;
	}

	Node* node = parent->next;
	while (node) {
		if (++counter, (node->elem == elem)) {
			parent->next = node->next;
			delete node;
			if (counter > MAX_COMP_NUM)
				rehash();
			return counter;
		}
		parent = node;
		node = parent->next;
	}

	if (counter > MAX_COMP_NUM)
		rehash();

	return -counter;
}

template <typename T, typename THash>
int HashTable<T, THash>::has(const T& elem) {
	int counter = 0;
	const int key = hash(elem, table_size);
	Node* node = table[key];
	while (node) {
		++counter;
		if (node->elem == elem) {
			if (counter > MAX_COMP_NUM)
				rehash();
			return counter;
		}
		node = node->next;
	}
	if (counter > MAX_COMP_NUM)
		rehash();
	return -counter;
}

template <class T, class THash>
void HashTable<T, THash>::rehash() {
	int old_size = table_size;
	table_size = get_next_simple(table_size);

	Node** new_table = new Node*[table_size];
	for (int i = 0; i != table_size; ++i)
		new_table[i] = nullptr;

	for (int i = 0; i != old_size; ++i) {
		Node* node = table[i];
		while (node) {
			const int key = hash(node->elem, table_size);
			new_table[key] = new Node(node->elem, new_table[key]);
			Node* tmp = node;
			node = node->next;
			delete tmp;
		}
	}

	delete[] table;
	table = new_table;
}

template<class T, class THash>
void HashTable<T, THash>::print() const {
	for (int i = 0; i != table_size; ++i) {
		Node* node = table[i];
		std::cout << i << ": ";
		if (!node)
			std::cout << "null;";
		while (node) {
			std::cout << node->elem << "; ";
			node = node->next;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

template<class T, class THash>
int HashTable<T, THash>::size() const {
	return sizeof (Node);
}

void _impl_hash_table() {
	HashTable<int, MyHasher<int>> hash_table;
	hash_table.add(1);
	hash_table.add(2);
	hash_table.remove(3);
	hash_table.print();
	std::cout << hash_table.size() << hash_table.has(3);
}
