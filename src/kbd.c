/**
 * Tugas Besar 1 IF2230 Operating System
 */

#include "anim.h"

#include "kbd.h"

void _kbd_irq_handler (void)
{
	char ch = inb (0x60);

	if (ch < 0x80)
		anim_is_enabled = !anim_is_enabled;

	outb (0x20, 0x61);
}

void kbd_init (void)
{
	/*
	 * http://inglorion.net/documents/tutorials/x86ostut/keyboard
	 * https://wiki.osdev.org/Interrupt_Vector_Table
	 */

#asm
	push    ds
	push    *0x0
	pop     ds
	cli
	mov     [0x24], #.irq
	mov     [0x26], cs
	sti
	pop     ds
	jmp     .end
.irq:
	cli
	pusha
	call    __kbd_irq_handler
	popa
	sti
	iret
.end:
#endasm
}
