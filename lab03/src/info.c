#include "info.h"

void help(void) {
	printf("hm\n");
}

void my_perror(int errcode) {
	switch (errcode) {
		case FAILED_ALLOC_ERROR:
			perror("alloc");
			break;
		case EMPTY_FILE_ERROR:
			fprintf(stderr, "Input file is empty.\n");
			break;
		case READ_FILE_ERROR:
			perror("read file");
			break;
		case UNEXPECTED_EOF_EROR:
			fprintf(stderr, "Reach end of input file (unexpected).\n");
			break;
		case INVALID_INPUT_ERROR:
			fprintf(stderr, "Invalid input.\n");
			break;
		case INVALID_ELEM_ERROR:
			fprintf(stderr, "Got invalid element.\n");
			break;
		case ELEM_EXISTS_ERROR:
			fprintf(stderr, "Element already exists.\n");
			break;
		case SIZE_OVERFLOW_ERROR:
			fprintf(stderr, "Size overflow (reached %d)\n", SIZE_LIMIT);
			break;
		case CHAIN_OVERFLOW_ERROR:
			fprintf(stderr, "I have no idea why this happend.\n");
			break;
		case WRONG_CHECK_ERROR:
			fprintf(stderr, "Error while parsing input.\n");
			break;
		case INPUT_ZERO_ERROR:
			fprintf(stderr, "Number must be nonzero.\n");
			break;
		case LT_ERROR:
			fprintf(stderr, "Invalid input (got impossible value).\n");
			break;
		case NZNLT_ERROR:
			fprintf(stderr, "Invalid input (got zero or impossible value).\n");
			break;
		case CANT_OPEN_FILE_ERROR:
			perror("open file");
			break;
		case INVALID_SIZES_ERROR:
			fprintf(stderr, "Can't multiply matrices with different sizes.\n");
			break;
		case WRONG_USAGE_ERROR:
			fprintf(stderr, "Second matrix must be a column.\n");
			break;
		case MATRICES_SIZES_ERROR:
			fprintf(stderr, "Error while compare sizes.\n");
			break;
		case INCOMPATIBLE_SLAE_ERROR:
			fprintf(stderr, "There are no solutions.\n");
			break;
	}
}
