#pragma once

#include <cstdint>

struct Request {
public:
	double time;
	int8_t type;
public:
	Request(const int8_t type = 0);
};
