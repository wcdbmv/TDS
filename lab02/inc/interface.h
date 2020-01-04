#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <dirent.h>
#include "table.h"
#include "info.h"

void display(const char *text, const char *title);

void strip(char *raw, char **begin);
void get_string(char *s, const char *prompt);
void get_filename(char *filename);
bool dir_is_empty(const char *dirname);
bool file_exists(const char *filename);
void clear_file(const char *filename);

void save_table(void);

void db_fcreate(void);
void db_fremove(void);
void db_fdisplay(void);
void db_display(void);
bool db_add(void);
void db_search(void);
void db_delete(void);
void db_sort(void);
void db_sort_keys(void);
void db_show_table_by_sort_keys(void);
void db_show_statistics(void);

bool db_menu(void);
bool menu(void);

#endif // __INTERFACE_H__
