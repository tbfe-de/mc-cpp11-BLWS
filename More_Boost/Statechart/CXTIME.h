/**
 @file
 @brief Makros to Meassure CPU time

 The \c CXTIME macro basically is a call-wrapper around an arbitrary statement.
 Around the wrapped statement some small support functions from the module
 \c cxtime.o will be called so that the CPU time of the given statement can
 be meassured.

 The support library makes use of system function \c clock(). This function
 returns the amount of CPU time consumed meassured in \c CLOCKS_PER_SEC. As
 the resolution of the \c clock() system function is usually too coarse, the
 statement to be timed must typically be called very often in a loop. The
 \c CXTIME macro arranges to increas the number of runs through this loop until
 reasonable total cpu time will result (more details see below).
 

 The CXTIME macro has 5 arguments:
 (1) Some descriptive text.
 (2) Optional code to prepare the time taking;
 (3) The code (fragment) statement for which the timing is to be taken;
 (4) Optional code to verify the outcome;
 (5) Optional code to cleanup after the time taking;

 Items (2) to (5) in the list below may single statements or statement
 sequences.  Furthermore they can - and frequently will - all be empty
 except item (3). (Technically this one could also be empty but that
 would make not sense as the whole purpose of the \c CXTIME macro is to
 time excactly this.)

 Results are sent to standard output in a 'human-readable' format. With
 a minor change to the source of module \c cxtime.c data may also be provided
 in XML format, which would ease postprocessing if tabular output (say for
 a survey) needs to be prepared.

 The above explanation together with some examples should be sufficient to
 make use of the CXTIME macro. The remaining description is meant to explain
 some of the inner workings and tries to supply the background information
 that helps to interpret the results.

 As shortly mentioned above the standard technique for meassuring CPU
 time consumption of a given stamenent or statement sequence is to pack
 this in a loop and execute this loop 'often enough' to get meaningful
 results. Furthermore sometimes there is the need to prepare a meaningful
 environment for the statement(s) to time, to verify the results or to
 cleanup afterwards. The time required for prepare, verify, and
 cleanup should of course be excluded from the meassured time.

 Where the \c CXTIME macro helps is basically to achieve two goals:
 (a) Automatically find 'how often' the loop needs be executed.
 (b) Separate the 'interesting' results from the rest.

 To achieve goal (a) the initial number of times through the loop is
 rather short (configurable with \c INITIALREPEAT in \c cxtime.c).  The
 meassurement with a loop of this length is then taken a number of
 times (configurable with either \c CXTIME_MEASSUREMENTS in \c CXTIME.h or
 with \c MEASSUREMENTS in \c cxtime.c). From the results the average and
 the standard deviation is calculated. If the latter is above a given
 treshold (configurable with \c PERCENTSTDDEV in \c cxtime.c) the
 meassurements are repeated with the number of times through the loop
 doubled. This may happen several times until the standard deviation is
 low enough or the total time used exceeds a given limit (configurable
 with \c TOTALTIMELIMIT \c in cxtime.c).

 To achieve goal (b) the macro actually executes the following
 (numbering from above):
 - Exactly once: (2) - (3) - (4) - (5) [give (4) a chance to fail]
 - In a loop (N times): only (2) and (5) [time meassured]
 - In a loop (N times): (2), (3), and (5) [time meassured]
 In the results the time taken first i.e. (time for prepare and cleanup)
 is subtracted from the results of the second meassurement and of
 course, the total time used is divided by the number of times through
 the loop. So the main information communicated back to the user is
 the number of times a single execution of the statement would have
 taken.

 Sometimes the problem is that the time for the required prepare and
 cleanup dominates the time for the statement that is of interest, or
 in other words that - using the numbers from above - the time for
 (2) + (5) is more than only a small percentge of the time for (3).

 In this case the macro CXTIME can be replaced with CXTIME_10. This
 effectively executes (an meassures) in a loop N times the sequence
 (2), 10*(3), and (5) thereby reducing the relative overhead for
 preparation (2) and cleanup (5) by a factor of 10. For the sake of
 consistent and simple implementation, CXTIME_10 internally just calls
 CXTIME, handing over the part to be meassured (third macro argument)
 ten times in sequence. Therefore the final output too will textually
 show ten repetitions of the timed sequence. To avoid confusion the
 total runtime is NOT divided by (another) factor of ten - i.e. it
 shows the execution time of what is visually marked. But to serve
 as a as a gentle reminder that CXTIME_10 was used the text "10 x "
 is prepended to the headline originally specified. (The intention
 was to make it easy to switch between CXTIME and CXTIME_10 as the need
 arises.)
*/
#ifndef CXTIME_h
#define CXTIME_h

/*
 NOTE: The following macro definition maybe activated or deactivated
 ====  by moving it out-of or inside this comment section, which has
       two consequences:

   (1) THE SUPPORT MODULE (cxtime.c) MUST BE RE-COMPILED !!!!!!!!!!!!

   (2) If the macro is defined the array to holding the measured
       values is NOT any more allocated on the heap, i.e. the host
       does not need to support malloc and free.

#define CXTIME_MEASUREMENTS 50
*/

struct cxtime_t {
	const char *description;
	const char *prepare_code;
	const char *timed_code;
	const char *verify_code;
	const char *cleanup_code;
	double overhead_usec;
	double full_usec;
	double stddev_usec;
	double average_usec;
	double minimum_usec;
	double maximum_usec;
	int timeout_end;
#ifdef	CXTIME_MEASUREMENTS
	double timings_usec[CXTIME_MEASUREMENTS];
#else
	double *timings_usec;
#endif
	int ith_timing;
	unsigned long repeat_count;
	double time_limit;
	double clock_start;
};

#ifdef __cplusplus
extern "C" {
#endif

void cxtime_setup(struct cxtime_t *tp, const char *description,
		 const char *prepare_code, const char *timed_code,
		 const char *cleanup_code, const char *check);
void cxtime_started(struct cxtime_t *tp);
void cxtime_ended_p_p(struct cxtime_t *tp);
void cxtime_ended_all(struct cxtime_t *tp);
int cxtime_repeat_inner(struct cxtime_t *tp);
int cxtime_repeat_outer(struct cxtime_t *tp);
void cxtime_print(struct cxtime_t *tp);
void cxtime_pessimize(const void *, ...);


#ifdef __cplusplus
}
#endif
	

#define CXTIME(description, prepare, code, verify, cleanup)\
if (description) {\
	struct cxtime_t cxtime_data;\
	prepare code verify cleanup\
	cxtime_setup(&cxtime_data, description, #prepare, #code, #verify, #cleanup);\
	do {\
		while (cxtime_repeat_inner(&cxtime_data)) {\
			{\
				cxtime_started(&cxtime_data);\
				unsigned long r = cxtime_data.repeat_count + 1;\
				while (--r != 0) {\
					prepare cleanup\
				}\
				cxtime_ended_p_p(&cxtime_data);\
			}\
			{\
				cxtime_started(&cxtime_data);\
				unsigned long r = cxtime_data.repeat_count + 1;\
				while (--r != 0) {\
					prepare code cleanup\
				}\
				cxtime_ended_all(&cxtime_data);\
			}\
		}\
	} while (cxtime_repeat_outer(&cxtime_data));\
	cxtime_print(&cxtime_data);\
}

#define CXTIME_10(description, prepare, code, verify, cleanup)\
	CXTIME("10 x " description, prepare,\
		code code code code code\
		code code code code code,\
		verify, cleanup)
		
#endif
