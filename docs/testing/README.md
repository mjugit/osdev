# Unit testing

## Compatibility

New unit testing files should use the new style in [`nutest.h`]("../../src/testing/include/nutest.h). For compatibility reasons, the old macros are also supported, but marked as OBSOLETE (will be removed in the medium term). At the moment they have been set up to replace the old macros with the new ones.

## How to unit test

In unit testing, we generally set up a certain environment, execute a function in that context, and evaluate any results or states. Thereby we use assertions to compare expected states with actual states. For the management of these tests and the convenient evaluation the header `nutest.h` is available. Unit tests are managed in two types of entities. The smaller of these is the `nut_UnitTest`. This contains the code to generate and evaluate the results. Multiple unit tests are grouped into a `nut_TestFixture`. The grouping also allows to specify functions for the one-time setup and teardown of the scenarios or or each time before all tests.

## The [`nutest.h` header file]("../../src/testing/include/nutest.h)

#### nut_UnitTest
Defines a test method signature with the given @name.

```c
nut_UnitTest(name)
```

#### nut_TestFixture
Defines a test fixture signature with the given @name.

```c
nut_TestFixture(name)
```

#### nut_ConfigureSetUpFunc
Sets the function, that is executed before each test to
@value. Will be reset as soon as a fixture finished running.

```c
nut_ConfigureSetUpFunc(value)
```

#### nut_ConfigureOneTimeSetUpFunc
Sets the function, that is executed once before the first test of
the following fixture, to @value. Will be reset as soon as the
fixture finished running.
 ```c
nut_ConfigureOneTimeSetUpFunc(value) 
```

#### nut_ConfigureTeardownFunc
Sets the function, that is executed after each test to
@value. Will be reset as soon as a fixture finished running.
```c
nut_ConfigureTeardownFunc(value)
```

#### nut_ConfigureOneTimeTeardownFunc
Sets the function, that is executed once after the last test of
the following fixture, to @value. Will be reset as soon as the
fixture finished running.
 ```c
 nut_ConfigureOneTimeTeardownFunc(value)
```

#### nut_ExecuteUnitTest
Runs the given @unitTest and prints the results to stdout.
```c
nut_ExecuteUnitTest(unitTest)
```

#### nut_ExecuteFixture
Runs the fixture with the given @fixtureName and prints the results to stdout.
```c
nut_ExecuteFixture(fixtureName)
```

#### nut_FailTest
Fails the test in which it is called manually.
```c
nut_FailTest()
```

#### nut_Assert
Evaluates the given @expr and prints the results to stdout.
```c
nut_Assert(expr)
```

#### nut_Test
Adds @text remarks at the position where it is called in the test report.
```c
nut_Text(text)
```
