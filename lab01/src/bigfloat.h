#ifndef __BIGFLOAT_H__
#define __BIGFLOAT_H__

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "errcodes.h"

#define MANTISSA_SIZE 30
#define EXPONENT_LIMIT 99999
#define EXP_LEN_LIMIT 5

#define BUF_LIMIT 512

typedef struct
{
	int exponent;
	uint8_t mantissa[MANTISSA_SIZE];
	uint8_t length;
	bool sign;
} BigFloat;

void set_zero(BigFloat *bf);
bool is_int(const BigFloat *bf);
int str_to_bigfloat(const char *s, BigFloat *bf);
int multiply(const BigFloat *a, const BigFloat *b, BigFloat *c);
void print_bigfloat(const BigFloat *bf);

#endif // __BIGFLOAT_H__
