.section .text

.global trap_s
.extern handler_s
.equ reg_size, 0x8
.align 2

trap_s:
	# save caller-saved registers and sepc

	# call handler_s(scause)
	
	# load sepc and caller-saved registers
	
	sret
