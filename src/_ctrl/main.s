! main.asm by @nieltg

export _main
_main:
	call _kernel_main
.loop:
	cli
	hlt
	jmp .loop
