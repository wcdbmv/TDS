#include "calculator.h"

int main() {
	std::string s(' ', 100);
	Calculator c("array");
	double d = 0;

	while (std::cout << "\033[1;1H\033[J>>> ", std::getline(std::cin, s) && s != "exit") {
		d = c.calculate(s);
		if (d == DIVISION_BY_ZERO)
			std::cout << "[Division by zero]\n";
		else if (d == DOUBLE_ERR)
			std::cout << "[Error while pars arg]\n";
		else if (d != INFIX_ERR)
			std::cout << "\033[1;1H\033[JResult: " << d;
		puts("\n\n<press enter>");
		getchar();
	}
}
