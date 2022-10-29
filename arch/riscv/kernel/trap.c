#include "defs.h"

extern main(), puts(), put_num(), ticks, do_timer();

extern void clock_set_next_event(void);


void handler_s(uint64_t cause, uint64_t epc) {
  // interrupt
  if (cause & 0x1000000000000000 == 0x1000000000000000) {
    // supervisor timer interrupt
    uint64_t timer_interrupt = cause & 0x7fffffffffffffff;
    if (timer_interrupt == 0x5) {
      // 设置下一个时钟中断，打印当前的中断数目。
      // your code
      puts("Supervisior mode timer interrupt number = ");
      put_num(ticks);
      clock_set_next_event();
    }
  }
}