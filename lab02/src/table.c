#include "table.h"

//——————————————————————————————————————————————————————————————————————— clear

void clear_table(table_t *table) {
	table->data = NULL;
	table->reserved = 0;
	table->size = 0;
}

void init_table(table_t *table) {
	clear_table(table);
}

bool table_is_clear(const table_t *table) {
	return !table->data && !table->reserved && !table->size;
}

bool table_isnt_clear(const table_t *table) {
	return table->data && table->reserved;
}

//———————————————————————————————————————————————————————————————————————— size

int create_table(table_t *table, const size_t reserve) {
	assert(table_is_clear(table));
	table->data = malloc(reserve * sizeof (country_t));
	if (!table->data) {
		return FAILED_ALLOC_ERROR;
	}
	table->reserved = reserve;
	table->size = 0;
	return SUCCESS;
}

void delete_table(table_t *table) {
	assert(table_isnt_clear(table));
	free(table->data);
	clear_table(table);
}

int resize_table(table_t *table, const size_t to) {
	assert(table_isnt_clear(table));
	assert(table->size <= to);
	table->data = realloc(table->data, to * sizeof (country_t));
	return table->data ? SUCCESS : FAILED_ALLOC_ERROR;
}

void copy_table(table_t *to, const table_t *from) {
	assert(to->reserved >= from->size);
	to->size = from->size;
	for (size_t i = 0; i != from->size; ++i) {
		copy_country(&to->data[i], &from->data[i]);
	}
}

//———————————————————————————————————————————————————————————————————————— file

// make short
int fget_row(FILE *file, table_t *table) {
	int rc;
	char s[STR_LIMIT];
	if ((rc = fscanf(file, "%s", s)) != 1) {
		if (rc == EOF) {
			return SUCCESS;
		}
		return INVALID_COUNTRY_NAME_ERROR;
	}
	if (table->size == table->reserved) {
		const size_t new_size = table->reserved + STD_RESERVE;
		if ((rc = resize_table(table, new_size)) != SUCCESS) {
			return rc; // FAILED_ALLOC_ERROR;
		}
	}
	static uint64_t ID = 0;
	int i = table->size++;
	country_t *curr_country = &table->data[i];
	if (!i)
		ID = 0;
	curr_country->id = ID++;
	if ((rc = set_name(s, curr_country)) != SUCCESS) {
		return rc; // INVALID_COUNTRY_NAME_ERROR
	}
	if ((rc = fget_population(file, curr_country)) != SUCCESS) {
		return rc;
	}
	if ((rc = fget_capital(file, curr_country)) != SUCCESS) {
		return rc;
	}
	if ((rc = fget_continent(file, curr_country)) != SUCCESS) {
		return rc;
	}
	if ((rc = fget_tourism(file, curr_country)) != SUCCESS) {
		return rc;
	}
	switch (curr_country->tourism) {
		case excursion:
			rc = fget_excursion(file, curr_country);
			break;
		case beach:
			rc = fget_beach(file, curr_country);
			break;
		case sports:
			rc = fget_sports(file, curr_country);
			break;
	}
	return rc; // INVALID_TOURISM_DATA_ERROR : SUCCESS
}

int fget_table(FILE *file, table_t *table) {
	assert(table_is_clear(table));
	create_table(table, STD_RESERVE);
	int rc;
	while (!feof(file)) {
		if ((rc = fget_row(file, table)) != SUCCESS) {
			if (rc != FAILED_ALLOC_ERROR) {
				delete_table(table);
			}
			return rc;
		}
	}
	return rc; // SUCCESS
}

void write_continent(FILE *file, const continent_t continent) {
	char s[STR_LIMIT];
	str_continent(s, continent);
	fprintf(file, "%-15s ", s);
}

void write_tourism(FILE *file, const tourism_t tourism) {
	char s[STR_LIMIT];
	str_tourism(s, tourism);
	fprintf(file, "%-11s", s);
}

void write_tourism_data(FILE *file, const country_t *country) {
	const tourism_data_t tourism_data = country->tourism_data;
	char s[STR_LIMIT];
	switch (country->tourism) {
		case excursion:
			str_excursion_basic(s, tourism_data.excursion.basic);
			fprintf(file, "%lu %s\n", tourism_data.excursion.objects, s);
			break;
		case beach:
			str_season(s, tourism_data.beach.season);
			const int8_t air = tourism_data.beach.air_temp;
			const int8_t water = tourism_data.beach.water_temp;
			const uint16_t flight = tourism_data.beach.flight_time;
			fprintf(file, "%s %hhd %hhd %hu\n", s, air, water, flight);
			break;
		case sports:
			str_sports_basic(s, tourism_data.sports.basic);
			fprintf(file, "%s %u\n", s, tourism_data.sports.min_cost);
			break;
	}
}

void write_country(FILE *file, const country_t *country, bool id) {
	if (id)
		fprintf(file, "%03lu  ", country->id);
	fprintf(file, "%-15s ", country->name);
	fprintf(file, "%-9lu ", country->population);
	fprintf(file, "%-15s ", country->capital);
	write_continent(file, country->continent);
	write_tourism(file, country->tourism);
	write_tourism_data(file, country);
}

void write_table(FILE *file, const table_t *table, bool id) {
	for (size_t i = 0; i != table->size; ++i) {
		write_country(file, &table->data[i], id);
	}
}

void print_table(const table_t *table, bool id) {
	write_table(stdout, table, id);
}

//———————————————————————————————————————————————————————————————————————— sort
//                             by population

ULL tick(void)
{
	ULL d;
	__asm__ __volatile__ ("rdtsc" : "=A" (d) );
	return d;
}

