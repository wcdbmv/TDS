#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <stddef.h>
#include "sparse_matrix.h"
#include "matrix.h"
#include "dir_ext.h"
#include "info.h"

#define DIR "sm/"

bool menu(void);
void sm_list(void);
void sm_display(void);
void sm_add(void);
void sm_fremove(void);
void sm_multiply(void);

#endif // __INTERFACE_H__
