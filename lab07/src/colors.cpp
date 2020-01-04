#include "colors.h"

#include <iostream>

void print_bold(std::string const& msg) {
	std::cout << DEFAULT BOLD << msg << DEFAULT << std::endl;
}

void print_flashing(std::string const& msg) {
	std::cout << DEFAULT FLASHING << msg << DEFAULT << std::endl;
}

void print_red(std::string const& msg) {
	std::cout << DEFAULT RED_FG << msg << DEFAULT << std::endl;
}

void print_green(std::string const& msg) {
	std::cout << DEFAULT GREEN_FG << msg << DEFAULT << std::endl;
}
