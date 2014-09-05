#include "CXTIME.h"

#ifdef CXTIME_MEASUREMENTS
#ifdef MEASUREMENTS
#error "Defining MEASUREMENTS here is NOT allowed as CXTIME_MEASUREMENTS is defined in CXTIME.h!"
#endif
#define MEASUREMENTS CXTIME_MEASUREMENTS
#else
#ifndef MEASUREMENTS
#define MEASUREMENTS 50
#endif
#endif
#ifndef INITIALREPEAT
#define INITIALREPEAT 1
#endif
#ifndef ALLOWPCSTDDEV
#define ALLOWPCSTDDEV 10.0
#endif
#ifndef TOTALTIMELIMIT
#define TOTALTIMELIMIT 20.0
#endif
#ifndef XMLOUTPUTTER
#define TEXTOUTPUTTER
#endif

#ifdef __cplusplus
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
#else
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#endif

void cxtime_setup(
	struct cxtime_t *tp,
	const char *description,
	const char *prepare_code,
	const char *timed_code,
	const char *verify_code,
	const char *cleanup_code
) {
	tp->description = description;
	tp->prepare_code = prepare_code;
	tp->timed_code = timed_code;
	tp->cleanup_code = cleanup_code;
	tp->verify_code = verify_code;
	tp->overhead_usec = 0.0;
	tp->full_usec = 0.0;
#ifndef CXTIME_MEASUREMENTS
	tp->timings_usec = (double *)malloc(MEASUREMENTS * sizeof (double));
#endif
	tp->ith_timing = 0;
	tp->repeat_count = INITIALREPEAT;
	tp->time_limit = clock() / (double)CLOCKS_PER_SEC + TOTALTIMELIMIT;
	tp->clock_start = -1.0;
}

/**
 * @brief Time required for for pre/cleanup_code
*/
void cxtime_started(
	struct cxtime_t *tp
) {
	assert(tp);
	assert(tp->clock_start == -1.0);
	{
		tp->clock_start = clock()/(double)CLOCKS_PER_SEC;
	}
}

void cxtime_ended_p_p(
	struct cxtime_t *tp
) {
	assert(tp);
	assert(tp->clock_start != -1.0);
	{
		const double diff = clock()/(double)CLOCKS_PER_SEC - tp->clock_start;
		tp->overhead_usec += 1e6 * (diff / tp->repeat_count);
		tp->clock_start = -1.0;
	}
}

void cxtime_ended_all(
	struct cxtime_t *tp
) {
	assert(tp);
	assert (tp->clock_start != -1.0);
	assert (tp->ith_timing < MEASUREMENTS);
	{
		const double diff = clock()/(double)CLOCKS_PER_SEC - tp->clock_start;
		tp->full_usec += 1e6 * (diff / tp->repeat_count);
		tp->clock_start = -1.0;
		tp->timings_usec[tp->ith_timing++] = 1e6 * (diff / tp->repeat_count);
	}
}

int cxtime_repeat_inner(struct cxtime_t *tp) {
	assert(tp);
	assert(tp->timings_usec);
	{
		return (tp->ith_timing < MEASUREMENTS);
	}
}

int cxtime_repeat_outer(struct cxtime_t *tp) {
	assert(tp);
	assert(tp->timings_usec);
	assert(tp->ith_timing == MEASUREMENTS);
	{
		size_t i = MEASUREMENTS;
		tp->timeout_end = (clock()/(double)CLOCKS_PER_SEC >= tp->time_limit);
		tp->overhead_usec /= MEASUREMENTS;
		tp->full_usec /= MEASUREMENTS;
		tp->average_usec = tp->full_usec - tp->overhead_usec;
		/* all measurements taken - find extrema and variance now */
		tp->minimum_usec = tp->maximum_usec = tp->timings_usec[0];
		tp->stddev_usec = 0.0;
		while (i-- != 0) {
			const double timing = tp->timings_usec[i];
			const double delta = timing - tp->full_usec;
			tp->stddev_usec += delta*delta;
			if (tp->minimum_usec > timing) {
				tp->minimum_usec = timing;
			}
			if (tp->maximum_usec < timing) {
				tp->maximum_usec = timing;
			}
		}
		tp->minimum_usec -= tp->overhead_usec;
		tp->maximum_usec -= tp->overhead_usec;
		tp->stddev_usec = sqrt(tp->stddev_usec/MEASUREMENTS);
		/* check whether results satisfy criteria for termination */
		{
			const int timings_ok = (tp->average_usec > 0.0);
			const double percent_stddev = 100.0*tp->stddev_usec/tp->full_usec;
			if (tp->timeout_end || (timings_ok && (percent_stddev <= ALLOWPCSTDDEV))) {
#ifdef CXTIME_MEASUREMENTS
				free(tp->timings_usec);
#endif
				tp->timings_usec = (double *)0;
				return 0;
			}
		}
		/* prepare another time through the loop */
		tp->repeat_count *= (tp->full_usec
				   * tp->repeat_count
				   * MEASUREMENTS >= .5e6) ? 2 : 10;
		tp->overhead_usec = 0.0;
		tp->full_usec = 0.0;
		tp->ith_timing = 0;
		return 1;
	}
}

