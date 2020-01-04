#include "single_linked_list.h"

node_t *create_node(void *data) {
	node_t *node = (node_t *) malloc(sizeof (node_t));

	if (node) {
		node->data = data;
		node->next = NULL;
	}

	return node;
}

node_t *fget_node(fget_data_ft fget_data_f, FILE *stream) {
	assert(stream);

	void *data = fget_data_f(stream);

	if (!data)
		return NULL;

	return create_node(data);
}

void delete_node(node_t **node, delete_data_ft delete_data_f) {
	assert(node && *node);

	if ((*node)->data)
		delete_data_f(&(*node)->data);

	free(*node);
	*node = NULL;
}

node_t *create_chain(size_t reserve) {
	assert(reserve);

	node_t *head = create_node(NULL);
	node_t *curr = head;
	for (size_t i = 1; i != reserve; ++i)
		curr = curr->next = create_node(NULL); // is it work ?

	return head;
}

void delete_chain(node_t **head, delete_data_ft delete_data_f) { // ?
	assert(head && *head);

	do {
		node_t *prev = *head;
		*head = (*head)->next;
		delete_node(&prev, delete_data_f);
	} while (*head);
}

int push_end_chain(node_t *head, void *data) {
	assert(head);

	node_t *curr = head;
	while (curr->data != NULL)
		if (!(curr = curr->next))
			return EXIT_FAILURE;

	curr->data = data;

	return EXIT_SUCCESS;
}

void swap_data(node_t *a, node_t *b) {
	void *tmp = a->data;
	a->data = b->data;
	b->data = tmp;
}

// this good but i need more powerful function with in_sm check
int fget_chain(FILE *stream, size_t size, node_t *head, fget_data_ft fget_data_f) {
	assert(stream && head && fget_data_f);

	node_t *curr = head;
	for (size_t i = 0; i != size; ++i) {
		if (!curr)
			return CHAIN_OVERFLOW_ERROR;
		curr->data = fget_data_f(stream);
		if (!curr->data)
			return INVALID_INPUT_ERROR;
	}

	return EXIT_SUCCESS;
}

void fwrite_chain(FILE *stream, const node_t *head, fwrite_data_ft fw_data_f) {
	void *data = head->data;
	while (data) {
		fw_data_f(stream, data);
		head = head->next;
		data = head->data;
	}
}
