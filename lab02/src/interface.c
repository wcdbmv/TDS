#include "interface.h"

// TODO: if empty table, do not print title

//—————————————————————————————————————————————————————————————————————— common

static char db_name[STR_LIMIT];
static table_t table;

static const char menu_info[] =
	"1. Create table\n"
	"2. Open table\n"
	"3. Delete table\n"
	"4. List tables\n"
	"0. Exit\n"
;

static const char db_menu_info[] =
	"1. Show table\n"
	"2. Add row to table\n"
	"3. Search\n"
	"4. Delete\n"
	"5. Show sorted table\n"
	"6. Show sorted keys\n"
	"7. Show table by sorted keys\n"
	"8. Show statistics\n"
	"0. Exit to start menu\n"
;

static const size_t nkeys = 5;
static const char *keys[] = {
	"COUNTRY",
	"POPULATION",
	"CAPITAL",
	"CONTINENT",
	"TOURISM",
};

int (*fget_func[])(FILE *, country_t *) = {
	fget_name,
	fget_population,
	fget_capital,
	fget_continent,
	fget_tourism
};

void display(const char *text, const char *title) {
	const size_t len = strlen(title);
	printf("\n---- %s ", title);
	for (size_t i = 0; i < 77-len-6; ++i) {
		putchar('-');
	}
	printf("\n%s", text);
}

void strip(char *raw, char **begin) {
	*begin = raw;
	while (isspace(**begin)) {
		++*begin;
	}
	char *end = *begin + strlen(*begin) - 1;
	while (*begin < end && isspace(*end)) {
		--end;
	}
	end[1] = '\0';
}

void get_string(char *s, const char *prompt) {
	char raw[STR_LIMIT];
	printf("%s", prompt);
	fgets(raw, STR_LIMIT, stdin);
	char *stripped;
	strip(raw, &stripped);
	strcpy(s, stripped);
}

void get_filename(char *filename) {
	char stripped_filename[STR_LIMIT];
	get_string(stripped_filename, "\nInput filename: ");
	strcpy(filename, "db/");
	strcat(filename, stripped_filename);
}

bool dir_is_empty(const char *dirname) {
	DIR *dir = opendir(dirname);
	if (!dir) {
		perror(dirname);
		return false;
	}
	struct dirent *ent;
	int nfiles = -2;
	while ((ent = readdir(dir))) {
		++nfiles;
	}
	closedir(dir);
	return nfiles <= 0;
}

bool file_exists(const char *filename) {
	FILE *file = fopen(filename, "r");
	if (file) {
		fclose(file);
		return true;
	}
	return false;
}

void clear_file(const char *filename) {
	FILE *file = fopen(filename, "w");
	if (!file) {
		perror(filename);
	}
	fclose(file);
}

//———————————————————————————————————————————————————————————————————————— file

void db_fcreate(void) {
	while (true) {
		char filename[STR_LIMIT];
		get_filename(filename);
		if (file_exists(filename)) {
			puts("File already exist.");
			continue;
		}

		clear_file(filename);
		break;
	}
}

bool db_fopen(void) {
	if (dir_is_empty("db")) {
		puts("There are no files.");
		return false;
	}
	while (true) {
		get_filename(db_name);
		if (file_exists(db_name)) {
			FILE *db = fopen(db_name, "r");
			if (!db) {
				perror(db_name);
				return false;
			}
			init_table(&table);
			int rc = fget_table(db, &table);
			if (rc != SUCCESS && rc != EMPTY_INPUT_FILE_ERROR) {
				my_perror(rc);
				fclose(db);
				return false;
			}
			fclose(db);
			return true;
		}
		puts("There is no such file.");
	}
}

// almost the same as db_fopen
void db_fremove(void) {
	if (dir_is_empty("db")) {
		puts("There are no files.");
		return;
	}
	while (true) {
		char filename[STR_LIMIT];
		get_filename(filename);
		if (file_exists(filename)) {
			if (remove(filename)) {
				perror(filename);
			}
			else {
				puts("File deleted successful.");
			}
			return;
		}
		puts("There is no such file.");
	}
}

void db_fdisplay(void) {
	DIR *dir;
	if (!(dir = opendir("db"))) {
		perror("db");
		return;
	}
	puts("\nList of databases:");
	struct dirent *ent;
	int nfiles = 0;
	while ((ent = readdir(dir))) {
		if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, "..")) {
			puts(ent->d_name);
			++nfiles;
		}
	}
	closedir(dir);
	if (!nfiles) {
		puts("There are no files.");
	}
}

