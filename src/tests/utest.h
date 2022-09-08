#ifndef UTEST_H
#define UTEST_H

#include <string.h>
#include <stdio.h>

// Maximum length of last message
#define MSGBUFF_SIZE 1024
static char msgbuff[MSGBUFF_SIZE];


static int _total_tests = 0;
static int _total_tests_passed = 0;
static int _total_assertions_evaluated = 0;
static int _total_tests_failed = 0;
static int _test_status = 0;

static void (*_setupfunc)(void) = NULL;
static void (*_teardownfunc)(void) = NULL;


#define test(name) static void name(void)
#define testfixture(name) static void name(void)

#define _safeblock(block) do {\
      block;\
    } while (0);

#define runfixture(name) _safeblock(\
    name();\
    _setupfunc = NULL;\
    _teardownfunc = NULL;\
)


#define beforetest(setup) _safeblock(\
    _setupfunc = setup;\
)

#define aftertest(teardown) _safeblock(\
    _teardownfunc = teardown;\
)

#define runtest(test) _safeblock(\
   if (_setupfunc) (*_setupfunc)();\
   _test_status = 0; \
   test(); \
   if (_test_status) {\
     _total_tests_failed++;\
     printf("\n%s\n", msgbuff);\
   } else {\
     _total_tests_passed++;\
   }\
   _total_tests++;\
   fflush(stdout);\
   if (_teardownfunc) (*_teardownfunc)();\
)

#define testreport() _safeblock(\
    printf("\n\n\t%8d %s\n\t%8d %s\n\t%8d %s\n\t%8d %s\n\n", \
	   _total_tests, "Tests total",\
	   _total_assertions_evaluated, "Assertions evaluated",\
	   _total_tests_passed, "Passed",\
	   _total_tests_failed, "Failed"); \
)

#define resetstats() _safeblock(\
    _total_tests = 0;\
    _total_assertions_evaluated = 0;\
    _total_tests_passed = 0;\
    _total_tests_failed = 0;\
)


#define assert_that(expression) _safeblock(\
    _total_assertions_evaluated++;\
    if (!(expression)) {\
	snprintf(msgbuff, MSGBUFF_SIZE, "[FAILED] %s\n\t %s, line %d: (%s)",\
	     __func__, __FILE__, __LINE__, #expression);\
	_test_status = 1;\
	return;\
    } else {\
        printf("[PASSED] %s\n",  __func__);\
    }\
)

#endif // UTEST_H
