#include "dir_ext.h"

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

size_t nfiles_in_dir(const char *dirname) {
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
	return nfiles <= 0 ? 0 : (size_t) nfiles;
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

void ls(const char *dirname, const char *prompt) {
	DIR *dir;
	if (!(dir = opendir(dirname))) {
		perror(dirname);
		return;
	}
	puts(prompt);
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
