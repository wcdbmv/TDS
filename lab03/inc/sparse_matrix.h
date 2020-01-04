#ifndef __SPARSE_MATRIX_H__
#define __SPARSE_MATRIX_H__

#include <stdbool.h>
#include <math.h> // fabs
#include "io_ext.h" // fget_arr
#include "single_linked_list.h"
#include "errcodes.h"

#define STD_RESERVE 32
#define SIZE_LIMIT 2500

// T is simple type
typedef float T;
#define FT "%g"
#define EPS 1e-6

// U is simple unsigned integer type
typedef size_t U;
#define FU "%lu"

#pragma pack(push, 1)
typedef struct {
	T *a;
	U *ia;
	node_t *ja;
	size_t reserved;
	size_t size;
	size_t height;
	size_t width;
} sparse_matrix_t;
#pragma pack(pop)

typedef sparse_matrix_t sm_t;

//——————————————————————————————————————————————————————————————— sll extension

void *create_pU(U data);
void *fget_U(FILE *stream);
void delete_U(void **u);
void fwrite_U(FILE *stream, void *data);
void swap_data_U(node_t *a, node_t *b);

//———————————————————————————————————————————————————————————————————————— main

void assert_sm_created(const sm_t *sm);

sm_t *create_sm(size_t reserve, size_t height, size_t width);
sm_t *resize_sm(sm_t *old, size_t size);
sm_t *copy_sm(const sm_t *src);
void delete_sm(sm_t **sm);

bool in_sm(U ia, U ja, const sm_t *sm);
int append(sm_t *sm, T a, U ia, U ja);

//—————————————————————————————————————————————————————————————————————————— io

size_t calc_reserve(size_t size);
int fget_sm(FILE *stream, sm_t **sm);
void fwrite_sm(FILE *stream, const sm_t *sm, bool prompt);
void fwrite_sm_as_m(FILE *stream, const sm_t *sm);

//———————————————————————————————————————————————————————————————————— multiply

void sort_sm(sm_t *sm);
int mult_sm(sm_t *p, sm_t *q, sm_t **r);

#endif // __SPARSE_MATRIX_H__
