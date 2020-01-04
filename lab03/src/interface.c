#include "interface.h"

static const char *menu_info = {
	"1. List matrices\n"
	"2. Show matrix\n"
	"3. Add matrix\n"
	"4. Delete matrix\n"
	"5. Multiply matrices\n"
	"0. Exit\n"
};

bool menu(void) {
	display(menu_info, "Menu:");
	char command[STR_LIMIT];
	get_string(command, "\nInput command: ");
	if (!strcmp(command, "1")) {
		sm_list();
	}
	else if (!strcmp(command, "2")) {
		sm_display();
	}
	else if (!strcmp(command, "3")) {
		sm_add();
	}
	else if (!strcmp(command, "4")) {
		sm_fremove();
	}
	else if (!strcmp(command, "5")) {
		sm_multiply();
	}
	else if (!strcmp(command, "0")) {
		puts("I hope i was helpful. Thanks you for using.");
		return false;
	}
	else {
		puts("Unfortunately, there is no such command :с");
		puts("Please try again.");
	}
	return true;
}

void sm_list(void) {
	ls(DIR, "\nList of matrices:");
}

int _fget_sm(sm_t **sm) {
	assert(sm && !*sm);

	FILE *file;
	get_file(&file, "r", DIR);
	if (!file) {
		return CANT_OPEN_FILE_ERROR;
	}
	int rc = fget_sm(file, sm);
	fclose(file);

	if (rc == EXIT_SUCCESS) {
		sort_sm(*sm);
	}
	return rc;
}

void sm_display(void) {
	sm_t *sm = NULL;
	int rc = _fget_sm(&sm);
	if (rc != EXIT_SUCCESS) {
		my_perror(rc);
		return;
	}
	printf("\n");
	fwrite_sm(stdout, sm, true);
	if (sm->height <= 20 && sm->width <= 40) {
		puts("\n==== (in the usual view) ====");
		fwrite_sm_as_m(stdout, sm);
	}
	delete_sm(&sm);
}

int is_nzT(void *p, void *_) {
	return fabs(*(T *) p) > EPS ? EXIT_SUCCESS : INPUT_ZERO_ERROR;
}

int is_lt(void *_r, void *_h) {
	U r = *(U *) _r;
	U h = *(U *) _h;
	return r <= h ? EXIT_SUCCESS : LT_ERROR;
}

int is_nznlt(void *_r, void *_h) {
	U r = *(U *) _r;
	U h = *(U *) _h;
	return 0 < r && r <= h ? EXIT_SUCCESS : NZNLT_ERROR;
}

void sm_add(void) {
	U __overflow_var = 1000000;
	size_t size, height, width;
	get_var(&height, "%llu", "\nInput height: ", is_nznlt, &__overflow_var);
	get_var(&width, "%llu", "\nInput width: ", is_nznlt, &__overflow_var);
	U max_size = height * width;
	get_var(&size, "%llu", "\nInput amount of nonzeros: ", is_lt, &max_size);

	size_t reserve = calc_reserve(size);
	sm_t *sm = create_sm(reserve, height, width);
	if (!sm) {
		my_perror(FAILED_ALLOC_ERROR);
		return;
	}

	for (size_t i = 0; i != size; ++i)
		while (true) {
			T a;
			U ia, ja;
			printf("\n---- Element %lu ----\n", i + 1);
			get_var(&a, FT, "\nInput elem: ", is_nzT, NULL);
			get_var(&ia, FU, "\nInput row: ", is_nznlt, &height);
			get_var(&ja, FU, "\nInput col: ", is_nznlt, &width);
			int rc = append(sm, a, ia - 1, ja - 1);
			if (rc == EXIT_SUCCESS) {
				printf("Element %lu was added successful.\n", i + 1);
				break;
			}
			my_perror(rc);
		}

	FILE *file;
	get_file(&file, "w", DIR);
	if (!file) {
		my_perror(CANT_OPEN_FILE_ERROR);
		delete_sm(&sm);
		return;
	}
	fwrite_sm(file, sm, false);
	puts("Matrix was created successful.");
	fclose(file);
	delete_sm(&sm);
}

