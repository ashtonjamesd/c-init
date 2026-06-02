#include "../lib/ctest.h"

should(correctly_add_two_numbers) {
   expect(2 + 5 == 7);
}

int main(void) {
   // run a unit test
   run_test(correctly_add_two_numbers);
   conclude_test_runner();

   return 0;
}
