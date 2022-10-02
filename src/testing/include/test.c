#include "nutest.h"

nut_UnitTest(dbg_ThisTestWillFail) {
  nut_FailTest();
}

nut_UnitTest(dbg_AnotherFailure) {
  nut_Assert(1 > 2) ;
}

nut_UnitTest(dbg_ThisTestWillSucceed) {
    nut_Assert(1 == 1);
}

nut_UnitTest(dbg_ThisTestWillSucceed2) {
    nut_Assert(1 == 1);
}

nut_TestFixture(dbg_MyTestFixture) {
  nut_Text("\
Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor \
invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et \
accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata \
sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing \
elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, \
sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita \
kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.\
");
  
  nut_ExecuteUnitTest(dbg_ThisTestWillFail);
  nut_ExecuteUnitTest(dbg_AnotherFailure);
  nut_ExecuteUnitTest(dbg_ThisTestWillSucceed);
  nut_ExecuteUnitTest(dbg_ThisTestWillSucceed2);
}


int main(void) {
  nut_ExecuteFixture(dbg_MyTestFixture);
  return 0;
}
