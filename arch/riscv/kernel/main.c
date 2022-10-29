#include "test.h"
extern test();
extern init();

int main() {
  puts("ZJU OS LAB 3      Student1:123456 张三     Student2:123456 李四\n");
  init();
  test();
  while (1) {
  }
  return 0;
}