#include "bigfloat.h"

#define N 21

void test_str_to_bigfloat()
{
	printf("test_str_to_bigfloat:\n");

	char s[N][16] =
	{
//		"123456789012345", <—— MAX
		"-123.456e-789",
		"+123.456E+789",
		"1234567890",
		"12345e6789",
		"+.12",
		".123e-456",
		"0",
		"00000",
		"00000.00000",
		".0000",
		"0.0e0",
		"+.0E-000",
		"",
		"hehe huhu",
		"e+123",
		"1.0e+",
		".",
		"+",
		"-.",
		"-.e+10",
		"-001.200e-05f"
	};

	int c[N] =
	{
		SUCCESS,
		SUCCESS,
		SUCCESS,
		SUCCESS,
		SUCCESS,
		SUCCESS,
		SUCCESS,
		SUCCESS,
		SUCCESS,
		SUCCESS,
		SUCCESS,
		SUCCESS,
		EMPTY_STRING_ERROR,
		INVALID_STRING_ERROR,
		INVALID_STRING_ERROR,
		INVALID_STRING_ERROR,
		INVALID_STRING_ERROR,
		INVALID_STRING_ERROR,
		INVALID_STRING_ERROR,
		INVALID_STRING_ERROR,
		INVALID_STRING_ERROR
	};

	for (int i = 0; i != N; ++i)
	{
		BigFloat bf;

		int rc = str_to_bigfloat(s[i], &bf);

		printf("test %2d: %15s (%3d): ", i + 1, s[i], c[i]);

		if (rc == c[i])
		{
			printf("passed\n");
		}
		else
		{
			printf("failed (got %d)\n", rc);
		}
	}
}

int main(void)
{
	test_str_to_bigfloat();
}
