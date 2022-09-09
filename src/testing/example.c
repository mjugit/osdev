#include "include/utest.h"

deftest(will_always_fail) {
  fact(4 == 3);
  fact(1);
  fact(0);
  fact("as");
}

deftest(will_succeed) {
  fact(1);
}

deftest(another_one) {
  fact(2);
}

deffixture(testfixture) {
  runtest(will_always_fail);
  runtest(will_succeed);
  runtest(another_one);
}

int main(void) {
  runfixture(testfixture);
  report();

  return 0;
}