void print_title(void) {
	puts("\n ID  COUNTRY       POPULATION  CAPITAL         CONTINENT       TOURISM    VARIATIVE");
}

void db_display(void) {
	print_title();
	print_table(&table, true);
}

void save_table(void) {
	FILE *db = fopen(db_name, "w");
	if (!db) {
		perror(db_name);
	}
	else {
		write_table(db, &table, false);
		fclose(db);
	}
}

bool db_add(void) {
	country_t new_country;
	for (size_t i = 0; i != nkeys; ++i) {
		while (true) {
			printf("%s: ", keys[i]);
			int rc = fget_func[i](stdin, &new_country);
			// write_country(stdout, &new_country, false);
			if (rc == SUCCESS) {
				break;
			}
			my_perror(rc);
		}
	}
	puts("Note: in variative part enter values separated by a space.");
	char prompt[64];
	int (*fget_table_data_func)(FILE *, country_t *);
	switch (new_country.tourism) {
		case excursion:
			strcpy(prompt, "EXCURSION (objects, basic)");
			fget_table_data_func = fget_excursion;
			break;
		case beach:
			strcpy(prompt, "BEACH (season, air temp, water temp, flight time)");
			fget_table_data_func = fget_beach;
			break;
		case sports:
			strcpy(prompt, "SPORTS (basic, min cost)");
			fget_table_data_func = fget_sports;
			break;
		default:
			fprintf(stderr, "what a heck\n");
			break;
	}
	while (true) {
		printf("%s: ", prompt);
		int rc = fget_table_data_func(stdin, &new_country);
		if (rc == SUCCESS) {
			break;
		}
		my_perror(rc);
	}
	char c;
	scanf("%c", &c); // first crutch
	if (table.size == table.reserved) {
		const size_t new_size = table.reserved + STD_RESERVE;
		if (resize_table(&table, new_size) != SUCCESS) {
			return false; // FAILED_ALLOC_ERROR;
		}
	}
	new_country.id = table.size ? table.data[table.size - 1].id + 1 : 0;
	copy_country(&table.data[table.size++], &new_country);
	save_table();
	return true;
}

// i'm tired

void input_continent(country_t *country) {
	while (true) {
		printf("%s: ", keys[3]);
		int rc = fget_continent(stdin, country);
		if (rc == SUCCESS) {
			break;
		}
		my_perror(rc);
	}
	char c;
	scanf("%c", &c); // second crutch
}

void input_tourism(country_t *country) {
	while (true) {
		printf("%s: ", keys[4]);
		int rc = fget_tourism(stdin, country);
		if (rc == SUCCESS) {
			break;
		}
		my_perror(rc);
	}
	char c;
	scanf("%c", &c); // second crutch
}

void db_search(void) {
	if (!table.size) {
		puts("Table is empty.");
		return;
	}
	puts("\nSearch by continent and tourism.\n");
	country_t tmp_country;
	input_continent(&tmp_country);
	input_tourism(&tmp_country);
	bool title = true;
	for (size_t i = 0; i != table.size; ++i) {
		country_t *curr_country = &table.data[i];
		if (curr_country->continent == tmp_country.continent
		 && curr_country->tourism == tmp_country.tourism) {
			if (title) {
				print_title();
				title = false;
			}
			write_country(stdout, curr_country, true);
		}
	}
	if (title) {
		printf("No matches.\n");
	}
}

// thus seems ugly, next lab will be better

/*
void db_delete(void) {
	if (!table.size) {
		puts("Table is empty.");
		return;
	}
	puts("\nSearch by continent and tourism.\n");
	country_t tmp_country;
	input_continent(&tmp_country);
	input_tourism(&tmp_country);
	for (int i = 0; i < table.size; ++i) {
		if (table.data[i].continent == tmp_country.continent
		 && table.data[i].tourism == tmp_country.tourism) {
			--table.size;
			for (int j = i--; j < table.size; ++j) {
				table.data[j] = table.data[j + 1];
			}
		}
	}
	save_table();
}
*/

void db_delete(void) {
	if (!table.size) {
		puts("Table is empty.");
		return;
	}
	uint64_t id;
	while (true) {
		printf("\nInput id: ");
		if (scanf("%lu", &id) == 1 && id < table.size)
			break;
		puts("Wrong id");
	}
	for (size_t i = id; i < table.size; ++i) {
		copy_country(&table.data[i], &table.data[i + 1]);
		table.data[i].id = i;
	}
	--table.size;
	puts("Delete successful.");
	char c;
	scanf("%c", &c); // second crutch
}

