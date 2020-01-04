#include <string>
#include <iostream>
#include "handler.h"
#include <ctime>
#include <algorithm>

#define ERR -32432154

double dget(const std::string& prompt) {
	std::cout << "\033[1;1H\033[JInput " << prompt << ": ";
	std::cin.clear();
	double d = ERR;
	std::cin >> d;
	std::cin.clear();
	return d;
}

int main() {

	std::srand(std::time(0));

	Options options;
	double d;
	char c;

sstart:
	std::cout << "\033[1;1H\033[Jstd ? ";
	c = getchar();
	if (c == 'n') {
		while (true) {
			d = dget("T1 start");
			if (d != ERR && d >= 0.0) {
				options.q1.from = d;
				break;
			}
			std::cout << "Wrong input!\n";
		}

		while (true) {
			d = dget("T1 end");
			if (d != ERR && d >= 0.0 && d >= options.q1.from) {
				options.q1.to = d;
				break;
			}
			std::cout << "Wrong input!\n";
		}

		while (true) {
			d = dget("T2 start");
			if (d != ERR && d >= 0.0) {
				options.q2.from = d;
				break;
			}
			std::cout << "Wrong input!\n";
		}

		while (true) {
			d = dget("T2 end");
			if (d != ERR && d >= 0.0 && d >= options.q2.from) {
				options.q2.to = d;
				break;
			}
			std::cout << "Wrong input!\n";
		}

		while (true) {
			d = dget("T3 start");
			if (d != ERR && d >= 0.0) {
				options.a1.from = d;
				break;
			}
			std::cout << "Wrong input!\n";
		}

		while (true) {
			d = dget("T3 end");
			if (d != ERR && d >= 0.0 && d >= options.a1.from) {
				options.a1.to = d;
				break;
			}
			std::cout << "Wrong input!\n";
		}

		while (true) {
			d = dget("T4 start");
			if (d != ERR && d >= 0.0) {
				options.a2.from = d;
				break;
			}
			std::cout << "Wrong input!\n";
		}

		while (true) {
			d = dget("T4 end");
			if (d != ERR && d >= 0.0 && d >= options.a2.from) {
				options.a2.to = d;
				break;
			}
			std::cout << "Wrong input!\n";
		}

		while (true) {
			d = dget("number of requests 1t");
			if (d != ERR && d >= 0.0) {
				options.num = d;
				break;
			}
			std::cout << "Wrong input!\n";
		}

		while (true) {
			d = dget("period");
			if (d != ERR && d >= 0.0) {
				options.period = d;
				break;
			}
			std::cout << "Wrong input!\n";
		}

		while (true) {
			d = dget("type of queue (1 - array, 2 - list)");
			if (d == 1 || d == 2) {
				options.type = d;
				break;
			}
			std::cout << "Wrong input!\n";
		}
	}
	else if (c == 'y') {
		options.q1.from = 1.0;
		options.q1.to = 5.0;
		options.q2.from = 0.0;
		options.q2.to = 3.0;
		options.a1.from = 0.0;
		options.a1.to = 4.0;
		options.a2.from = 0.0;
		options.a2.to = 1.0;
		options.num = 1000;
		options.period = 100;
		options.type = 2;
	}
	else
		goto sstart;



	start(options);
}
