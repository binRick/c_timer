// MESON_BIN_ENABLED=true
#include "../src/c_timer.c"
///////////////////////////////////
#define INNER_QTY    3
#define INNER_MS     20
#define SLEEP_DUR    1000
///////////////////////////////////


int ct_test(void) {
  ct_start("Outer Milliseconds");
  for (int i = 0; i < INNER_QTY; ++i) {
    ct_start("Inner Milliseconds");
    usleep(SLEEP_DUR * INNER_MS);

    ct_set_unit(ct_MILLISECONDS);
    OK(ct_stop("Inner Milliseconds"));
  }
  ct_set_unit(ct_MILLISECONDS);
  OK(ct_stop("Outer Milliseconds"));

  return(0);
}


int main(const int argc, const char **argv){
  ct_start("Completed Tests in");

  assert(ct_test() == 0);

  ct_set_unit(ct_MILLISECONDS);
  OK(ct_stop("Completed Tests in"));
}
