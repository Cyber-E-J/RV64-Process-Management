#include "defs.h"

extern main(), puts(), put_num(), ticks;
extern void clock_set_next_event(void);

void handler_s(uint64_t cause) {
  // interrupt
  if (1) {
    // supervisor timer interrupt
    if (1) {
      // 设置下一个时钟中断，打印当前的中断数目。
      // your code
    }
  }
}