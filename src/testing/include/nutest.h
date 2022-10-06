#ifndef NUTEST_H
#  define NUTEST_H

#  include <stdio.h>
#  include <string.h>
#  include <limits.h>

enum ETestResult {
  testSuccess,
  testFailure
};

struct TestStats {
  unsigned int numberOfTests;
  unsigned int numberOfFails;
  unsigned int numberOfPasses;
  unsigned int numberOfAssertions;
};


static void (*_setUpFunc)(void) = 0;
static void (*_oneTimeSetUpFunc)(void) = 0;
static void (*_teardownFunc)(void) = 0;
static void (*_oneTimeTeardownFunc)(void) = 0;
static enum ETestResult _lastResult;

static char _errorMessageBuffer[1024];
static char _annotationBuffer[USHRT_MAX];
static struct TestStats _testStats;


/*
 * _nut_Safe
 * Shields @code to the sourrounding statements.
 */
#  define _nut_Safe(code) do { code } while (0);

/*
 * nut_UnitTest
 * Defines a test method signature with the given @name.
 */
#  define nut_UnitTest(name) static void name(void)

/*
 * nut_TestFixture
 * Defines a test fixture signature with the given @name.
 */
#  define nut_TestFixture(name) static void name(void)

/*
 * nut_ConfigureSetUpFunc
 * Sets the function, that is executed before each test to
 * @value. Will be reset as soon as a fixture finished running.
 */
#  define nut_ConfigureSetUpFunc(value) _nut_Safe(_setUpFunc = value;)

/*
 * nut_ConfigureOneTimeSetUpFunc
 * Sets the function, that is executed once before the first test of
 * the following fixture, to @value. Will be reset as soon as the
 * fixture finished running.
 */
#  define nut_ConfigureOneTimeSetUpFunc(value) _nut_Safe(_oneTimeSetUpFunc = value;)

/*
 * nut_ConfigureTeardownFunc
 * Sets the function, that is executed after each test to
 * @value. Will be reset as soon as a fixture finished running.
 */
#  define nut_ConfigureTeardownFunc(value) _nut_Safe(_teardownFunc = value;)

/*
 * nut_ConfigureOneTimeTeardownFunc
 * Sets the function, that is executed once after the last test of
 * the following fixture, to @value. Will be reset as soon as the
 * fixture finished running.
 */
#  define nut_ConfigureOneTimeTeardownFunc(value) _nut_Safe(_oneTimeTeardownFunc = value;)

/*
 * nut_ExecuteUnitTest
 * Runs the given @unitTest and prints the results to stdout.
 */
#  define nut_ExecuteUnitTest(unitTest) _nut_Safe(\
       _lastResult = testSuccess;\
       if (_setUpFunc) (*_setUpFunc)();\
       \
       unitTest();\
       \
       if (_lastResult == testFailure) {\
	 _testStats.numberOfFails++;\
	 printf("\t\x1b[31mFAILED\x1b[0m \x1b[37;4m%s\x1b[0m\n", #unitTest);\
	 printf("\t%s\n", _errorMessageBuffer);\
       } else {\
	 printf("\t\x1b[32mPASSED\x1b[0m \x1b[37;4m%s\x1b[0m\n", #unitTest);\
	 _testStats.numberOfPasses++;\
       }\
       \
       printf("\t%d %s proven true.\n\n",\
	      _testStats.numberOfAssertions,\
	      _testStats.numberOfAssertions == 1\
	      ? "assertion has"\
	      : "assertions have");\
       _testStats.numberOfAssertions = 0;\
       _testStats.numberOfTests++;\
       fflush(stdout);\
       \
       if (_teardownFunc) (*_teardownFunc)();\
)

/*
 * nut_ExecuteFixture
 * Runs the fixture with the given @fixtureName and prints the results to stdout.
 */
#  define nut_ExecuteFixture(fixtureName) _nut_Safe(\
       printf("\x1b[35mFIXTURE\x1b[0m \x1b[37;4m%s\x1b[0m\n\n", #fixtureName);\
       if (_oneTimeSetUpFunc) (*_oneTimeSetUpFunc)();\
       \
       fixtureName();\
       \
       if (_oneTimeTeardownFunc) (*_oneTimeTeardownFunc)();\
       \
       nut_ConfigureSetUpFunc(0);\
       nut_ConfigureOneTimeTeardownFunc(0);\
       nut_ConfigureOneTimeSetUpFunc(0);\
       nut_ConfigureTeardownFunc(0);\
       \
       printf("\x1b[35mSTATS\x1b[0m \x1b[37;4m%s\x1b[0m\n\n", #fixtureName);\
       printf("\t%d tests in total ", _testStats.numberOfTests);\
       printf("(%d passed, %d failed)\n", _testStats.numberOfPasses, _testStats.numberOfFails);	\
       printf("\f");\
)

/*
 * nut_FailTest
 * Fails the test in which it is called manually.
 */
#  define nut_FailTest() _nut_Safe(\
       sprintf(_errorMessageBuffer,\
	  "\x1b[33;2m%s, line %d:\x1b[0m\n\tFailure triggered manually.",\
	  __FILE__,\
	  __LINE__\
       ); \
       _lastResult = testFailure;\
)

/*
 * nut_Assert
 * Evaluates the given @expr and prints the results to stdout.
 */
#  define nut_Assert(expr) _nut_Safe(\
       _testStats.numberOfAssertions++;\
       if (!(expr)) {\
	 sprintf(_errorMessageBuffer,\
	  "\x1b[33;2m%s, line %d:\x1b[0m\n\tAssertion was (%s).",\
	  __FILE__,\
          __LINE__,\
	  #expr\
         );\
         _lastResult = testFailure;\
       }\
)

/*
 * nut_Test
 * Adds @text remarks at the position where it is called in the test report.
 */
# define nut_Text(text) _nut_Safe(\
       sprintf(_annotationBuffer, "\x1b[36;2mREMARK\x1b[0m %s\n", text);\
       printf("%s\n", _annotationBuffer);\
)


#endif
