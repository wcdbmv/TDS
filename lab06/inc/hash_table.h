#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

int my_hash(const int& elem, int m);
int get_next_simple(int n);

#define MAX_COMP_NUM 4

template <typename T>
struct MyHasher {
	int operator()(const T& elem, int m) const;
};

template <typename T, typename THash=MyHasher<T>>
struct HashTable {
	static const int BINS_COUNT = 5;

	HashTable();
	~HashTable();

	bool add(const T& elem);
	int has(const T& elem);
	int remove(const T& elem);
	void print() const;
	int size() const;
private:
	struct Node {
		T elem;
		Node* next = nullptr;

		Node(const T& elem, Node* next = nullptr)
			: elem(elem)
			, next(next)
			{ }
	};

	Node** table = nullptr;
	int table_size;
	THash hash;

	void clear();
	void rehash();
};

#endif // HASH_TABLE_H_