void print_ticks(ULL ticks) {
	double ms = (double) ticks / 1E9;
	printf("\nTicks: %llu, sec: %.5lf\n", ticks, ms);
}

void copy_country(country_t *to, const country_t *from) {
	strcpy(to->name, from->name);
	strcpy(to->capital, from->capital);
	to->population = from->population;
	to->continent = from->continent;
	to->tourism = from->tourism;
	to->tourism_data = from->tourism_data;
	to->id = from->id;
}

void swap_countries(country_t *a, country_t *b) {
	country_t tmp;
	copy_country(&tmp, a);
	copy_country(a, b);
	copy_country(b, &tmp);
}

void sort_table(table_t *table) {
	for (int i = 0; i < table->size - 1; ++i) {
		int swaps = 0;
		for (int j = 0; j < table->size - i - 1; ++j) {
			if (table->data[j].population < table->data[j + 1].population) {
				swap_countries(&table->data[j], &table->data[j + 1]);
				++swaps;
			}
		}
		if (!swaps)
			return;
	}
}

void sort_table2(table_t *table) {
	for (int i = 0; i < table->size - 1; ++i) {
		int i_max = i;
		for (int j = i; j < table->size; ++j) {
			if (table->data[j].population > table->data[i_max].population) {
				i_max = j;
			}
		}
		if (i != i_max)
			swap_countries(&table->data[i], &table->data[i_max]);
	}
}

void init_keys(key_t *k, const table_t *table) {
	for (size_t i = 0; i < table->size; ++i) {
		country_t *curr_country = &table->data[i];
		k[i].id = curr_country->id;
		k[i].population = curr_country->population;
	}
}

void swap_keys(key_t *k1, key_t *k2) {
	key_t tmp_k = *k1;
	*k1 = *k2;
	*k2 = tmp_k;
}

void sort_keys(key_t *k, size_t size) {
	for (int i = 0; i < size - 1; ++i) {
		int swaps = 0;
		for (int j = 0; j < size - i - 1; ++j) {
			if (k[j].population < k[j + 1].population) {
				swap_keys(k + j, k + j + 1);
				++swaps;
			}
		}
		if (!swaps)
			return;
	}
}

void sort_keys2(key_t *k, size_t size) {
	for (int i = 0; i < size - 1; ++i) {
		int i_max = i;
		for (int j = i; j < size; ++j) {
			if (k[j].population > k[i_max].population) {
				i_max = j;
			}
		}
		if (i != i_max)
			swap_keys(k + i, k + i_max);
	}
}

void print_keys(key_t *k, size_t size) {
	puts("\n ID  POPULATION");
	for (size_t i = 0; i < size; ++i) {
		printf("%03lu  %-7lu\n", k[i].id, k[i].population);
	}
}

size_t find_row_by_id(const table_t *table, const uint64_t id) {
	size_t i = 0;
	for (; i != table->size; ++i)
		if (table->data[i].id == id)
			break;
	return i;
}

// unstable
void sort_table_by_keys(const table_t *table, const key_t *k, table_t *sorted_table, ULL *ticks) {
	create_table(sorted_table, table->size);
	sorted_table->size = sorted_table->reserved;
	ULL tb = tick();
	for (size_t i = 0; i != table->size; ++i) {
		size_t j = find_row_by_id(table, k[i].id);
		if (j >= table->size) {
			puts("Check the code here");
			return;
		}
		copy_country(&sorted_table->data[i], &table->data[j]);
	}
	ULL te = tick();
	*ticks = te - tb;
}

// i'm so tired
// this is unsightly
// go out

ULL get_ticks_sort_table(const table_t *table) {
	if (!table->size) {
		return 0;
	}
	table_t tmp;
	init_table(&tmp);
	create_table(&tmp, table->size);
	copy_table(&tmp, table);
	ULL tb = tick();
	sort_table(&tmp);
	ULL te = tick();
	delete_table(&tmp);
	return te - tb;
}

ULL get_ticks_sort_table2(const table_t *table) {
	if (!table->size) {
		return 0;
	}
	table_t tmp;
	init_table(&tmp);
	create_table(&tmp, table->size);
	copy_table(&tmp, table);
	ULL tb = tick();
	sort_table2(&tmp);
	ULL te = tick();
	delete_table(&tmp);
	return te - tb;
}

ULL get_ticks_sort_keys(const table_t *table) {
	if (!table->size) {
		return 0;
	}
	key_t k[table->size];
	init_keys(k, table);
	ULL tb = tick();
	sort_keys(k, table->size);
	ULL te = tick();
	return te - tb;
}

ULL get_ticks_sort_keys2(const table_t *table) {
	if (!table->size) {
		return 0;
	}
	key_t k[table->size];
	init_keys(k, table);
	ULL tb = tick();
	sort_keys2(k, table->size);
	ULL te = tick();
	return te - tb;
}

ULL get_ticks_sort_table_by_keys(const table_t *table) {
	if (!table->size) {
		return 0;
	}
	key_t k[table->size];
	init_keys(k, table);
	ULL tb = tick();
	sort_keys(k, table->size);
	ULL te = tick();
	table_t sorted_table;
	init_table(&sorted_table);
	ULL ticks;
	sort_table_by_keys(table, k, &sorted_table, &ticks);
	delete_table(&sorted_table);
	return te - tb + ticks;
}

ULL get_ticks_sort_table_by_keys2(const table_t *table) {
	if (!table->size) {
		return 0;
	}
	key_t k[table->size];
	init_keys(k, table);
	ULL tb = tick();
	sort_keys2(k, table->size);
	ULL te = tick();
	table_t sorted_table;
	init_table(&sorted_table);
	ULL ticks;
	sort_table_by_keys(table, k, &sorted_table, &ticks);
	delete_table(&sorted_table);
	return te - tb + ticks;
}
