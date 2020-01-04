#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "avl_tree_node.h"
#include "binary_tree_node.h"
#include "hash_table.h"

void cls();

void fill_structs(HashTable<int, MyHasher<int> >* hash_table,
                  AVLTreeNode<int>** avl_tree,
                  BinaryTreeNode<int>** binary_tree);

void show_info();

int read_action();

void print_structs(HashTable<int, MyHasher<int> >& hash_table,
                   AVLTreeNode<int>* avl_tree,
                   BinaryTreeNode<int>* binary_tree);

void insert_key(HashTable<int, MyHasher<int> >& hash_table,
                AVLTreeNode<int>** avl_tree,
                BinaryTreeNode<int>** binary_tree);

void remove_key(HashTable<int, MyHasher<int> >& hash_table,
                AVLTreeNode<int>** avl_tree,
                BinaryTreeNode<int>** binary_tree);

int print_exit();

void print_error(const char* msg = nullptr);

#endif // INTERFACE_H_
