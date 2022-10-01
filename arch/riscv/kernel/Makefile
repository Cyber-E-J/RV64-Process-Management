# 函数调用，很像变量的使用，也是以 $ 来标识的，其语法如下：
# $(<function> <arguments>)




# $(wildcard *.c) 可以获取当前目录下的所有的 .c 文件列表



ASM_SRC   = $(sort $(wildcard *.S))
C_SRC     = $(sort $(wildcard *.c))

# $(patsubst 原模式, 目标模式, 文件列表)






# patsubst¶

# $(patsubst <pattern>,<replacement>,<text>)
# 名称：模式字符串替换函数。
# 功能：查找 <text> 中的单词（单词以“空格”、“Tab”或“回车”“换行”分隔）是否符合模式 <pattern> ，
# 如果匹配的话，则以 <replacement> 替换。这里， <pattern> 可以包括通配符 % ，表示任意长度的字串。
# 如果 <replacement> 中也包含 % ，那么， <replacement> 中的这个 % 将是 <pattern> 中的那个 % 所代表的字串。
# （可以用 \ 来转义，以 \% 来表示真实含义的 % 字符）
# 返回：函数返回被替换过后的字符串。
# 示例：

# $(patsubst %.c,%.o,x.c.c bar.c)
# 把字串 x.c.c bar.c 符合模式 %.c 的单词替换成 %.o ，返回结果是 x.c.o bar.o

# 备注：这和我们前面“变量章节”说过的相关知识有点相似。如 $(var:<pattern>=<replacement>;) 
# 相当于 $(patsubst <pattern>,<replacement>,$(var)) ，而 $(var: <suffix>=<replacement>) 则相当于 $(patsubst %<suffix>,%<replacement>,$(var)) 。

# 例如有:

# objects = foo.o bar.o baz.o，
# 那么， $(objects:.o=.c) 和 $(patsubst %.o,%.c,$(objects)) 是一样的。








OBJ		    = $(patsubst %.S,%.o,$(ASM_SRC)) $(patsubst %.c,%.o,$(C_SRC))



# 你可以通过 @echo 输出这些变量, 来查看他们起到了什么样的作用

# 通常，make会把其要执行的命令行在命令执行前输出到屏幕上。当我们用 @ 字符在命令行前
# 那么，这个命令将不被make显示出来，最具代表性的例子是，我们用这个功能来向屏幕显示一些信息。如:

# @echo 正在编译XXX模块......
# 当make执行时，会输出“正在编译XXX模块……”字串，但不会输出命令，如果没有“@”，那么，make将输出:



# echo 正在编译XXX模块......
# 正在编译XXX模块......

# 如果make执行时，带入make参数 -n 或 --just-print 
# 那么其只是显示命令，但不会执行命令，这个功能很有利于我们调试我们的Makefile
# 看看我们书写的命令是执行起来是什么样子的或是什么顺序的。


all: $(OBJ)

# 通配符 wildcard
# $< 自动化变量 表示第一个依赖文件
# 每条命令的开头必须以 Tab 键开头



%.o:%.S
	$(CC) $(CFLAG) -c $<
%.o:%.c
	$(CC) $(CFLAG) -c $<



# 2>	将错误输出重定向到文件
clean:
	$(shell rm *.o 2>/dev/null)
