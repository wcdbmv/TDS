#include "sparse_matrix.h"

//——————————————————————————————————————————————————————————————— sll extension

void *create_pU(U data) {
	U *pu = (U *) malloc(sizeof (U));

	if (pu)
		*pu = data;

	return (void *) pu;
}

void *fget_U(FILE *stream) {
	assert(stream);

	U u;

	if (fscanf(stream, FU, &u) != 1) // here is format
		return NULL;

	return create_pU(u);
}

void delete_U(void **u) {
	assert(u && *u);

	free(*(U **) u);
	*(U **) u = NULL;
}

void fwrite_U(FILE *stream, void *data) {
	assert(stream && data);

	fprintf(stream, FU " ", *(U *) data + 1); // here is format
}

//———————————————————————————————————————————————————————————————————————— main

void assert_sm_created(const sm_t *sm) {
	assert(sm);
	assert(sm->reserved);
	assert(sm->height);
	assert(sm->width);
	assert(sm->size < sm->reserved);
	assert(sm->a);
	assert(sm->ia);
	assert(sm->ja);
}

sm_t *create_sm(size_t reserve, size_t height, size_t width) {
	assert(reserve && height && width);

	sm_t *sm = (sm_t *) malloc(sizeof (sm_t));

	if (sm) {
		if ((sm->a = (T *) malloc(reserve * sizeof (T *)))) {
			if ((sm->ia = (U *) malloc(reserve * sizeof (U *)))) {
				if ((sm->ja = create_chain(reserve))) {
					sm->reserved = reserve;
					sm->size = 0;
					sm->height = height;
					sm->width = width;
					return sm;
				}
				free(sm->ia);
			}
			free(sm->a);
		}
		free(sm);
	}

	return sm;
}

sm_t *resize_sm(sm_t *old, size_t size) {
	return NULL;
}

void delete_sm(sm_t **sm) {
	assert(sm);
	assert_sm_created(*sm);

	free((*sm)->a);
	free((*sm)->ia);
	delete_chain(&(*sm)->ja, delete_U);

	free(*sm);
	*sm = NULL;
}

sm_t *copy_sm(const sm_t *src) {
	assert_sm_created(src);

	const size_t reserve = src->reserved;
	const size_t size = src->size;

	sm_t *dest = (sm_t *) malloc(sizeof (sm_t));

	if (dest) {
		if ((dest->a = (T *) malloc(reserve * sizeof (T *)))) {
			if ((dest->ia = (U *) malloc(reserve * sizeof (U *)))) {
				if ((dest->ja = create_chain(reserve))) {
					dest->reserved = reserve;
					dest->size = size;
					dest->height = src->height;
					dest->width = src->width;
					memcpy(dest->a, src->a, size * sizeof (T));
					memcpy(dest->ia, src->ia, size * sizeof (U));
					node_t **djai = &dest->ja;
					node_t *sjai = src->ja;
					for (size_t i = 0; i != size; ++i) {
						(*djai)->data = create_pU(*(U *) sjai->data);
						djai = &(*djai)->next;
						sjai = sjai->next;
					}
					return dest;
				}
				free(dest->ia);
			}
			free(dest->a);
		}
		free(dest);
	}

	return dest;
}

bool in_sm(U ia, U ja, const sm_t *sm) {
	assert_sm_created(sm);

	node_t *jai = sm->ja;
	for (size_t i = 0; i != sm->size; ++i, jai = jai->next)
		if (sm->ia[i] == ia && *(U *) jai->data == ja)
			return true;

	return false;
}

int append(sm_t *sm, T a, U ia, U ja) {
	assert_sm_created(sm);

	if (fabs(a) < EPS || ia >= sm->height || ja >= sm->width)
		return INVALID_ELEM_ERROR;

	if (in_sm(ia, ja, sm))
		return ELEM_EXISTS_ERROR;

	const size_t i = sm->size++;
	sm->a[i] = a;
	sm->ia[i] = ia;

	U *pja = create_pU(ja);
	if (!pja)
		return FAILED_ALLOC_ERROR;
	push_end_chain(sm->ja, pja);

	return EXIT_SUCCESS;
}

//—————————————————————————————————————————————————————————————————————————— io

size_t calc_reserve(size_t size) {
	size_t reserve = STD_RESERVE;
	while (reserve < size)
		reserve += STD_RESERVE;
	return reserve;
}

