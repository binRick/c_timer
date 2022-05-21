// MESON_BIN_ENABLED=true
#include "../src/c_timer.c"
char *str;
char *enc;
char *dec;
char *str = "timer0";


int main(const int argc, const char **argv){
  enc = (char *)b64_encode((const unsigned char *)str, strlen(str));
  OK(enc);

  dec = (char *)b64_decode(enc, strlen(enc));
  OK(dec);
  return(0);
}
