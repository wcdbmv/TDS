#include "ui.h"

#include <cstdio>

int main() {
	setbuf(stdout, nullptr);

	while (true)
		if (!menu())
			break;
}