void db_sort(void) {
	if (!table.size) {
		puts("Table is empty.");
		return;
	}
	puts("\nSorted by population.");
	table_t tmp;
	init_table(&tmp);
	create_table(&tmp, table.size);
	copy_table(&tmp, &table);
	ULL tb = tick();
	sort_table(&tmp);
	ULL te = tick();
	print_title();
	print_table(&tmp, true);
	print_ticks(te - tb);
	delete_table(&tmp);
}

void db_sort_keys(void) {
	if (!table.size) {
		puts("Table is empty.");
		return;
	}
	puts("\nSorted by population.");
	key_t k[table.size];
	init_keys(k, &table);
	ULL tb = tick();
	sort_keys(k, table.size);
	ULL te = tick();
	print_keys(k, table.size);
	print_ticks(te - tb);
}

void db_show_table_by_sort_keys(void) {
	if (!table.size) {
		puts("Table is empty.");
		return;
	}
	puts("\nSorted by population.");
	key_t k[table.size];
	init_keys(k, &table);
	ULL tb = tick();
	sort_keys(k, table.size);
	ULL te = tick();
	table_t sorted_table;
	init_table(&sorted_table);
	ULL ticks;
	sort_table_by_keys(&table, k, &sorted_table, &ticks);
	print_title();
	print_table(&sorted_table, true);
	delete_table(&sorted_table);
	print_ticks(te - tb + ticks);
}

void db_show_statistics(void) {
	if (!table.size) {
		puts("Table is empty.");
		return;
	}
	ULL s1 = 0, s2 = 0, k1 = 0, k2 = 0, sk1 = 0, sk2 = 0;
	for (int i = 0; i != 10; ++i) {
		s1 += get_ticks_sort_table(&table);
		s2 += get_ticks_sort_table2(&table);
		k1 += get_ticks_sort_keys(&table);
		k2 += get_ticks_sort_keys2(&table);
		sk1 += get_ticks_sort_table_by_keys(&table);
		sk2 += get_ticks_sort_table_by_keys2(&table);
	}
	puts("");
	printf("---- Bubble sort table ----");
	print_ticks(s1);
	printf("---- Selection sort table ----");
	print_ticks(s2);
	printf("---- Bubble sort keys ----");
	print_ticks(k1);
	printf("---- Selection sort keys ----");
	print_ticks(k2);
	printf("---- Bubble sort table by keys ----");
	print_ticks(sk1);
	printf("---- Selection sort table by keys ----");
	print_ticks(sk2);
}

//———————————————————————————————————————————————————————————————————————— menu

bool db_menu(void) {
	display(db_menu_info, "DB Menu:");
	char command[STR_LIMIT];
	get_string(command, "\nInput command: ");
	if (!strcmp(command, "1")) {
		db_display();
	}
	else if (!strcmp(command, "2")) {
		if (!db_add()) {
			my_perror(FAILED_ALLOC_ERROR);
			return false;
		}
	}
	else if (!strcmp(command, "3")) {
		db_search();
	}
	else if (!strcmp(command, "4")) {
		db_delete();
	}
	else if (!strcmp(command, "5")) {
		db_sort();
	}
	else if (!strcmp(command, "6")) {
		db_sort_keys();
	}
	else if (!strcmp(command, "7")) {
		db_show_table_by_sort_keys();
	}
	else if (!strcmp(command, "8")) {
		db_show_statistics();
	}
	else if (!strcmp(command, "0")) {
		puts("Exiting..");
		delete_table(&table);
		return false;
	}
	else {
		puts("Unfortunately, there is no such command :с");
		puts("Please try again.");
	}
	return true;
}

bool menu(void) {
	display(menu_info, "Menu:");
	char command[STR_LIMIT];
	get_string(command, "\nInput command: ");
	if (!strcmp(command, "1")) {
		db_fcreate();
	}
	else if (!strcmp(command, "2")) {
		if (db_fopen()) {
			while (true) {
				if (!db_menu()) {
					break;
				}
			}
		}
	}
	else if (!strcmp(command, "3")) {
		db_fremove();
	}
	else if (!strcmp(command, "4")) {
		db_fdisplay();
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
