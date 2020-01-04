#ifndef __TABLE_H__
#define __TABLE_H__

#include <stdbool.h>
#include <time.h>
#include "country.h"

#define STD_RESERVE 64

typedef struct {
	country_t *data;
	size_t size;
	size_t reserved;
} table_t;

void clear_table(table_t *table);
void init_table(table_t *table);
bool table_is_clear(const table_t *table);
bool table_isnt_clear(const table_t *table);

int create_table(table_t *table, const size_t reserve);
void delete_table(table_t *table);
int resize_table(table_t *table, const size_t to);
void copy_table(table_t *to, const table_t *from);

int fget_row(FILE *file, table_t *table);
int fget_table(FILE *file, table_t *table);

void write_continent(FILE *file, const continent_t continent);
void write_tourism(FILE *file, const tourism_t tourism);
void write_tourism_data(FILE *file, const country_t *country);
void write_country(FILE *file, const country_t *country, bool id);
void write_table(FILE *file, const table_t *table, bool id);
void print_table(const table_t *table, bool id);

typedef unsigned long long ULL;
ULL tick(void);
void print_ticks(ULL ticks);

void copy_country(country_t *to, const country_t *from);
void swap_countries(country_t *a, country_t *b);
void sort_table(table_t *table);
void sort_table2(table_t *table);

typedef struct {
	uint64_t id;
	uint64_t population;
} key_t;
void init_keys(key_t *k, const table_t *table);
void swap_keys(key_t *k1, key_t *k2);
void sort_keys(key_t *k, size_t size);
void sort_keys2(key_t *k, size_t size);
void print_keys(key_t *k, size_t size);

size_t find_row_by_id(const table_t *table, const uint64_t id);
void sort_table_by_keys(const table_t *, const key_t *, table_t *, ULL *);

ULL get_ticks_sort_table(const table_t *table);
ULL get_ticks_sort_table2(const table_t *table);
ULL get_ticks_sort_keys(const table_t *table);
ULL get_ticks_sort_keys2(const table_t *table);
ULL get_ticks_sort_table_by_keys(const table_t *table);
ULL get_ticks_sort_table_by_keys2(const table_t *table);

#endif // __TABLE_H__
