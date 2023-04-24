#include <cstdio>
#include <cstdlib>

void errif(bool condition, const char *msg) {
  if (condition) {
    perror(msg);
    exit(-1);
  }
}