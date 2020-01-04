#include "ui.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include "stack_array.h"
#include "stack_linked_list.h"
#include "palindrom.h"
#include "colors.h"

//—————————————————————————————————————————————————————————————————————— static

static IStack<char>* stack;
static enum { ARRAY, LINKED_LIST } mode;
static std::size_t const LIMIT_OF_ARRAY_STACK_LIMIT = 4086LLU;
static std::vector<std::size_t> freed;

static std::string const& menu_info = \
	"Menu:\n"
	"1. Create stack based on array\n"
	"2. Create stack based on linked list\n"
	"3. Print statistics\n"
	"0. Exit\n"
;

static std::string const& stack_menu_info = \
	"Stack menu:\n"
	"1. Push\n"
	"2. Pop\n"
	"3. Is palindrom?\n"
	"0. Exit\n"
;

//—————————————————————————————————————————————————————————————————————— common

int clear_input() {
	char c;
	int symbols = 0;
	while ((c = std::cin.get()) != '\n' && c != EOF)
		++symbols;
	return symbols;
}

void press_enter() {
	print_flashing("\n<press Enter to continue>");
	if (getchar() != '\n')
		clear_input();
	cls();
}

void print_exit() {
	print_bold("I hope I was helpful. Thank you for using.");
	press_enter();
	cls();
}

void print_error(std::string const& msg) {
	print_red(msg);
	press_enter();
}

void print_good(std::string const& msg) {
	print_green(msg);
	press_enter();
}

void display(std::string const& msg) {
	cls();
	std::cout << msg;
}

char input_char(std::string const& prompt) {
	std::cout << "\nInput " << prompt << "\n>>> ";
	char c = std::cin.get();
	if (c == '\n' || clear_input())
		return -1;
	return c;
}

int input_unsigned(std::string const& prompt) {
	int d = -1;
	std::cout << "\nInput " << prompt << "\n>>> ";
	int rc1 = scanf("%d", &d);
	int rc2 = clear_input();
	if (rc1 != 1 || rc2)
		return -1;
	return d;
}

//———————————————————————————————————————————————————————————————————— stack ui

void stack_print() {
	std::cout << "Stack: ";
	stack->print();
	std::cout << std::endl;
	if (mode == LINKED_LIST) {
		if (freed.size()) {
			std::cout << std::endl;
			std::cout << "Free: ";
			for(std::size_t i = 0; i < freed.size(); ++i)
				std::cout << freed[i] << ' ';
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

void stack_push()
{
	if (stack->full()) {
		print_error("Stack is full");
		return;
	}

	char c = input_char("new char");
	if (c < 0) {
		print_error("Invalid input");
		return;
	}

	stack->push(c);

	if (mode == LINKED_LIST) {
		std::size_t adrs = stack->vtop();
		freed.erase(std::remove(freed.begin(), freed.end(), adrs), freed.end());
	}

	print_good("Char pushed successful");
}

void stack_pop()
{
	if (stack->empty()) {
		print_error("Stack is empty");
		return;
	}

	if (mode == LINKED_LIST)
		freed.push_back(stack->vtop());

	stack->pop();

	print_good("Char popped successful");
}

void stack_is_palindrom()
{
	if (stack->empty())
		print_error("Stack is empty");
	else if (palindrom(stack, mode))
		print_good("String is palindrom");
	else
		print_error("String isn't palindrom");
}


//—————————————————————————————————————————————————————————————————————————— ui

std::size_t tick(void)
{
	std::size_t d;
	__asm__ __volatile__ ("rdtsc" : "=A" (d) );
	return d;
}

void print_ticks(std::size_t ticks, const char* prompt) {
	double ms = (double) ticks / 5E8;
	printf("**** [%s] sec: %.5lf ****\n", prompt, ms);
}

void print_statistics() {
	StackArray<double> sa;
	StackLinkedList<double> sl;

#define for1000 for (int i = 0; i != 1000; ++i)

	std::size_t _a = tick();
	for1000 sa.push(i);
	std::size_t _b = tick();
	for1000 sl.push(i);
	std::size_t _c = tick();
	for1000 sa.pop();
	std::size_t _d = tick();
	for1000 sl.pop();
	std::size_t _e = tick();
	printf("\n%g(time)\n", 0.0);
	std::size_t _f = tick();

	std::cout << "Add 1000:\n";
	print_ticks(_b - _a, "array");
	print_ticks(_c - _b, "llist");
	std::cout << "Pop 1000:\n";
	print_ticks(_d - _c, "array");
	print_ticks(_e - _d, "llist");
	std::cout << "Print 1000:\n";
	print_ticks(1000 * (_f - _e) + 2 * (_d - _c + _b - _a), "array");
	print_ticks(1000 * (_f - _e) + 2 * (_e - _d + _c - _b), "llist");

	press_enter();
}

bool create_stack_based_on_array() {
	int limit = input_unsigned("limit of stack");
	if (limit <= 0 || (std::size_t) limit > LIMIT_OF_ARRAY_STACK_LIMIT) {
		print_error("Invalid value");
		return false;
	}
	stack = new StackArray<char>(limit);
	mode = ARRAY;
	print_good("Stack created successful");
	return true;
}

bool create_stack_based_on_linked_list() {
	stack = new StackLinkedList<char>();
	mode = LINKED_LIST;
	print_good("Stack created successful");
	return true;
}

//———————————————————————————————————————————————————————————————————————— menu

bool stack_menu() {
	stack_print();
	std::cout << stack_menu_info << std::endl;
	int action = input_char("action") - '0';
	switch (action) {
	case 1:
		stack_push();
		return true;
	case 2:
		stack_pop();
		return true;
	case 3:
		stack_is_palindrom();
		return true;
	case 0:
		delete stack;
		print_exit();
		return false;
	default:
		print_error("No such action");
		return true;
	}
}

bool menu() {
	std::cout << menu_info << std::endl;
	int action = input_char("action") - '0';
	switch (action) {
	case 1:
		if (create_stack_based_on_array())
			while (stack_menu())
				;
		return true;
	case 2:
		if (create_stack_based_on_linked_list())
			while (stack_menu())
				;
		return true;
	case 3:
		print_statistics();
		return true;
	case 0:
		print_exit();
		return false;
	default:
		print_error("No such action");
		return true;
	}
}
