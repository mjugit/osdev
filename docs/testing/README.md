# Unit testing

## Compatibility

New unit testing files should use the new style in [`nutest.h`]("../../src/testing/include/nutest.h). For compatibility reasons, the old macros are also supported, but marked as OBSOLETE (will be removed in the medium term). At the moment they have been set up to replace the old macros with the new ones.

## How to unit test

In unit testing, we generally set up a certain environment, execute a function in that context, and evaluate any results or states. Thereby we use assertions to compare expected states with actual states. For the management of these tests and the convenient evaluation the header `nutest.h` is available. Unit tests are managed in two types of entities. The smaller of these is the `nut_UnitTest`. This contains the code to generate and evaluate the results. Multiple unit tests are grouped into a `nut_TestFixture`. The grouping also allows to specify functions for the one-time setup and teardown of the scenarios or or each time before all tests.

## The [`nutest.h` header file]("../../src/testing/include/nutest.h)

