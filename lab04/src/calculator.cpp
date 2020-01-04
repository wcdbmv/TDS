#include "calculator.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include "parser.cpp"

Calculator::Calculator(const std::string &stack_type) {
	if (stack_type == "array")
		stack_ = new StackArray<double>();
	else if (stack_type == "linked_list")
		stack_ = new StackLinkedList<double>();
}

Calculator::~Calculator() {
	delete stack_;
}

double Calculator::calculate(const std::string &infix) {
	std::string postfix = infix_to_postfix_(infix);
	if (!postfix.size())
		return INFIX_ERR;

	stack_->clear();

	std::string oss(postfix);
	std::istringstream iss(postfix);
	std::string str("");

	while (iss >> str) {

		printf("\033[1;1H\033[JQueue| ");
		std::cout << oss;
		oss = oss.substr(oss.find_first_of(" \t")+1);
		printf("\nStack| ");
		stack_->print();
		puts("\n\n<press enter>");
		getchar();

		if (str_is_double(str.c_str()) == SUCCESS)
			stack_->push(str_to_double(str));
		else if (str.size() == 1) {
			if (stack_->size() < 2)
				throw std::underflow_error("stack size < 2");
			const double b = stack_->pop();
			const double a = stack_->pop();
			double res = 0;
			if (str[0] == '+')
				res = a + b;
			else if (str[0] == '-')
				res = a - b;
			else if (str[0] == '*')
				res = a * b;
			else if (str[0] == '/') {
				if (b < 1E-9)
					return DIVISION_BY_ZERO;
				res = a / b;
			}
			else if (str[0] == '^') {
				res = pow(a, b);
			}
			else
				return DOUBLE_ERR;
			stack_->push(res);
		}
		else
			return DOUBLE_ERR;
	}

	printf("\033[1;1H\033[JQueue| ");
	std::cout << oss;
	oss = oss.substr(oss.find_first_of(" \t")+1);
	printf("\nStack| ");
	stack_->print();
	puts("\n\n<press enter>");
	getchar();


	return stack_->top();
}


std::string Calculator::infix_to_postfix_(const std::string &infix) {
	const char *cstr = infix.c_str();

	static int __init = init();
	if (!__init)
		return std::string("");

	std::stringstream ss;

	if (parse(cstr)) {
		char buf[32];

		for (int i = 0; i < l_queue; i++) {
			int res = snprintf(buf, sizeof buf, "%.*s ", queue[i].len, queue[i].s);
				if (res <= 0 || res >= 32)
					return std::string("");
			std::string str(buf);
			ss << str;
		}

		return ss.str();
	}
	else
		return std::string("");
}

double str_to_double (std::string str) {
	std::stringstream ss;
	double temp(0);
	ss << str;
	ss >> temp;
	ss.clear();
	return temp;
}

int str_is_double(const char *s)
{
	// bool is_neg = false;
	int exp = -1;  //exp_mult = 1;
	unsigned m_len = 0, exp_len = 0;

	if (!*s)
		return EMPTY_STRING_ERROR;

	if (*s == '-')
	{
		// is_neg = true;
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
			if (m_len < BUF_LIMIT)
				buf[m_len++] = *s++ - '0';
			else
				return BUF_OVERFLOW_ERROR;
	}

	if (!m_len && !maybe_zero)
			return INVALID_STRING_ERROR;

	// cut trailing zeros
	while (m_len && !buf[m_len-1])
		--m_len;

	if (!m_len)
		is_zero = true;

	if (tolower(*s) == 'e')
	{
		++s;

		if (*s == '-')
		{
			// exp_mult = -1;
			++s;
		}
		else if (*s == '+')
			++s;

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
				return BUF_OVERFLOW_ERROR;
		}

		if (!exp_len && !exp_maybe_zero)
				return INVALID_STRING_ERROR;
	}

	if (*s)
		return INVALID_STRING_ERROR;

	if (is_zero)
		return SUCCESS;

	if (m_len > MANTISSA_SIZE)
		return MANTISSA_OVERFLOW_ERROR;

	if (exp_len > EXP_LEN_LIMIT)
		return EXPONENT_OVERFLOW_ERROR;

	return SUCCESS;
}
