#include "interface.h"

int check_args(int argc, char *argv[])
{
	assert(argc > 1);

	if (argc > 2 || strcmp(argv[1], "--help"))
	{
		usage(stderr);
		return WRONG_USAGE_ERROR;
	}

	help();
	return SUCCESS;
}

int input_int(BigFloat *bf)
{
	char s[BUF_LIMIT];
	int rc;

	printf("Введите целое число%15c|\n%34c|\r>>> ", ' ', ' ');
	scanf("%s", s);

	if ((rc = str_to_bigfloat(s, bf)) == SUCCESS)
	{
		if (!is_int(bf))
		{
			return NOT_INT_ERROR;
		}
	}

	return rc;
}

int input_float(BigFloat *bf)
{
	char s[BUF_LIMIT];

	printf("Введите действительное число%6c|\n%34c|\r>>> ", ' ', ' ');
	scanf("%s", s);

	return str_to_bigfloat(s, bf);
}

void print_multiply(const BigFloat *bf)
{
	printf("Произведение этих чисел:\n");
	print_bigfloat(bf);
}
