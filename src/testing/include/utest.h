#ifndef UTEST_H
#define UTEST_H

#include <string.h>
#include <stdio.h>

#define TEST_SUCCESS 0
#define TEST_FAILURE 1


#define MSGBUFF_LEN 1024
static char _msgbuff[MSGBUFF_LEN];

static unsigned int _ntests;
static unsigned int _npassed;
static unsigned int _nasserts;
static unsigned int _nfailures;
static unsigned int _state;

static void (*_setupfn)(void) = NULL;
static void (*_teardownfn)(void) = NULL;


#define _safe(code) do { code } while(0);

// Print the statistics of the last run
#define report() _safe(\
    printf("\nReport:\n");\
    printf("  %8d %s\n", _ntests, "tests total");\
    printf("  %8d %s\n", _nasserts, "assertions evaluated");\
    printf("  %8d %s\n", _npassed, "passed");\
    printf("  %8d %s\n", _nfailures, "failed");\
)

// Defines a test
#define deftest(name) static void name(void)

// Defines a group of tests, that should be executed together
#define deffixture(name) static void name(void)

// Sets the function that will be executed before each test
#define setupfn(ptr) _safe(_setupfn = ptr;)

// Sets the function that will be executed after each test.
#define teardownfn(ptr) _safe(_teardownfn = ptr;)

// Run a single test
#define runtest(test) _safe(\
    if (_setupfn) \
	(*_setupfn)();\
    _state = TEST_SUCCESS;\
    test();\
    if (_state == TEST_FAILURE) {\
	_nfailures++;\
	printf("[FAIL] %s\n", #test);\
	printf("%s\n", _msgbuff);\
    } else {\
      printf("[ OK ] %s\n", #test);\
	_npassed++;\
    };\
    _ntests++;\
    fflush(stdout);\
    if (_teardownfn)\
	(*_teardownfn)();\
)

// Run a group of tests
#define runfixture(name) _safe(name(); _setupfn = _teardownfn = NULL;)

// Reset counters
#define resetstats() _safe(_ntests = _npassed = _nasserts = _nfailures = 0;)

#define fact(expr) _safe(\
    _nasserts++;\
    if (!(expr)) {\
	snprintf(_msgbuff, MSGBUFF_LEN, "\t%s, l%d: (%s)",\
		 __FILE__, __LINE__, #expr);\
	_state = TEST_FAILURE;\
    }\
)

#define fail() _safe(\
    snprintf(_msgbuff, MSGBUFF_LEN, "\t%s, l%d: (%s)",\
	     __FILE__, __LINE__, "fail");\
    _state = TEST_FAILURE;\
)

#endif // UTEST_H
