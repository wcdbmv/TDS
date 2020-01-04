#include "country.h"

bool alphabetic(const char *s) {
	assert(*s);
	while (*s) {
		if (!isalpha(*s++)) {
			return false;
		}
	}
	return true;
}

//————————————————————————————————————————————————————————————————————————— set

int set_name(const char *s, country_t *country) {
	assert(strlen(s));
	if (!alphabetic(s)) {
		return INVALID_COUNTRY_NAME_ERROR;
	}
	strcpy(country->name, s);
	return SUCCESS;
}

int set_capital(const char *s, country_t *country) {
	assert(strlen(s));
	if (!alphabetic(s)) {
		return INVALID_CAPITAL_ERROR;
	}
	strcpy(country->capital, s);
	return SUCCESS;
}

int set_continent(const char *s, country_t *country) {
	continent_t continent;
	if (!strcmp(s, AFRICA)) {
		continent = africa;
	}
	else if (!strcmp(s, EURASIA)) {
		continent = eurasia;
	}
	else if (!strcmp(s, NORTH_AMERICA)) {
		continent = north_america;
	}
	else if (!strcmp(s, SOUTH_AMERICA)) {
		continent = south_america;
	}
	else if (!strcmp(s, ANTARCTICA)) {
		continent = antarctica;
	}
	else if (!strcmp(s, AUSTRALIA)) {
		continent = australia;
	}
	else {
		return INVALID_CONTINENT_ERROR;
	}
	country->continent = continent;
	return SUCCESS;
}

int set_tourism(const char *s, country_t *country) {
	tourism_t tourism;
	if (!strcmp(s, EXCURSION)) {
		tourism = excursion;
	}
	else if (!strcmp(s, BEACH)) {
		tourism = beach;
	}
	else if (!strcmp(s, SPORTS)) {
		tourism = sports;
	}
	else {
		return INVALID_TOURISM_ERROR;
	}
	country->tourism = tourism;
	return SUCCESS;
}

int set_excursion_basic(const char *s, country_t *country) {
	excursion_basic_t basic;
	if (!strcmp(s, NATURE)) {
		basic = nature;
	}
	else if (!strcmp(s, HISTORY)) {
		basic = history;
	}
	else if (!strcmp(s, ART)) {
		basic = art;
	}
	else {
		return INVALID_EXCURSION_BASIC_ERROR;
	}
	country->tourism_data.excursion.basic = basic;
	return SUCCESS;
}

int set_season(const char *s, country_t *country) {
	season_t season;
	if (!strcmp(s, WINTER)) {
		season = winter;
	}
	else if (!strcmp(s, SPRING)) {
		season = spring;
	}
	else if (!strcmp(s, SUMMER)) {
		season = summer;
	}
	else if (!strcmp(s, FALL)) {
		season = fall;
	}
	else {
		return INVALID_SEASON_ERROR;
	}
	country->tourism_data.beach.season = season;
	return SUCCESS;
}

int set_sports_basic(const char *s, country_t *country) {
	sports_basic_t basic;
	if (!strcmp(s, ALPINE_SKIING)) {
		basic = alpine_skiing;
	}
	else if (!strcmp(s, SURFING)) {
		basic = surfing;
	}
	else if (!strcmp(s, CLIMBING)) {
		basic = climbing;
	}
	else {
		return INVALID_SPORTS_BASIC_ERROR;
	}
	country->tourism_data.sports.basic = basic;
	return SUCCESS;
}

//————————————————————————————————————————————————————————————————————————— str

void str_continent(char *s, const continent_t continent) {
	switch (continent) {
		case africa:
			strcpy(s, AFRICA);
			break;
		case eurasia:
			strcpy(s, EURASIA);
			break;
		case north_america:
			strcpy(s, NORTH_AMERICA);
			break;
		case south_america:
			strcpy(s, SOUTH_AMERICA);
			break;
		case antarctica:
			strcpy(s, ANTARCTICA);
			break;
		case australia:
			strcpy(s, AUSTRALIA);
			break;
		default:
			strcpy(s, "UNDEFINED");
			break;
	}
}

void str_tourism(char *s, const tourism_t tourism) {
	switch (tourism) {
		case excursion:
			strcpy(s, EXCURSION);
			break;
		case beach:
			strcpy(s, BEACH);
			break;
		case sports:
			strcpy(s, SPORTS);
			break;
		default:
			strcpy(s, "UNDEFINED");
			break;
	}
}

void str_excursion_basic(char *s, const excursion_basic_t basic) {
	switch (basic) {
		case nature:
			strcpy(s, NATURE);
			break;
		case history:
			strcpy(s, HISTORY);
			break;
		case art:
			strcpy(s, ART);
			break;
		default:
			strcpy(s, "UNDEFINED");
			break;
	}
}

void str_season(char *s, const season_t season) {
	switch (season) {
		case winter:
			strcpy(s, WINTER);
			break;
		case spring:
			strcpy(s, SPRING);
			break;
		case summer:
			strcpy(s, SUMMER);
			break;
		case fall:
			strcpy(s, FALL);
			break;
		default:
			strcpy(s, "UNDEFINED");
			break;
	}
}

