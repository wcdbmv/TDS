#include "operations.h"

//———————————————————————————————————————————————————————————————————————— plus

double PlusOp::operation(char op, double a, double b, double) {
	if (op != '+')
		throw std::logic_error("Operation other than Plus (+) are not supported");

	return a + b;
}

IOperation::Arity PlusOp::get_arity() const {
	return binary;
}

//——————————————————————————————————————————————————————————————————————— minus

double MinusOp::operation(char op, double a, double b, double) {
	if (op != '-')
		throw std::logic_error("Operation other than Minus (-) are not supported");

	return a - b;
}

IOperation::Arity MinusOp::get_arity() const {
	return binary;
}

//———————————————————————————————————————————————————————————————————————— mult

double MultOp::operation(char op, double a, double b, double) {
	if (op != '*')
		throw std::logic_error("Operation other than Mult (*) are not supported");

	return a * b;
}

IOperation::Arity MultOp::get_arity() const {
	return binary;
}

//————————————————————————————————————————————————————————————————————————— div

#ifndef EPS
#define EPS 1E-6
#endif

double DivOp::operation(char op, double a, double b, double) {
	if (op != '/')
		throw std::logic_error("Operation other than Div (/) are not supported");

	if (-EPS < b && b < EPS)
		throw std::overflow_error("Divide by zero");

	return a / b;
}

IOperation::Arity DivOp::get_arity() const {
	return binary;
}
