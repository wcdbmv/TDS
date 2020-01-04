#ifndef REQUEST_H_
#define REQUEST_H_

#include <cstdint>

struct Request {
public:
	double time;
	int8_t type;
public:
	Request(const int8_t type = 0);
};

#endif // REQUEST_H_
