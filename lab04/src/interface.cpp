#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "stack_array.h"
#include "stack_linked_list.h"
#include "calculator.h"

static const std::string menu_prompt =
	"1. Array\n"
	"2. Linked list\n"
	"3. Statistics\n"
	"0. Exit\n"
;

static const std::string stack_menu_prompt =
	"1. Push\n"
	"2. Pop\n"
	"3. Calculate\n"
	"0. Exit\n"
;

static IStack<double> *s;
static int mode;

static std::vector<llu> freed;

void cls() {
	std::cout << "\033[1;1H\033[J";
}

void display(const std::string& prompt, const std::string& title) {
	std::cout << "---- " << title << ' ' << std::string(80 - title.size() - 6, '-') << std::endl;
	std::cout << prompt;
}

typedef long long unsigned llu;

llu tick(void)
{
	llu d;
	__asm__ __volatile__ ("rdtsc" : "=A" (d) );
	return d;
}

void print_ticks(llu ticks, const char *prompt) {
	double ms = (double) ticks / 5E8;
	printf("**** [%s] sec: %.5lf ****\n", prompt, ms);
}

void statistics(void) {
	StackArray<double> sa;
	StackLinkedList<double> sl;

#define for1000 for (int i = 0; i != 1000; ++i)

	llu _a = tick();
	for1000 sa.push(i);
	llu _b = tick();
	for1000	sl.push(i);
	llu _c = tick();
	for1000 sa.pop();
	llu _d = tick();
	for1000 sl.pop();
	llu _e = tick();
	printf("%g", 123.456);
	llu _f = tick();

	cls();
	std::cout << "Add 1000:\n";
	print_ticks(_b - _a, "array");
	print_ticks(_c - _b, "llist");
	std::cout << "\nPop 1000:\n";
	print_ticks(_d - _c, "array");
	print_ticks(_e - _d, "llist");
	std::cout << "\nPrint 1000:\n";
	print_ticks(1000 * (_f - _e) + 2 * (_d - _c + _b - _a), "array");
	print_ticks(1000 * (_f - _e) + 2 * (_e - _d + _c - _b), "llist");
	getchar();
	getchar();
}


#define ERR -71234123

double dget(const std::string& prompt) {
	std::cout << prompt;
	std::cin.clear();
	double d = ERR;
	std::cin >> d;
	std::cin.clear();
	return d;
}

void wronginput() {
	std::cout << "Wrong input. (tap enter)\n";
	getchar();
	getchar();
}

void vprint(const std::vector<llu>& v) {
	for(unsigned i = 0; i < v.size(); ++i)
		std::cout << v[i] << ' ';
}

#define exiting \
std::cout << "Exiting.. (Tap Enter)\n"; \
getchar(); \
cls(); \
return false;

#define nl() std::cout << "\n"

static Calculator *c;
static std::string asdf(' ', 100);
static double dd;

bool stack_menu() {
	cls();
	std::cout << "Stack: ";
	s->print();
	nl();
	if (mode) {
		if (freed.size()) {
			std::cout << "Free: ";
			vprint(freed);
			nl();
		}
	}
	nl();
	display(stack_menu_prompt, "Stack menu:");
	int command = dget("Input command: ");
	double d;
	switch (command) {
		case 1:
			if (!mode && s->is_full())
			{
				std::cout << "Stack is full. (tap enter)\n";
				getchar();
				getchar();
				break;
			}
			d = dget("Input new item: ");
			if (d == ERR) {
				wronginput();
				break;
			}
			s->push(d);
			if (mode) {
				llu l = s->vtop();
				freed.erase(std::remove(freed.begin(), freed.end(), l), freed.end());
			}
			break;
		case 2:
			if (s->is_empty()) {
				std::cout << "Stack is empty\n";
				getchar();
				getchar();
			}
			else {
				if (mode) {
					freed.push_back(s->vtop());
				}
				s->pop();
			}
			break;
		case 3:
			c = new Calculator(mode ? "linked_list" : "array");
			dd = 0;
			std::cin.clear();
			std::cin.clear();
			std::cout << "\nNote: type exit to exit\n<tap enter to start>\n";
			getchar();
			getchar();
			std::cin.clear();
			std::cin.clear();
			while (std::cout << "\033[1;1H\033[J>>> ", std::getline(std::cin, asdf) && asdf != "exit") {
				if (!asdf.size())
				{
					std::cout << "Empty input\n";
					getchar();
					continue;
				}
				dd = c->calculate(asdf);
				if (dd == DIVISION_BY_ZERO)
					std::cout << "[Division by zero]\n";
				else if (dd == DOUBLE_ERR)
					std::cout << "[Error while pars arg]\n";
				else if (dd != INFIX_ERR)
					std::cout << "\033[1;1H\033[JResult: " << dd;
				puts("\n\n<press enter>");
				getchar();
			}
			delete c;
			break;
		case 0:
			exiting
		default:
			wronginput();
			break;
	}
	return true;
}

bool menu() {
	cls();
	display(menu_prompt, "Menu:");
	int command;
	command = dget("Input command: ");
	switch (command) {
		case 1:
			s = new StackArray<double>(6);
			mode = 0;
			while (stack_menu())
				;
			delete s;
			break;
		case 2:
			s = new StackLinkedList<double>;
			mode = 1;
			while (stack_menu())
				;
			delete s;
			freed.clear();
			break;
		case 3:
			statistics();
			break;
		case 0:
			exiting
		default:
			wronginput();
			break;
	}
	return true;
}

int main()
{
	while (menu())
		;
}