static void show_formatted(int indent, const char *mark, const char *stmt, int newline, int xml_esc) {
	if (*stmt == '\0')
		return;
	printf("%-*s", indent, mark ? mark : "");
	int linestart = 0;
	while (*stmt != '\0') {
		if (linestart) {
			while (*stmt == ' ' || *stmt == '\t') {
				++stmt;
			}
			if (*stmt != '}') {
				printf("\n%*s", indent, "");
			}
			linestart = 0;
		}
		switch (*stmt) {
		case ';':
			linestart = 1;
			break;
		case '{':
			linestart = 1;
			/*FALLTHROUGH*/
		case '(':
			indent += 2;
			break;
		case ')':
			indent -= 2;
			break;
		case '}':
			indent -= 2;
			printf("\n%*c", indent + 1, *stmt++);
			continue;
		case '&':
			if (!xml_esc)
				break;
			printf("&amp;");
			++stmt;
			continue;
		case '<':
			if (!xml_esc)
				break;
			printf("&lt;");
			++stmt;
			continue;
		case '>':
			if (!xml_esc)
				break;
			printf("&gt;");
			++stmt;
			continue;
		}
		printf("%c", *stmt++);
	}
	if (newline) {
		printf("\n");
	}
}

#ifdef TEXTOUTPUTTER
void cxtime_print(struct cxtime_t *tp) {
	assert(tp);
	assert(tp->timings_usec == 0);
	printf("** %s **\n", tp->description);
	show_formatted(5, 0, tp->prepare_code, 1, 0);
	show_formatted(5, " -->", tp->timed_code, 0, 0);
	printf(" <--[%lu times executed]\n", tp->repeat_count);
	show_formatted(5, 0, tp->cleanup_code, 1, 0);
	printf(" = %5.3f usec total (%5.3f usec overhead was subtracted)\n",
		tp->average_usec,
		tp->overhead_usec);
	if (tp->overhead_usec > tp->full_usec/5.0)
		printf(" ! WARNING: substantial overhead\n");
	printf("   extrema %5.3f usec (minimum) and %5.3f usec (maximum)\n",
		tp->minimum_usec, tp->maximum_usec);
	if (tp->minimum_usec < tp->average_usec/1.5)
		printf(" ! WARNING: unusual low minimum\n");
	if (tp->maximum_usec > tp->average_usec*1.5)
		printf(" ! WARNING: unusual high maximum\n");
	printf("   standard deviation %5.3f usec = %3.1f %% (in %lu measurements)\n",
		tp->stddev_usec,
		100.0*tp->stddev_usec/tp->average_usec,
		(unsigned long)MEASUREMENTS);
	if (tp->timeout_end)
		printf(" ! WARNING: ended by time-out\n");
	printf("\n");
}
#endif

#ifdef XMLOUTPUTTER
void cxtime_print(struct cxtime_t *tp) {
	assert(tp);
	assert(tp->timings_usec == 0);
	printf("<cxtime>\n"
	       "<title>");
	show_formatted(0, 0, tp->description, 0, 1);
	printf("</title>\n"
	       "<prepare_code>\n");
	show_formatted(0, 0, tp->prepare_code, 1, 1);
	printf("</prepare_code>\n"
	       "<timed_code>\n");
	show_formatted(0, 0, tp->timed_code, 1, 1);
	printf("</timed_code>\n"
	       "<verify_code>\n");
	show_formatted(0, 0, tp->verify_code, 1, 1);
	printf("</verify_code>\n"
	       "<cleanup_code>\n");
	show_formatted(0, 0, tp->cleanup_code, 1, 1);
	printf("</cleanup_code>\n"
	       "<result repeat_count='%lu'\n"
	       "        average_usec='%.3f'\n"
	       "        minimum_usec='%.3f'\n"
	       "        maximum_usec='%.3f'\n"
	       "        overhead_usec='%.3f'\n"
	       "        stddev_usec='%.3f'\n"
	       "        timeout_end='%d'\n"
	       "        measurements='%lu'\n"
	       "/>\n",
		tp->repeat_count,
		tp->average_usec,
		tp->minimum_usec,
		tp->maximum_usec,
		tp->overhead_usec,
		tp->stddev_usec,
		tp->timeout_end,
		(unsigned long)MEASUREMENTS);
	printf("</cxtime>\n");
}
#endif

void cxtime_pessimize(const void *dummy, ...) {}

