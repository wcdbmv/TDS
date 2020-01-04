#pragma once

#include "stack_array.h"
#include "stack_linked_list.h"

#include <algorithm>
#include <iostream>

struct Calculator {
public:
	Calculator(const std::string &stack_stype);
	~Calculator();

	double calculate(const std::string &infix);
protected:
	std::string infix_to_postfix_(const std::string &infix);

	IStack<double> *stack_;
};

double str_to_double(std::string str);
int    str_is_double(const char *s);

#define INFIX_ERR -34613597
#define DIVISION_BY_ZERO -6547913246
#define DOUBLE_ERR -99513723

#define SUCCESS 0
#define WRONG_USAGE_ERROR -1
#define EMPTY_STRING_ERROR -2
#define INVALID_STRING_ERROR -3
#define BUF_OVERFLOW_ERROR -4
#define MANTISSA_OVERFLOW_ERROR -5
#define EXPONENT_OVERFLOW_ERROR -6
#define NOT_INT_ERROR -7
#define MULTIPLY_OVERFLOW_ERROR -8

#define MANTISSA_SIZE 18
#define EXPONENT_LIMIT 1000
#define EXP_LEN_LIMIT 4

#define BUF_LIMIT 120
