.text
.globl _short_poke

_short_poke:
	link a6,#0             | do not change a6 until unlk to avoid crashes
	move.l a0,-(sp)
	
	move.l 10(a6),a0       | fetch pointer
	move.w 8(a6),(a0)      | use long as pointer
	
	move.l (sp)+,a0
	unlk a6
	rts
.end
	
