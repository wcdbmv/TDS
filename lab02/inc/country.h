#ifndef __COUNTRY_H__
#define __COUNTRY_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "errcodes.h"

#define STR_LIMIT 32

//——————————————————————————————————————————————————————————— in tourism_data_t

#define NATURE "Nature"
#define HISTORY "History"
#define ART "Art"

typedef enum {
	nature, history, art
} excursion_basic_t;

#define WINTER "Winter"
#define SPRING "Spring"
#define SUMMER "Summer"
#define FALL "Fall"

typedef enum {
	winter, spring, summer, fall
} season_t;

#define ALPINE_SKIING "Alpine_skiing"
#define SURFING "Surfing"
#define CLIMBING "Climbing"

typedef enum {
	alpine_skiing, surfing, climbing
} sports_basic_t;

//———————————————————————————————————————————————————————————————— in tourism_t

typedef struct {
	uint64_t objects;
	excursion_basic_t basic;
} excursion_t;

typedef struct {
	season_t season;
	uint16_t flight_time;
	int8_t air_temp;
	int8_t water_temp;
} beach_t;

typedef struct {
	uint32_t min_cost;
	sports_basic_t basic;
} sports_t;

//———————————————————————————————————————————————————————————————— in country_t

#define AFRICA "Africa"
#define EURASIA "Eurasia"
#define NORTH_AMERICA "North_America"
#define SOUTH_AMERICA "South_America"
#define ANTARCTICA "Antarctica"
#define AUSTRALIA "Australia"

typedef enum {
	africa, eurasia, north_america, south_america, antarctica, australia
} continent_t;

typedef enum {
	excursion, beach, sports
} tourism_t;

#define EXCURSION "Excursion"
#define BEACH "Beach"
#define SPORTS "Sports"

typedef union {
	excursion_t excursion;
	beach_t beach;
	sports_t sports;
} tourism_data_t;

//———————————————————————————————————————————————————————————————————————— main

#pragma pack(push, 1)
typedef struct {
	char name[STR_LIMIT];
	char capital[STR_LIMIT];
	tourism_data_t tourism_data;
	uint64_t population;
	size_t id;
	continent_t continent;
	tourism_t tourism;
} country_t;
#pragma pack(pop)

//————————————————————————————————————————————————————————————————————————— sub

bool alphabetic(const char *s);
int set_name(const char *s, country_t *country);
int set_capital(const char *s, country_t *country);
int set_continent(const char *s, country_t *country);
int set_tourism(const char *s, country_t *country);
int set_excursion_basic(const char *s, country_t *country);
int set_season(const char *s, country_t *country);
int set_sports_basic(const char *s, country_t *country);
void str_continent(char *s, const continent_t continent);
void str_tourism(char *s, const tourism_t tourism);
void str_excursion_basic(char *s, const excursion_basic_t basic);
void str_season(char *s, const season_t season);
void str_sports_basic(char *s, const sports_basic_t basic);
int fget_name(FILE *file, country_t *country);
int fget_population(FILE *file, country_t *country);
int fget_capital(FILE *file, country_t *country);
int fget_continent(FILE *file, country_t *country);
int fget_tourism(FILE *file, country_t *country);
int fget_excursion(FILE *file, country_t *country);
int fget_beach(FILE *file, country_t *country);
int fget_sports(FILE *file, country_t *country);

#endif // __COUNTRY_H__
