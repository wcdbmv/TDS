#include "io_ext.h"

void display(const char *text, const char *title) {
	assert(text && title);
	const size_t len = strlen(title);
	printf("\n---- %s ", title);
	for (size_t i = 0; i < 77-len-6; ++i) {
		putchar('-');
	}
	printf("\n%s", text);
}

void strip(char *raw, char **begin) {
	assert(raw && begin); //
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
	assert(s && prompt);
	char raw[STR_LIMIT];
	printf("%s", prompt);
	fgets(raw, STR_LIMIT, stdin);
	char *stripped;
	strip(raw, &stripped);
	strcpy(s, stripped);
}

void get_filename(char *filename, const char *dir) {
	assert(filename && dir);
	char stripped_filename[STR_LIMIT];
	get_string(stripped_filename, "\nInput filename: ");
	strcpy(filename, dir);
	strcat(filename, stripped_filename);
}

void get_file(FILE **file, const char *mode, const char *dir) {
	assert(file && mode && dir);
	if (dir_is_empty(dir)) {
		puts("There are no files.");
		*file = NULL;
	}
	char filename[STR_LIMIT];
	if (!strcmp(mode, "r")) {
		while (true) {
			get_filename(filename, dir);
			if (file_exists(filename)) {
				*file = fopen(filename, mode);
				if (*file)
					break;
				perror(filename);
			}
			puts("There is no such file.");
		}
	}
	else if (!strcmp(mode, "w")) {
		while (true) {
			get_filename(filename, dir);
			if (!file_exists(filename)) {
				*file = fopen(filename, mode);
				if (*file)
					break;
				perror(filename);
			}
			puts("File already exists.");
		}
	}
}

void get_var(void *var, const char *f, const char *prompt, check_t check, void *_) {
	char frm[STR_LIMIT];
	strcpy(frm, f);
	strcat(frm, "%c"); // ono ono
	int rc;
	while (true) {
		printf("%s", prompt);
		char c;
		if ((rc = scanf(frm, var, &c)) == 2) {
			if (c != '\n') {
				my_perror(INVALID_INPUT_ERROR);
				char s[STR_LIMIT];
				scanf("%s", s); // omagad
				continue;
			}
			if (!check || (rc = check(var, _)) == EXIT_SUCCESS)
				break;
			my_perror(rc);
			continue;
		}
		char s[STR_LIMIT];
		scanf("%s", s); // omagad
		my_perror(INVALID_INPUT_ERROR);
	}
}

int fget_arr(FILE *stream, size_t nmemb, size_t size, void *a, const char *f) {
	assert(stream && a && f);

	int rc;
	for (size_t i = 0; i != nmemb; ++i)
		if ((rc = fscanf(stream, f, (char *) a + i * size)) != 1)
			return rc ? UNEXPECTED_EOF_EROR : INVALID_INPUT_ERROR;

	return EXIT_SUCCESS;
}
