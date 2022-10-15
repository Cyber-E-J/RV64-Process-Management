// 为你提供了一些实用的宏，请自行学习其含义和原理



/* csrw reg,val */

/* write_csr(reg,val)
   将寄存器val中的值写入 csr寄存器reg中
   调用"csrw (),()"
 */

#define write_csr(reg, val)                                     \
  ({                                                            \
    if (__builtin_constant_p(val) && (unsigned long)(val) < 32) \
      asm volatile("csrw " #reg ", %0" ::"i"(val));             \
    else asm volatile("csrw " #reg ", %0" ::"r"(val));          \
  })
//内联汇编，字母i表示立即数，r表示自动分配寄存器
//操作数，用%0来访问。这里没有[]给它起名字，所以直接这样表示
//

// csrw csr, rs1 CSRs[csr] = x[rs1]
// 写控制状态寄存器 (Control and Status Register Set). 伪指令(Pesudoinstruction), RV32I and
// RV64I.
// 对于 x[rs1]中每一个为 1 的位，把控制状态寄存器 csr 的的对应位置位，等同于 csrrs x0, csr,
// rs1.




/* csrr (out),reg */

/* read_csr(reg)
   读出寄存器的值
   调用"csrr ()"
 */
#define read_csr(reg)                             \
  ({                                              \
    unsigned long __tmp;                          \
    asm volatile("csrr %0, " #reg : "=r"(__tmp)); \
    __tmp;                                        \
  })
//输出操作数而言，等号"="代表输出变量用作输出，原来的值会被新值替换，而且是只写的

// csrr rd, csr x[rd] = CSRs[csr]
// 读控制状态寄存器 (Control and Status Register Read). 伪指令(Pesudoinstruction), RV32I and
// RV64I.
// 把控制状态寄存器 csr 的值写入 x[rd]，等同于 csrrs rd, csr, x0.



/* csrrs (out),reg,bit */

#define set_csr(reg, bit)                                              \
  ({                                                                   \
    unsigned long __tmp;                                               \
    if (__builtin_constant_p(bit) && (unsigned long)(bit) < 32)        \
      asm volatile("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "i"(bit)); \
    else                                                               \
      asm volatile("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "r"(bit)); \
    __tmp;                                                             \
  })


/* csrrc (out),reg,bit */

#define clear_csr(reg, bit)                                            \
  ({                                                                   \
    unsigned long __tmp;                                               \
    if (__builtin_constant_p(bit) && (unsigned long)(bit) < 32)        \
      asm volatile("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "i"(bit)); \
    else                                                               \
      asm volatile("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "r"(bit)); \
    __tmp;                                                             \
  })

#define rdtime() read_csr(time)
#define rdcycle() read_csr(cycle)
#define rdinstret() read_csr(instret)