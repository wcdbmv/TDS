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

	return EXIT_SUCCESS;
}


/*
#include "sparse_matrix.h"
#include "info.h"

int main() {
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	sm_t *sm = create_sm(16, 8, 8);
	fwrite_sm(stdout, sm, 1);
	append(sm, 1, 1, 1);
	fwrite_sm(stdout, sm, 1);
	append(sm, -1, 2, 4);
	fwrite_sm(stdout, sm, 1);
	append(sm, 0, 2, 4);
	fwrite_sm(stdout, sm, 1);
	delete_sm(&sm);

	printf("\n\n\n\n\n");

	FILE *sm_1txt = fopen("sm/sm_1.txt", "r");
	if (sm_1txt) {
		sm_t *sm = NULL;
		int rc = fget_sm(sm_1txt, &sm);
		if (rc == EXIT_SUCCESS) {
			fwrite_sm(stdout, sm, 1);
			delete_sm(&sm);
		}
		else {
			my_perror(rc);
		}
		fclose(sm_1txt);
	}
	else {
		perror("sm/sm_1.txt");
	}

	return EXIT_SUCCESS;
}
*/
