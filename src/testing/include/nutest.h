#ifndef NUTEST_H
#  define NUTEST_H

enum ETestResult {
  testSuccess,
  testFailure
};

struct TestStats {
  unsigned int numberOfTests;
  unsigned int numberOfFails;
  unsigned int numberOfPasses;
};



static void (*_setUpFunc)(void) = 0;
static void (*_oneTimeSetUpFunc)(void) = 0;
static void (*_teardownFunc)(void) = 0;
static void (*_oneTimeTeardownFunc)(void) = 0;
static enum ETestResult _lastResult;

static char _errorMessageBuffer[1024];
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
#  define nut_ConfigureOneTimeTeardownFunc(value) _nut_Safe(_oneTimeTearDownFunc = value;)

#  define nut_ExecuteUnitTest(unitTest) _nut_safe(\
       if (_setUpFunc) (*_setUpFunc)();\
       \
       _lastResult = testSuccess;\
       unitTest();\
       \
       if (_lastResult == testFailure) {\
	 _stats.numberOfFailures++;\
	 printf("\x1b[31mFAIL\x1b[0m\t %s\n", #unitTest);\
	 printf("%s\n", _errorMessageBuffer);\
       } else {\
	 printf("\x1b[32mPASS\x1b[0m %s\n", #unitTest);\
	 _stats.numberOfPasses++;\
       }\
       \
       _stats.numberOfTests++;\
       fflush(stdout);\
       \
       if (_teardownFunc) (*_teardownFunc)();\
)

#  define nut_ExecuteFixture(fixtureName) _nut_safe(\
       if (_oneTimeSetUpFunc) (*_oneTimeSetUpFunc)();\
       \
       fixtureName();\
       \
       if (_oneTimeTearDownFunc) (*oneTimeTearDownFunc)()\
       \
       nut_ConfigureSetUpFunc(0);\
       nut_ConfigureOneTimeTeardownFunc(0);\
       nut_ConfigureOneTimeSetUpFunc(0);\
       nut_ConfigureTeardownFunc(0);\
)
       

#endif
