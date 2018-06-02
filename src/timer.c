/**
 * Tugas Besar 1 IF2230 Operating System
 */

#include "anim.h"

#include "timer.h"

void _timer_irq_handler (void)
{
	if (anim_is_idle ())
		reboot ();

	anim_next ();
	anim_render ();

	outb (0x20, 0x20);
}

void timer_init (void)
{
#asm
	cli
#endasm

	/*
	 * http://inglorion.net/documents/tutorials/x86ostut/keyboard
	 * http://osdever.net/bkerndev/Docs/pit.htm
	 * https://wiki.osdev.org/Interrupt_Vector_Table
	 * https://wiki.osdev.org/Programmable_Interval_Timer
	 */

	outb (0x43, 00110100b);

	outb (0x40, 0xFF);
	outb (0x40, 0xFF);

#asm
	push    ds
	push    *0x0
	pop     ds
	mov     [0x20], #.irq
	mov     [0x22], cs
	sti
	pop     ds
	jmp     .end
.irq:
	cli
	pusha
	call    __timer_irq_handler
	popa
	sti
	iret
.end:
#endasm
}