void sm_fremove(void) {
	if (dir_is_empty(DIR)) {
		puts("There are no files.");
		return;
	}
	while (true) {
		char filename[STR_LIMIT];
		get_filename(filename, DIR);
		if (file_exists(filename)) {
			if (remove(filename)) {
				perror(filename);
			}
			else {
				puts("File was deleted successful.");
			}
			return;
		}
		puts("There is no such file.");
	}
}

typedef unsigned long long ULL;
ULL tick(void);
void print_ticks(ULL ticks, const char *prompt);

void sm_multiply(void) {
	size_t n = nfiles_in_dir(DIR);
	if (!n) {
		puts("There are no files.");
		return;
	}
	if (n == 1) {
		puts("Too few files.");
		return;
	}
	sm_t *p = NULL;
	puts("\n---- First matrix ----");
	int rc = _fget_sm(&p);
	if (rc != EXIT_SUCCESS) {
		my_perror(rc);
		return;
	}
	puts("First matrix was read successful.");
	sm_t *q = NULL;
	puts("\n---- Second matrix ----");
	if ((rc = _fget_sm(&q)) != EXIT_SUCCESS) {
		my_perror(rc);
		delete_sm(&p);
		return;
	}
	puts("Second matrix was read successful.");

	bool stat = false;
	const size_t _limit = 1000;
	m_t pp, qq, rr;
	if (p->height <= _limit && p->width <= _limit && q->height == p->width && q->width == 1) {
		stat = true;
		FILE *f = fopen("_tmp1", "w");
		fwrite_sm_as_m(f, p);
		fclose(f);
		f = fopen("_tmp2", "w");
		fwrite_sm_as_m(f, q);
		fclose(f);
		f = fopen("_tmp1", "r");
		get_matrix_1(f, &pp);
		fclose(f);
		remove("_tmp1");
		f = fopen("_tmp2", "r");
		get_matrix_1(f, &qq);
		fclose(f);
		remove("_tmp2");
	}

	ULL _a, _b, _c, _d;

	const size_t _mh = 20;
	const size_t _mw = 40;

	sm_t *res = NULL;
	_a = tick();
	if ((rc = mult_sm(p, q, &res)) == EXIT_SUCCESS) {
		_b = tick();
		puts("\n---- First matrix: ----");
		fwrite_sm(stdout, p, true);
		if (p->height <= _mh && p->width <= _mw) {
			puts("\n==== (in the usual view) ====");
			fwrite_sm_as_m(stdout, p);
		}
		puts("\n---- Second matrix: ----");
		fwrite_sm(stdout, q, true);
		if (q->height <= _mh && q->width <= _mw) {
			puts("\n==== (in the usual view) ====");
			fwrite_sm_as_m(stdout, q);
		}
		puts("\n---- Result: ----");
		fwrite_sm(stdout, res, true);
		if (res->height <= _mh && res->width <= _mw) {
			puts("\n==== (in the usual view) ====");
			fwrite_sm_as_m(stdout, res);
		}
		delete_sm(&res);

		print_ticks(_b - _a, "sparse");

		if (stat) {
			_c = tick();
			rc = multiply_matrices(&pp, &qq, &rr);
			_d = tick();
			if (rc != EXIT_SUCCESS) {
				fprintf(stderr, "hmm...\n");
			}
			else {
				free_matrix(&rr);
				print_ticks(_d - _c, "simple");
			}
		}

	}

	my_perror(rc);

	if (stat) {
		free_matrix(&pp);
		free_matrix(&qq);
	}

	delete_sm(&p);
	delete_sm(&q);
}



//———————————————————————————————————————————————————————————————————————— tick

ULL tick(void)
{
	ULL d;
	__asm__ __volatile__ ("rdtsc" : "=A" (d) );
	return d;
}

void print_ticks(ULL ticks, const char *prompt) {
	double ms = (double) ticks / 5E8;
	printf("\n**** [%s] sec: %.5lf ****\n", prompt, ms);
}