int fget_sm(FILE *stream, sm_t **sm) {
	assert(stream && sm);
	assert(!*sm);

	int rc;

	size_t size, height, width;
	if ((rc = fscanf(stream, "%lu %lu %lu", &size, &height, &width)) != 3) {
		return !rc && feof(stream) ? EMPTY_FILE_ERROR : READ_FILE_ERROR;
	}

	if (size > SIZE_LIMIT)
		return SIZE_OVERFLOW_ERROR;

	const size_t reserve = calc_reserve(size);

	if (!(*sm = create_sm(reserve, height, width)))
		return FAILED_ALLOC_ERROR;

	T a[size];
	U ia[size], ja[size];

	if ((rc = fget_arr(stream, size, sizeof (T), a, FT)) != EXIT_SUCCESS) {
		delete_sm(sm);
		return rc;
	}

	if ((rc = fget_arr(stream, size, sizeof (U), ia, FU)) != EXIT_SUCCESS) {
		delete_sm(sm);
		return rc;
	}

	if ((rc = fget_arr(stream, size, sizeof (U), ja, FU)) != EXIT_SUCCESS) {
		delete_sm(sm);
		return rc;
	}

	for (size_t i = 0; i != size; ++i) {
		if ((rc = append(*sm, a[i], ia[i] - 1, ja[i] - 1)) != EXIT_SUCCESS) {
			delete_sm(sm);
			return rc;
		}
	}

	char r[64]; // ou, here may be attack
	if (fscanf(stream, "%s", r) == 1) {
		delete_sm(sm);
		return rc;
	}

	return rc; // EXIT_SUCCESS
}

void fwrite_sm(FILE *stream, const sm_t *sm, bool prompt) {
	assert_sm_created(sm);
	assert(stream);

	if (prompt) {
		fprintf(stream, "nonzeros: %lu, height: %lu, width: %lu\n", sm->size, sm->height, sm->width);
	}
	else {
		fprintf(stream, "%lu %lu %lu\n", sm->size, sm->height, sm->width);
	}

	if (prompt)
		fprintf(stream, " A: ");
	for (size_t i = 0; i != sm->size; ++i)
		fprintf(stream, FT " ", sm->a[i]); // here is format
	fprintf(stream, "\n");

	if (prompt)
		fprintf(stream, "IA: ");
	for (size_t i = 0; i != sm->size; ++i)
		fprintf(stream, FU " ", sm->ia[i] + 1); // here is format
	fprintf(stream, "\n");

	if (prompt)
		fprintf(stream, "JA: ");
	fwrite_chain(stream, sm->ja, fwrite_U); // here is format
	fprintf(stream, "\n");
}

void fwrite_sm_as_m(FILE *stream, const sm_t *sm) {
	assert_sm_created(sm);
	assert(stream);

	// sm must be sorted !!!

	const size_t height = sm->height;
	const size_t width = sm->width;
	const size_t size = sm->size;

	fprintf(stream, "%lu %lu\n", height, width);

	U k = 0;
	node_t *jak = sm->ja;

	for (U i = 0; i != height; ++i) {
		for (U j = 0; j != width; ++j) {
			if (k < size && sm->ia[k] == i && *(U *) jak->data == j) {
				fprintf(stream, FT " ", sm->a[k]);
				++k;
				jak = jak->next;
			}
			else {
				fprintf(stream, "0 ");
			}
		}
		fprintf(stream, "\n");
	}
}

//———————————————————————————————————————————————————————————————————— multiply

void sort_sm(sm_t *sm) {
	size_t size = sm->size;
	if (!sm->size)
		return;
	node_t **ja_i = &sm->ja;
	for (size_t i = 0; i != size - 1; ++i) {
		size_t i_min = i;
		node_t **ja_i_min = ja_i;
		T a_min = sm->a[i_min];
		U ia_min = sm->ia[i_min];
		U ja_min = *(U *) (*ja_i_min)->data;

		node_t **ja_j = &(*ja_i_min)->next;
		for (size_t j = i + 1; j != size; ++j) {
			T a_curr = sm->a[j];
			U ia_curr = sm->ia[j];
			U ja_curr = *(U *) (*ja_j)->data;

			if (ia_curr <= ia_min && ja_curr <= ja_min) {
				i_min = j;
				ja_i_min = ja_j;
				a_min = a_curr;
				ia_min = ia_curr;
				ja_min = ja_curr;
			}

			ja_j = &(*ja_j)->next;
		}

		if (i_min != i) {
			sm->a[i_min] = sm->a[i];
			sm->a[i] = a_min;

			sm->ia[i_min] = sm->ia[i];
			sm->ia[i] = ia_min;

			swap_data(*ja_i, *ja_i_min);
		}

		ja_i = &(*ja_i)->next;
	}
}


