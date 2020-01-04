#include "handler.h"

#include <cassert>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <cstdint>
#include "queue_array.h"
#include "queue_linked_list.h"

#define EPS 1E-3
#define EXP (uint8_t) 1000

bool double_equal(const double a, const double b) {
	return std::abs(a - b) < EPS / 100;
}

double rand_double(double a, double b, uint8_t exp) {
	return a + (double) ((rand() % (unsigned) ((b - a) * exp))) / exp;
}


Request unload(OA& oa) {
	oa.processing = 0;
	oa.timespent = oa.triggertime = -1;
	oa.is_target = false;
	return oa.target;
}

void load(OA& oa, const Request& request, double t) {
	oa.processing = request.type;
	oa.target = request;
	oa.timespent = 0.0;
	oa.triggertime = t;
}



void start(const Options& options) {
#define PLAN_Q1 (rand_double(options.q1.from, options.q1.to, EXP))
#define PLAN_Q2 (rand_double(options.q2.from, options.q2.to, EXP))
#define PLAN_A1 (rand_double(options.a1.from, options.a1.to, EXP))
#define PLAN_A2 (rand_double(options.a2.from, options.a2.to, EXP))

	IQueue<Request>* q1;
	IQueue<Request>* q2;

	if (options.type == 1) {
		q1 = new QueueArray<Request>();
		q2 = new QueueArray<Request>();
	}
	else if (options.type == 2) {
		q1 = new QueueLinkedList<Request>();
		q2 = new QueueLinkedList<Request>();
	}

	OA oa;
	oa.processing = 0;
	oa.triggertime = -1;
	oa.timespent = -1;

	double timepass = 0.0;
	double timeidle = 0.0;
	double timewaste = 0.0;
	double timework = 0.0;

	double q1_next = PLAN_Q1;
	double q2_next = PLAN_Q2;

	size_t loaded1 = 0;
	size_t loaded2 = 0;
	size_t processed1 = 0;
	size_t processed2 = 0;
	size_t wasted = 0;

	size_t maxlen1 = 0;
	size_t maxlen2 = 0;

	bool action = false;

	long long unsigned cycles = 0;

	double buf = 0.0;

	fprintf(stdout,
		"Options:\n"
		"%.3lf .. %.3lf for 1st type updating\n"
		"%.3lf .. %.3lf for 2nd type updating\n"
		"%.3lf .. %.3lf for 1st type processing\n"
		"%.3lf .. %.3lf for 2nd type processing\n"
		"Process till %lu 1st type, dumping every %lu\n\n",
		options.q1.from, options.q1.to,
		options.q2.from, options.q2.to,
		options.a1.from, options.a1.to,
		options.a2.from, options.a2.to,
		options.num, options.period
	);

	fprintf(stderr, "Start\n\n");

	clock_t _a = clock();

	while (processed1 < options.num) {
		++cycles;

		if (double_equal(timepass, q1_next)) {
			if (options.type == 1 && q1->is_full()) {
				fprintf(stderr, "[X] Error: (_%.3lf_) Couldn't add element to q1, it's full!\n", timepass);
			}
			else {
				q1->push(Request(1));

				fprintf(stderr, "(_%.3lf_) Adding element to q1, next one: on %.3lf\n"
				              , timepass, q1_next);

				maxlen1 = std::max(q1->size(), maxlen1);
				++loaded1;
			}
			q1_next += PLAN_Q1;
		}

		if (double_equal(timepass, q2_next)) {
			if (options.type == 1 && q2->is_full()) {
				fprintf(stderr, "[X] Error: (_%.3lf_) Couldn't add element to q2, it's full!\n", timepass);
			}
			else {
				q2->push(Request(2));

				fprintf(stderr, "(_%.3lf_) Adding element to q2, next one: on %.3lf\n"
				, timepass, q2_next);

				maxlen2 = std::max(q2->size(), maxlen2);
				++loaded2;
			}
			q2_next += PLAN_Q2;
		}

		if (double_equal(oa.triggertime, timepass)) {
			fprintf(stderr, "(_%.3lf_) finished request from q%d\n"
			              , timepass, oa.processing);

			if (oa.processing == 1) {
				++processed1;
				timework += oa.timespent;
			}
			else if (oa.processing == 2) {
				++processed2;
			}

			unload(oa);
		}

		if (oa.processing == 2 && !q1->is_empty()) {
			fprintf(stderr, "Switching! Time was spent: %f\n", oa.timespent);

			timewaste += oa.timespent;
			++wasted;

			Request t = unload(oa);
			if (q2->is_full())
				fprintf(stderr, "[X] Error: (_%.3lf_) Couldn't add element to q2, it's full!\n", timepass);
			else
				q2->push(t);
		}

		if (!oa.processing) {
			if (!q1->is_empty()) {
				load(oa, q1->pop(), timepass + PLAN_A1);
			}
			else if (!q2->is_empty()) {
				load(oa, q2->pop(), timepass + PLAN_A2);
			}
			else {
				buf = std::min(q1_next, q2_next) - timepass;

				fprintf(stderr, "(_%.3lf_) Automation is idling: skipping %.3lf, forward to %.3lf\n"
				              , timepass, buf, timepass + buf);

				timeidle += buf;
			}

			if (!q1->is_empty() || !q2->is_empty()) {
				fprintf(stderr, "(_%.3lf_) empty, loaded %d type, till %.3lf (for %.3lf)\n"
				              , timepass
				              , oa.processing
				              , oa.triggertime
				              , oa.triggertime - timepass);
			}

			if (double_equal(oa.triggertime, timepass))
				fprintf(stderr, "Immediate unload!\n");
		}
		else {
			buf = std::min(std::min(q1_next, q2_next), oa.triggertime) - timepass;
		}

		if (!(processed1 % options.period)) {
			if (!action) {
				fprintf(stdout, "q1 length is %lu and q2 length is %lu\n"
				              , q1->size(), q2->size());

				// fprintf(stderr, "\tAdresses: Q1 = 0x%X;   Q2 = 0x%X\n",, Q1, Q2);
				fprintf(stdout, "\tAverage waiting of request: %.3lf in q1;   %.3lf in q2\n"
				              , q1->avgtime(), q1->avgtime());

				fprintf(stdout, "\tNext: q1 on %.3lf;   q2 on %.3lf\n"
				              , q1_next, q2_next);

				fprintf(stdout, "\tAutomaton processing %d for %.3lf, till %.3lf\n"
				              , oa.processing, oa.timespent, oa.triggertime);

				fprintf(stdout, "\tProcessed %lu requests of q1 and %lu of q2\n"
				              , processed1, processed2);

				if (options.period != 1)
					action = true;
			}
		}
		else
			action = false;

		if (processed1 == options.num)
			break;

		timepass += buf;
		if (oa.processing)
			oa.timespent += buf;

		q1->updqueue(buf);
		q1->updqueue(buf);

		fprintf(stderr, "\n");
	}

	clock_t _b = clock();

	fprintf(stdout, "\n\n * * * Process finished\n");
	fprintf(stdout, "\tPERFORMANCE: time passed %lf sec, maxlen1: %lu, maxlen2: %lu\n"
	              , (double) (_b - _a) / CLOCKS_PER_SEC, maxlen1, maxlen2);

	fprintf(stdout, "\tTOTAL. Time passed: %.3lf , idling for: %.3lf\n"
	              , timepass, timeidle);
	fprintf(stdout, "\tREMAIN: %lu in Q1 and %lu in Q2 when process stopped.\n"
	              , q1->size(), q2->size());
	fprintf(stdout, "\t1st TYPE. Were loaded: %lu, processed: %lu. Automaton was working for %.3lf\n"
	              , loaded1, processed1, timework);
	fprintf(stdout, "\t2nd TYPE. Were loaded: %lu, of them wasted: %lu for %.3lf; processed: %lu\n"
	              , loaded2, wasted, timewaste, processed2);

	double d1 = (options.q1.from + options.q1.to) / 2;
	double d2 = (options.a1.from + options.a1.to) / 2;

	double d = std::max(d1, d2);

	double expec = d * options.num;

	double proc = std::abs(expec - timepass) / expec;

	fprintf(stdout, "\texpected: %lu * %g = %g\n", options.num, d, expec);
	fprintf(stdout, "\td: |%g - %g| / %g = %.2lf %%\n", expec, timepass, expec, proc);

	delete q1;
	delete q2;
}
