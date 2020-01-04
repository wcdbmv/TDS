#include "bigfloat.h"

void set_zero(BigFloat *bf)
{
	bf->sign = false;
	bf->exponent = 0;
	bf->length = 1;
	memset(bf->mantissa, 0, MANTISSA_SIZE);
}

bool is_zero(const BigFloat *bf)
{
	return bf->length == 1 && bf->mantissa[0] == 0;
}

bool is_int(const BigFloat *bf)
{
	return is_zero(bf) || bf->exponent + 1 >= bf->length;
}

int str_to_bigfloat(const char *s, BigFloat *bf)
{
	bool is_neg = false;
	int exp = -1, exp_mult = 1;
	unsigned m_len = 0, exp_len = 0;

	if (!*s)
	{
		return EMPTY_STRING_ERROR;
	}

	if (*s == '-')
	{
		is_neg = true;
		++s;
	}
	else if (*s == '+')
	{
		++s;
	}

	bool maybe_zero = false;
	bool is_zero = false;

	// skip leading zeros
	while (*s == '0')
	{
		maybe_zero = true;
		++s;
	}

	uint8_t buf[BUF_LIMIT];
	while (isdigit(*s))
	{
		if (m_len < BUF_LIMIT)
		{
			buf[m_len++] = *s++ - '0';
			++exp;
		}
		else
		{
			return BUF_OVERFLOW_ERROR;
		}
	}

	if (*s == '.')
	{
		++s;

		if (!m_len)
		{
			while (*s == '0')
			{
				maybe_zero = true;
				++s;
				--exp;
			}
		}

		while (isdigit(*s))
		{
			if (m_len < BUF_LIMIT)
			{
				buf[m_len++] = *s++ - '0';
			}
			else
			{
				return BUF_OVERFLOW_ERROR;
			}
		}
	}

	if (!m_len)
	{
		if (!maybe_zero)
		{
			return INVALID_STRING_ERROR;
		}
	}

	// cut trailing zeros
	while (m_len && !buf[m_len-1])
	{
		--m_len;
	}

	if (!m_len)
	{
		is_zero = true;
	}

	if (tolower(*s) == 'e')
	{
		++s;

		if (*s == '-')
		{
			exp_mult = -1;
			++s;
		}
		else if (*s == '+')
		{
			++s;
		}

		bool exp_maybe_zero = false;

		// skip leading zeros
		while (*s == '0')
		{
			exp_maybe_zero = true;
			++s;
		}

		while (isdigit(*s))
		{
			size_t i = m_len + exp_len;
			if (i < BUF_LIMIT)
			{
				buf[i] = *s++ - '0';
				++exp_len;
			}
			else
			{
				return BUF_OVERFLOW_ERROR;
			}
		}

		if (!exp_len)
		{
			if (!exp_maybe_zero)
			{
				return INVALID_STRING_ERROR;
			}
		}
	}

	if (*s)
	{
		return INVALID_STRING_ERROR;
	}

	if (is_zero)
	{
		set_zero(bf);
		return SUCCESS;
	}

	bf->sign = is_neg;

	if (m_len > MANTISSA_SIZE)
	{
		return MANTISSA_OVERFLOW_ERROR;
	}

	for (unsigned i = 0; i != m_len; ++i)
	{
		bf->mantissa[i] = buf[m_len - i - 1];
	}

	bf->length = m_len;

	if (exp_len > EXP_LEN_LIMIT)
	{
		return EXPONENT_OVERFLOW_ERROR;
	}

	int pow = 1;
	for (int i = 0; i != exp_len; ++i)
	{
		exp += exp_mult * buf[m_len + exp_len - i - 1] * pow;
		pow *= 10;
	}

	bf->exponent = exp;

	return SUCCESS;
}

int multiply(const BigFloat *a, const BigFloat *b, BigFloat *c)
{
	// assert(a->sign | 1 == 1 && b->sign | 1 == 1);

	if (is_zero(a) || is_zero(b))
	{
		set_zero(c);
		return SUCCESS;
	}

	uint8_t buf[2 * MANTISSA_SIZE] = {0};
	uint8_t new_length = 1;
	for (int i = 0; i != a->length; ++i)
	{
		for (int j = 0; j != b->length; ++j)
		{
			int tmp = a->mantissa[i] * b->mantissa[j];
			int k = i + j;
			buf[k] += tmp;
			while ((tmp = buf[k] / 10) > 0)
			{
				buf[k++] %= 10;
				buf[k] += tmp;
			}
			if (k + 1 > new_length)
			{
				new_length = k + 1;
			}
		}
	}

	int exp = a->exponent + b->exponent + new_length - a->length - b->length + 1;

	if (abs(exp + 1) > EXPONENT_LIMIT)
	{
		return MULTIPLY_OVERFLOW_ERROR;
	}

	c->exponent = exp;
	c->sign = a->sign ^ b->sign;

	// cut trailing zeros
	int zeros = 0;
	while (new_length > zeros && !buf[zeros])
	{
		++zeros;
	}

	int real_new_length = new_length - zeros;
	if (real_new_length > MANTISSA_SIZE)
	{
		real_new_length = MANTISSA_SIZE;

		int k = new_length - MANTISSA_SIZE - 1;
		if (buf[k] >= 5)
		{
			int nines = 0;
			for (int n = k + 1; n < new_length; ++n)
			{
				if (buf[n] == 9)
				{
					++nines;
				}
				else
				{
					break;
				}
			}

			if (nines)
			{
				zeros += nines;
				real_new_length -= nines;

				if (!real_new_length)
				{
					++real_new_length;
					++new_length;
				}
			}
			++buf[k + nines + 1];
		}
	}
	c->length = real_new_length;

	int j = real_new_length - 1;
	int i = new_length - 1;
	for (; j >= 0; --i, --j)
	{
		c->mantissa[j] = buf[i];
	}

	return SUCCESS;
}

void print_bigfloat(const BigFloat *bf)
{
	if (is_zero(bf))
	{
		puts("0");
		return;
	}

	printf("%c0.", (bf->sign ? '-' : '+'));
	for (int i = bf->length - 1; i >= 0; --i)
	{
		printf("%d", bf->mantissa[i]);
	}
	printf("e");
	if (bf->exponent > 0)
	{
		printf("+");
	}
	printf("%d\n", bf->exponent + 1);
}
