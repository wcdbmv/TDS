#include "interface.h"

int main(void) {
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	help();

	while (true) {
		if (!menu()) {
			break;
		}
	}

	return SUCCESS;
}
