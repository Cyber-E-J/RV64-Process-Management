
# 当make嵌套调用时（参见前面的“嵌套调用”章节），上层Makefile中定义的变量会以系统环境变量的方式传递到下层的Makefile 中。
# 当然，默认情况下，只有通过命令行设置的变量会被传递。
# 而定义在文件中的变量，如果要向下层Makefile传递，则需要使用export关键字来声明。

# export 关键字定义的变量在调用子 Makefile 文件时依然有效
export
CROSS_  = riscv64-unknown-elf-
CC      = $(CROSS_)gcc
LD      = $(CROSS_)ld
OBJCOPY = $(CROSS_)objcopy



# 还有一个比较有用的操作符是 ?= ，先看示例：
# FOO ?= bar
# 其含义是，如果FOO没有被定义过，那么变量FOO的值就是“bar”，
# 如果FOO先前被定义过，那么这条语将什么也不做，其等价于：
# ifeq ($(origin FOO), undefined)
#     FOO = bar
# endif

DEBUG  ?= true

# gcc 编译相关参数
ISA     = rv64imafd
ABI     = lp64
INCLUDE = -I$(shell pwd)/include -I$(shell pwd)/arch/riscv/include
CF      = -g -march=$(ISA) -mabi=$(ABI) -mcmodel=medany -ffunction-sections -fdata-sections -nostartfiles -nostdlib -nostdinc -fno-builtin -static -lgcc 
CFLAG   = ${CF} ${INCLUDE} ${TASK_MM}


# 追加变量值 +=

# 第二个条件关键字是 ifneq 。语法是：
# ifneq (<arg1>, <arg2>)
# ifneq '<arg1>' '<arg2>'
# ifneq "<arg1>" "<arg2>"
# ifneq "<arg1>" '<arg2>'
# ifneq '<arg1>' "<arg2>"
# 其比较参数 arg1 和 arg2 的值是否相同，如果不同，则为真。

ifneq ($(DEBUG), )  
  CFLAG += -DDEBUG_LOG
endif


all: vmlinux


# 正像我们前面例子中的“clean”一样，既然我们生成了许多文件编译文件，我们也应该提供一个清除它们的“目标”以备完整地重编译而用。 （以“make clean”来使用该目标）

# 因为，我们并不生成“clean”这个文件。“伪目标”并不是一个文件，只是一个标签，由于“伪目标”不是文件，所以make无法生成它的依赖关系和决定它是否要执行。我们只有通过显式地指明这个“目标”才能让其生效。当然，“伪目标”的取名不能和文件名重名，不然其就失去了“伪目标”的意义了。

# 当然，为了避免和文件重名的这种情况，我们可以使用一个特殊的标记“.PHONY”来显式地指明一个目标是“伪目标”，向make说明，不管是否有这个文件，这个目标就是“伪目标”。

.PHONY: vmlinux run debug clean

vmlinux:

# make 定义了很多默认变量，像常用的命令或者是命令选项之类的，什么CC啊，CFLAGS啊之类。
# $(MAKE)就是预设的 make 这个命令的名称（或者路径）


# -C <dir>, --directory=<dir>
# 指定读取makefile的目录。如果有多个“-C”参数，make的解释是后面的路径以前面的作为相对路径，
# 并以最后的目录作为被指定目录。如：“make -C ~hchen/test -C prog”等价于“make -C ~hchen/test/prog”。
	$(MAKE) -C arch/riscv all 


	$(LD) -T arch/riscv/kernel/vmlinux.lds arch/riscv/kernel/*.o arch/riscv/libs/*.o -o vmlinux
	$(shell test -d arch/riscv/boot || mkdir -p arch/riscv/boot)

	$(OBJCOPY) -O binary vmlinux arch/riscv/boot/Image
	
# names的缩写, nm命令主要是用来列出某些文件中的符号(说白了就是一些函数和全局变量等)
	nm vmlinux > System.map
	@echo "\033[32mMake vmlinux Success! \033[0m"

run: vmlinux
	@qemu-system-riscv64 -nographic --machine virt -bios default -device loader,file=vmlinux,addr=0x80200000 -D log

debug: vmlinux
	@qemu-system-riscv64 -nographic -machine virt -bios default -device loader,file=vmlinux,addr=0x80200000 -S -s

clean:
	$(MAKE) -C arch/riscv clean
	$(shell test -f vmlinux && rm vmlinux)
	$(shell test -f System.map && rm System.map)
	@echo "\033[32mMake clean Success! \033[0m"

