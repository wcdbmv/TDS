#ifndef HANDLER_H_
#define HANDLER_H_

#include <stddef.h>
#include "request.h"
#include "interval.h"

struct OA {
	Request target;
	bool is_target;
	int8_t processing;
	double triggertime;
	double timespent;
};

struct Options {
	Interval q1, q2;
	Interval a1, a2;

	size_t num;
	size_t period;

	int8_t type;
};

void start(const Options& options);
void measure(const Options& options);

Request unload(OA& oa);
void load(OA& oa, const Request& request, double t);

#endif // HANDLER_H_