void str_sports_basic(char *s, const sports_basic_t basic) {
	switch (basic) {
		case alpine_skiing:
			strcpy(s, ALPINE_SKIING);
			break;
		case surfing:
			strcpy(s, SURFING);
			break;
		case climbing:
			strcpy(s, CLIMBING);
			break;
		default:
			strcpy(s, "UNDEFINED");
			break;
	}
}

//———————————————————————————————————————————————————————————————————————— fget

int fget_name(FILE *file, country_t *country) {
	int rc;
	char s[STR_LIMIT];
	if ((rc = fscanf(file, "%s", s)) != 1) {
		return rc == EOF ? UNEXPECTED_EOF_ERROR : INVALID_COUNTRY_NAME_ERROR;
	}
	return set_name(s, country);
}

int fget_population(FILE *file, country_t *country) {
	int rc;
	uint64_t u;
	if ((rc = fscanf(file, "%lu", &u)) != 1) {
		return rc == EOF ? UNEXPECTED_EOF_ERROR : INVALID_POPULATION_ERROR;
	}
	if (u > 1500000) {
		return INVALID_POPULATION_ERROR;
	}
	country->population = u;
	return SUCCESS;
}

int fget_capital(FILE *file, country_t *country) {
	int rc;
	char s[STR_LIMIT];
	if ((rc = fscanf(file, "%s", s)) != 1) {
		return rc == EOF ? UNEXPECTED_EOF_ERROR : INVALID_CAPITAL_ERROR;
	}
	return set_capital(s, country);
}

int fget_continent(FILE *file, country_t *country) {
	int rc;
	char s[STR_LIMIT];
	if ((rc = fscanf(file, "%s", s)) != 1) {
		return rc == EOF ? UNEXPECTED_EOF_ERROR : INVALID_CONTINENT_ERROR;
	}
	return set_continent(s, country);
}

int fget_tourism(FILE *file, country_t *country) {
	int rc;
	char s[STR_LIMIT];
	if ((rc = fscanf(file, "%s", s)) != 1) {
		return rc == EOF ? UNEXPECTED_EOF_ERROR : INVALID_TOURISM_ERROR;
	}
	return set_tourism(s, country);
}

int fget_excursion(FILE *file, country_t *country) {
	int rc;
	uint64_t u;
	if ((rc = fscanf(file, "%lu", &u)) != 1) {
		return rc == EOF ? UNEXPECTED_EOF_ERROR : INVALID_OBJECTS_ERROR;
	}
	country->tourism_data.excursion.objects = u;
	char s[STR_LIMIT];
	if ((rc = fscanf(file, "%s", s)) != 1) {
		return rc == EOF ? UNEXPECTED_EOF_ERROR : INVALID_EXCURSION_BASIC_ERROR;
	}
	return set_excursion_basic(s, country);
}

int fget_beach(FILE *file, country_t *country) {
	int rc;
	char s[STR_LIMIT];
	if ((rc = fscanf(file, "%s", s)) != 1) {
		return rc == EOF ? UNEXPECTED_EOF_ERROR : INVALID_SEASON_ERROR;
	}
	if ((rc = set_season(s, country)) != SUCCESS) {
		return rc; // INVALID_SEASON_ERROR
	}
	int8_t d;
	if ((rc = fscanf(file, "%hhd", &d)) != 1) {
		return feof(file) ? UNEXPECTED_EOF_ERROR : INVALID_TEMP_ERROR;
	}
	// need check temps
	country->tourism_data.beach.air_temp = d;
	if ((rc = fscanf(file, "%hhd", &d)) != 1) {
		return feof(file) ? UNEXPECTED_EOF_ERROR : INVALID_TEMP_ERROR;
	}
	// need check temps
	country->tourism_data.beach.water_temp = d;
	uint16_t u;
	if ((rc = fscanf(file, "%hu", &u)) != 1) {
		return rc == EOF ? UNEXPECTED_EOF_ERROR : INVALID_FLIGHT_TIME_ERROR;
	}
	country->tourism_data.beach.flight_time = u;
	return SUCCESS;
}

int fget_sports(FILE *file, country_t *country) {
	int rc;
	char s[STR_LIMIT];
	if ((rc = fscanf(file, "%s", s)) != 1) {
		return rc == EOF ? UNEXPECTED_EOF_ERROR : INVALID_SPORTS_BASIC_ERROR;
	}
	if ((rc = set_sports_basic(s, country)) != SUCCESS) {
		return rc; // INVALID_SPORTS_BASIC_ERROR
	}
	uint32_t min_cost;
	if ((rc = fscanf(file, "%u", &min_cost)) != 1) {
		return rc == EOF ? UNEXPECTED_EOF_ERROR : INVALID_MIN_COST_ERROR;
	}
	country->tourism_data.sports.min_cost = min_cost;
	return SUCCESS;
}
