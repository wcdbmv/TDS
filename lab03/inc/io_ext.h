#ifndef __IO_EXT_H__
#define __IO_EXT_H__

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "errcodes.h" // for fget_arr
#include "dir_ext.h"
#include "info.h"

#define STR_LIMIT 64

void display(const char *text, const char *title);

typedef int (*check_t)(void *, void *);

void strip(char *raw, char **begin);
void get_string(char *s, const char *prompt);
void get_filename(char *filename, const char *dir);
void get_file(FILE **file, const char *mode, const char *dir);
void get_var(void *var, const char *f, const char *prompt, check_t, void *);


int fget_arr(FILE *stream, size_t nmemb, size_t size, void *a, const char *f);

#endif // __IO_EXT_H__
