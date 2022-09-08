#include "utest.h"

// Prototypes go here
testfixture(testof_utest_h);
test(this_will_fail);
test(this_will_pass);
void examplemsg(void);

int main(void) {
  beforetest(&examplemsg);
  aftertest(&examplemsg);
  runfixture(testof_utest_h);
  testreport();
  // setup and teardown is reseted after a fixure is executed
  
  runfixture(testof_utest_h);
  testreport();

  // Stats have to be reseted manually
  resetstats();
  testreport();
 
  return 0;
}


// Define a group of tests
testfixture(testof_utest_h) {
  runtest(this_will_fail);
  runtest(this_will_pass);
}

void examplemsg(void) {
  printf("<<< printmsg was called >>>\n");
}

test(this_will_fail) {
  assert_that(5 == 2);
}

test(this_will_pass) {
  assert_that(1);
}
