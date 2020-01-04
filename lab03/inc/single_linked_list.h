#ifndef __SINGLE_LINKED_LIST_H__
#define __SINGLE_LINKED_LIST_H__

#include <stdio.h> // FILE *
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

#include "errcodes.h" // for fget_chain

typedef struct node node_t;

struct node {
	void *data;
	node_t *next;
};

typedef void *(*fget_data_ft)(FILE *);
typedef void (*delete_data_ft)(void **);
typedef void (*fwrite_data_ft)(FILE *, void *);

node_t *create_node(void *data);
node_t *fget_node(fget_data_ft fget_data_f, FILE *stream);
void delete_node(node_t **node, delete_data_ft delete_data_f);

node_t *create_chain(size_t reserve);
void delete_chain(node_t **head, delete_data_ft delete_data_f);

int push_end_chain(node_t *head, void *data);
void swap_data(node_t *a, node_t *b);

int fget_chain(FILE *stream, size_t size, node_t *head, fget_data_ft fget_data_f);
void fwrite_chain(FILE *stream, const node_t *head, fwrite_data_ft fw_data_f);


#endif // __SINGLE_LINKED_LIST_H__
