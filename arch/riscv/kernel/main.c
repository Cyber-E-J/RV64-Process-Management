#include "defs.h"
#include "print.h"
extern int test();

int main() {
  puts("Hello riscv \n");
  // Change the number to your stu_id.
  //puts("3200104810\n");


  /* for debug */
  // puts("test: before put_num\n");


  put_num(3200104810);



  /* for debug */
  // puts("test: after put_num\n");

  test();
  return 0;
}