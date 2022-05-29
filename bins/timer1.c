// MESON_BIN_ENABLED=true
#include "../src/c_timer.c"
#include "../submodules/b64.c/b64.h"
///////////////////////////////////
#define BUF          1024
#define INNER_QTY    3
#define INNER_MS     20
#define SLEEP_DUR    1000
///////////////////////////////////
char *str, *dur, *enc, *dec;
///////////////////////////////////

#define DO_TEST(UNIT_NAME, UNIT, DURATION_NS)    {                     \
    char *msg = malloc(BUF);                                           \
    sprintf(dec                                                        \
            , "%s|%d|%s"                                               \
            , UNIT_NAME                                                \
            , DURATION_NS                                              \
            , UNIT_NAME                                                \
            );                                                         \
    enc = (char *)b64_encode((const unsigned char *)dec, strlen(dec)); \
    sprintf(msg                                                        \
            , "%12s Test> %10dns -> %15s"                              \
            , UNIT_NAME                                                \
            , DURATION_NS                                              \
            , UNIT_NAME                                                \
            );                                                         \
    ct_start(msg);                                                     \
    usleep(DURATION_NS / SLEEP_DUR);                                   \
    ct_set_unit(UNIT);                                                 \
    OK(ct_stop(msg));                                                  \
    free(msg);                                                         \
}


int init(void) {
  str = malloc(1024);
  dur = malloc(1024);
  enc = malloc(1024);
  dec = malloc(1024);

  return(0);
}


int ct_test(void) {
  DO_TEST("Nanoseconds", ct_NANOSECONDS, SLEEP_DUR * 1);
  DO_TEST("Nanoseconds", ct_NANOSECONDS, SLEEP_DUR * 10);
  DO_TEST("Nanoseconds", ct_NANOSECONDS, SLEEP_DUR * 75);
  DO_TEST("Nanoseconds", ct_NANOSECONDS, SLEEP_DUR * 300);

  DO_TEST("Microseconds", ct_MICROSECONDS, SLEEP_DUR * 1);
  DO_TEST("Microseconds", ct_MICROSECONDS, SLEEP_DUR * 10);
  DO_TEST("Microseconds", ct_MICROSECONDS, SLEEP_DUR * 200);
  DO_TEST("Microseconds", ct_MICROSECONDS, SLEEP_DUR * 400);
  DO_TEST("Microseconds", ct_MICROSECONDS, SLEEP_DUR * 750);

  DO_TEST("Milliseconds", ct_MILLISECONDS, SLEEP_DUR * 1);
  DO_TEST("Milliseconds", ct_MILLISECONDS, SLEEP_DUR * 400);
  DO_TEST("Milliseconds", ct_MILLISECONDS, SLEEP_DUR * 900);

  DO_TEST("Seconds", ct_SECONDS, SLEEP_DUR * 1000 * 1000);


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

  assert(init() == 0);
  assert(ct_test() == 0);

  ct_set_unit(ct_MILLISECONDS);
  OK(ct_stop("Completed Tests in"));
}
