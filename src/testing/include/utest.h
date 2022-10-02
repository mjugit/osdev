#ifndef UTEST_H
#define UTEST_H

#include "nutest.h"
#include <string.h>
#include <stdio.h>

#define TEST_SUCCESS testSuccess
#define TEST_FAILURE testFailure

#define _safe(code) _nut_Safe(code)

// Print the statistics of the last run
#define report()

// Defines a test
#define deftest(name) nut_UnitTest(name)

// Defines a group of tests, that should be executed together
#define deffixture(name) nut_TestFixture(name)

// Sets the function that will be executed before each test
#define setupfn(ptr) nut_ConfigureOneTimeSetUpFunc(ptr)

// Sets the function that will be executed after each test.
#define teardownfn(ptr) nut_ConfigureOneTimeTeardownFunc(ptr)

// Run a single test
#define runtest(test) nut_ExecuteUnitTest(test)

// Run a group of tests
#define runfixture(name) nut_ExecuteFixture(name)

// Reset counters
#define resetstats()

#define fact(expr) nut_Assert(expr)

#define fail() nut_FailTest()

#endif // UTEST_H
