/************************************************************************/
/* This file contains the BCC compiler helper functions */
/* (C) Copyright Bruce Evans */
/* Support for integer arithmetic
 * __idiv.o __idivu.o __imod.o __imodu.o __imul.o __isl.o __isr.o __isru.o
 */

/*
 * https://github.com/lkundrak/dev86/blob/e62b351/libc/bcc/bcc_int.c
 */

#asm
	.text	! This is common to all.
	.even
#endasm

/************************************************************************/
/* Function idivu */

#asm

! idivu.s
! idiv_u doesn`t preserve dx (returns remainder in it)

	.globl idiv_u

idiv_u:
	xor	dx,dx
	div	bx
	ret
#endasm

/************************************************************************/
/* Function imodu */

#asm

! imodu.s
! imodu doesn`t preserve dx (returns quotient in it)

	.globl imodu

imodu:
	xor	dx,dx
	div	bx
	mov	ax,dx		! instruction queue full so xchg slower
	ret
#endasm