int mult_sm(sm_t *p, sm_t *q, sm_t **r) {
	assert_sm_created(p);
	assert_sm_created(q);
	assert(r && !*r);

	if (p->width != q->height)
		return INVALID_SIZES_ERROR;

	if (q->width != 1)
		return WRONG_USAGE_ERROR;

	// `p` and `q` must be sorted!!!

	size_t reserve = calc_reserve(p->size > q->size ? p->size : q->size); //
	*r = create_sm(reserve, p->height, q->width);
	if (!*r)
		return FAILED_ALLOC_ERROR;

	// 1

	size_t i = 0;
	node_t *jai = p->ja;
	while (i < p->size) {
		// printf("hure. i = %lu\n", i);
		T p_elem = p->a[i];
		U p_row = p->ia[i];
		U p_col = *(U *) jai->data;
		bool add_row = false;
		T elem = 0;
		size_t j = 0;
		bool is_break = false;
		while (j < q->size) {
			// printf("here. i = %lu, j = %lu\n", i, j);
			fwrite_sm(stderr, *r, 1);
			T q_elem = q->a[j];
			U q_row = q->ia[j];
			if (q_row > p_col) {
				// printf("q_roq > p_col\n");
				++i;
				if (i == p->size)
					return EXIT_SUCCESS;
				jai = jai->next;
				if (p_row != p->ia[i]) {
					is_break = true;
					// printf("p_row != p->ia[i], %lu, %lu\n", p_row, p->ia[i]);
					break;
				}
				p_elem = p->a[i];
				p_row = p->ia[i];
				p_col = *(U *) jai->data;
				// printf("q_row > p_col\n");
				continue;
			}
			else if (q_row == p_col) {
				add_row = true;
				elem += p_elem * q_elem;
				++j;
				continue;
			}
			else {
				++j;
				continue;
				// printf("++j = %lu\n", j);
			}
		}
		if (add_row && fabs(elem) >= EPS) {
			// printf("add row!\n");
			int rc = append(*r, elem, p_row, 0);
			if (rc != EXIT_SUCCESS) {
				delete_sm(r);
				return rc;
			}
		}
		if (is_break) {
			// printf("isbreak!\n");
			continue;
		}
		// printf("++i !!\n");
		++i;
		jai = jai->next;
	}

	return EXIT_SUCCESS;
}






//——————————————————————————————————————————————————————————————————— rudiments

/* old version of fget_row

int fget_row(FILE *stream, size_t *size, size_t *reserved, T **nums) {
	assert(stream && size && reserved && nums);
	assert(!*nums);

	char *buf = NULL;
	size_t len = 0;
	int rc = getline(&buf, &len, stream);
	if (rc <= 0) {
		rc = feof(stream) ? EMPTY_FILE_ERROR : READ_FILE_ERROR;
		goto fget_row_free_buf;
	}

	*reserved = STD_RESERVE;
	*nums = (T *) malloc(STD_RESERVE * sizeof (T));
	if (!nums) {
		rc = FAILED_ALLOC_ERROR;
		goto fget_row_free_buf;
	}
	*size = 0;

	int d, n;
	char *s = buf;
	while (true);
		if ((rc = sscanf(s, "%d %n", &d, &n)) != 1)
			break;
		if (*size == *reserved) {
			*reserved += STD_RESERVE;
			T* p = (T *) realloc(nums, c);
			if (!p) {
				rc = FAILED_ALLOC_ERROR;
				goto fget_row_free_nums;
			}
		}
		s += n;
	}

	// remainder
	char r[STR_LIMIT];
	if (sscanf(s, "%s", r) == 1) {
		rc = INVALID_INPUT_ERROR;
		goto fget_row_free_nums;
	}

	rc = EXIT_SUCCESS;
	goto fget_row_fin;

fget_row_free_nums:
	free(*nums);
	*nums = NULL;

fget_row_free_buf:
	if (buf)
		free(buf);

fget_row_fin:
	return rc;
}
*/
