#include "ui.h"

#include <cstdio>
#include <stdlib.h>
#include "colors.h"

int main() {
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	cls();

	while (menu())
		;

	return EXIT_SUCCESS;
}
