#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <assert.h>
#include "bigfloat.h"
#include "info.h"

int check_args(int argc, char *argv[]);
int input_int(BigFloat *bf);
int input_float(BigFloat *bf);
void print_multiply(const BigFloat *bf);

#endif // __INTERFACE_H__
