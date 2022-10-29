#include "test.h"
extern test();
extern init();

int main() {
  puts("ZJU OS LAB 3      Student1:32000104810 周逸杰     Student2:320012523 张景森\n");
  init();
  test();
  while (1) {
  }
  return 0;
}