.section .text.entry

.extern test
.global trap_s
.extern handler_s
.equ reg_size, 0x8
.align 2

trap_s:
	# save caller-saved registers and sepc

	# call handler_s(scause)
	
	# load sepc and caller-saved registers
	
	
	sret


.globl __switch_to
__switch_to:
	li    a4,  40 
	add   a3, a0, a4
	add   a4, a1, a4
	# Save context into prev->thread
	# your code

	# Restore context from next->thread
	# your code

	# return to ra
	ret


.globl __init_sepc
__init_sepc:
	la  t0, test
	csrw sepc, t0
	sret
