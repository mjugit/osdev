#ifndef UTEST_H
#  define UTEST_H

/*
 * This library is OBSOLETE!
 * Please use the new syntax defined in 'nutest.h'. The methods
 * included here are configured to forward or invalidate existing
 * macro calls for compatibility reasons.
 */

#  include "nutest.h"
#  include <string.h>
#  include <stdio.h>

/*
 * OBSOLETE
 * Was replaced with ETestResult.
 */
#  define TEST_SUCCESS testSuccess
#  define TEST_FAILURE testFailure

/*
 * OBSOLETE
 * _safe
 * Was used to shield the @code to the sourrounding statements.
 */
#  define _safe(code) _nut_Safe(code)

/*
 * OBSOLETE
 * report
 * Was used to print the statistics of a test run. The
 * nut_ExecuteFixture method does this on its own now, so there is no
 * need to trigger it manually.
 */
#  define report()

/*
 * OBSOLETE
 * deftest
 * Was used to define a new unit test block.
 */
#  define deftest(name) nut_UnitTest(name)

/*
 * OBSOLETE
 * deffixture
 * Was used to define a group test.
 */
#  define deffixture(name) nut_TestFixture(name)

/*
 * OBSOLETE
 * setupfn
 * Was used to set the one time setup function for the next fixture
 * execution.
 */
#  define setupfn(ptr) nut_ConfigureOneTimeSetUpFunc(ptr)

/*
 * OBSOLETE
 * teardownfn
 * Was used to set the one time teardown function for the next fixture
 * execution.
 */
#  define teardownfn(ptr) nut_ConfigureOneTimeTeardownFunc(ptr)

/*
 * OBSOLETE
 * runtest
 * Was used to execute a unit test.
 */
#  define runtest(test) nut_ExecuteUnitTest(test)

/*
 * OBSOLETE
 * runfixture
 * Was used to execute a set of unit tests.
 */
#  define runfixture(name) nut_Text("These tests use legacy keywords."); nut_ExecuteFixture(name)

/*
 * OBSOLETE
 * resetstats
 * Was used to reset the statistics of the test runs.
 */
#  define resetstats()

/*
 * OBSOLETE
 * fact
 * Was used to define assertions.
 */
#  define fact(expr) nut_Assert(expr)

/*
 * OBSOLETE
 * fail
 * Was used to manually fail a test.
 */
#  define fail() nut_FailTest()

#endif // UTEST_H
