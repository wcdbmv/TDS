#include "info.h"

void help(void) {
	printf(
"Задача: ввести список стран, содержащий название страны, количество жителей,\n"
"столицу, материк, основной вид туризма (экскурсионный — количество объектов,\n"
"основной вид (природа, история, искусство); пляжный – основной сезон,\n"
"температура воздуха и воды, время полёта до страны; спортивный – вид спорта\n"
"(горные лыжи, серфинг, восхождения), минимальная стоимость отдыха). Вывести\n"
"список стран на выбранном материке, где можно заняться указанным видом отдыха.\n\n");
}

void my_perror(int errcode) {
	switch (errcode) {
		case SUCCESS:
			break;
		case FAILED_ALLOC_ERROR:
			perror("alloc:");
			break;
		case EMPTY_INPUT_FILE_ERROR:
			fprintf(stderr, "Input file is empty.\n");
			break;
		case UNEXPECTED_EOF_ERROR:
			fprintf(stderr, "Unexpected end of input file.\n");
			break;
		case INVALID_COUNTRY_NAME_ERROR:
			fprintf(stderr, "Invalid country name.\n");
			break;
		case INVALID_POPULATION_ERROR:
			fprintf(stderr, "Invalid population (expect 0..1500000).\n");
			break;
		case INVALID_CAPITAL_ERROR:
			fprintf(stderr, "Invalid capital.\n");
			break;
		case INVALID_CONTINENT_ERROR:
			fprintf(stderr, "Invalid continent (expect %s|%s|%s|%s|%s|%s).\n", AFRICA, EURASIA, NORTH_AMERICA, SOUTH_AMERICA, ANTARCTICA, AUSTRALIA);
			break;
		case INVALID_TOURISM_ERROR:
			fprintf(stderr, "Invalid tourism (expect %s|%s|%s).\n", EXCURSION, BEACH, SPORTS);
			break;
		case INVALID_TOURISM_DATA_ERROR:
			fprintf(stderr, "Invalid tourism data.\n");
			break;
		case INVALID_OBJECTS_ERROR:
			fprintf(stderr, "Invalid objects.\n");
			break;
		case INVALID_EXCURSION_BASIC_ERROR:
			fprintf(stderr, "Invalid basic excursion (expect %s|%s|%s).\n", NATURE, HISTORY, ART);
			break;
		case INVALID_SEASON_ERROR:
			fprintf(stderr, "Invalid season (expect %s|%s|%s|%s).\n", WINTER, SPRING, SUMMER, FALL);
			break;
		case INVALID_TEMP_ERROR:
			fprintf(stderr, "Invalid temp.\n");
			break;
		case INVALID_FLIGHT_TIME_ERROR:
			fprintf(stderr, "Invalid flight time.\n");
			break;
		case INVALID_SPORTS_BASIC_ERROR:
			fprintf(stderr, "Invalid basic sports (expect %s|%s|%s).\n", ALPINE_SKIING, SURFING, CLIMBING);
			break;
		case INVALID_MIN_COST_ERROR:
			fprintf(stderr, "Invalid min cost.\n");
			break;
		case INVALID_INPUT_TEXT_FILE_ERROR:
			fprintf(stderr, "Invalid input text file.\n");
			break;
	}
}
