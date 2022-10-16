#include "riscv.h"

extern void clock_init(void);


/* sstatus 共有32位 */
void intr_enable(void) {
  // 设置 sstatus[sie] = 1, 打开 s 模式的中断开关
  // your code
  set_csr(sstatus, 0x2);
}

void intr_disable(void) {
  // 设置 sstatus[sie] = 0, 关闭 s 模式的中断开关
  // your code
  clear_csr(sstatus, 0xfffffffffffffffd);
}

//C 语言中，可以使用取地址符和函数名，获取函数的地址。
void idt_init(void) {
  extern void trap_s(void);
  unsigned long long addr = &trap_s;
  // 向 stvec 寄存器中写入中断处理后跳转函数的地址
  // your code
  write_csr(stvec, addr);
  
}

void init(void) {
  idt_init();
  intr_enable();
  clock_init();
}
