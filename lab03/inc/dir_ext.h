#ifndef __DIR_EXT_H__
#define __DIR_EXT_H__

#include <stdbool.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

bool dir_is_empty(const char *dirname);
size_t nfiles_in_dir(const char *dirname);
bool file_exists(const char *filename);
void clear_file(const char *filename);
void ls(const char *dirname, const char *prompt);

#endif // __DIR_EXT_H__
