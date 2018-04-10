| Multi Atari Boot code.
| If you have done an ST demo, use that boot to run it on these machines:
|
| ST, STe, Mega-ST,TT,Falcon,CT60
|
| More info:
| http://leonard.oxg.free.fr/articles/multi_atari/multi_atari.html		
|
| GNU as/gcc compatible startup code by mfro
| Integration (c) 2014 by Simon Sunnyboy / Paradize
|
		
		
			.equ 	BASEPAGE_SIZE,0x100
			.equ	STACK_SIZE,0x4000
			.equ    MCH,0x5f4d4348
			.equ    CT60,0x43543630
					
			.text
			.globl ___main

start:
			move.l	4(sp),a5				| address to basepage
			move.l	0x0c(a5),d0				| length of text segment
			add.l	0x14(a5),d0				| length of data segment
			add.l	0x1c(a5),d0				| length of bss segment
			add.l	#STACK_SIZE+BASEPAGE_SIZE,d0		| length of stackpointer+basepage
			move.l	a5,d1					| address to basepage
			add.l	d0,d1					| end of program
			and.l	#0xfffffff0,d1			| align stack
			move.l	d1,sp					| new stackspace

			move.l	d0,-(sp)				| mshrink()
			move.l	a5,-(sp)
			clr.w	-(sp)
			move.w	#0x4a,-(sp)
			trap	#1
			lea.l	12(sp),sp
			
			pea       leonard_init | Offset 2
			move.w    #38,-(sp)    | Offset 0
			trap      #14          | Call XBIOS Supexec()
			addq.l    #6,sp        | Correct stack





exit:	
			clr.w -(sp)
			trap #1		
		
___main:
			rts
			
		

leonard_init:

			move.l 0x5a0.w,d0
			beq noCookie
			move.l d0,a0
			.loop: move.l (a0)+,d0
			beq noCookie
			cmp.l #MCH,d0
			beq.s .find
			cmp.l #CT60,d0
			bne.s .skip

| CT60, switch off the cache
			pea (a0)

			lea bCT60(pc),a0
			st (a0)

			clr.w -(a7) | param = 0 ( switch off all caches )
			move.w #5,-(a7) | opcode
			move.w #160,-(a7)
			trap #14
			addq.w #6,a7
			move.l (a7)+,a0
			.skip:
			addq.w #4,a0
			bra.s .loop

.find:		 move.w (a0)+,d7
				beq noCookie | STF
				move.b d7,0x1fe.w

				cmpi.w #1,d7
				bne.s .noSTE
				btst.b #4,1(a0)
				beq.s .noMegaSTE
				clr.b 0xffff8e21.w | 8Mhz MegaSTE

.noMegaSTE:
			bra noCookie

.noSTE:
| here TT or FALCON

| Always switch off the cache on these machines.
			move.b bCT60(pc),d0
			bne.s .noMovec

moveq #0,d0
dc.l 0x4e7b0002 | movec d0,cacr | switch off cache
.noMovec:

cmpi.w #3,d7
bne.s noCookie

| Here FALCON
move.w #0x59,-(a7) |check monitortype (falcon)
trap #14
addq.l #2,a7
lea rgb50(pc),a0
subq.w #1,d0
beq.s .setRegs
subq.w #2,d0
beq.s .setRegs
lea vga50(pc),a0

.setRegs:
move.l (a0)+,0xffff8282.w
move.l (a0)+,0xffff8286.w
move.l (a0)+,0xffff828a.w
move.l (a0)+,0xffff82a2.w
move.l (a0)+,0xffff82a6.w
move.l (a0)+,0xffff82aa.w
move.w (a0)+,0xffff820a.w
move.w (a0)+,0xffff82c0.w
move.w (a0)+,0xffff8266.w
clr.b 0xffff8260.w
move.w (a0)+,0xffff82c2.w
move.w (a0)+,0xffff8210.w

noCookie:

| Set res for all machines exept falcon or ct60
cmpi.b #3,0x1fe.w
beq letsGo

clr.w -(a7) |set stlow (st/tt)
moveq #-1,d0
move.l d0,-(a7)
move.l d0,-(a7)
move.w #5,-(a7)
trap #14
lea 12(a7),a7

cmpi.b #2,0x1fe.w | enough in case of TT
beq.s letsGo

move.w 0x468.w,d0
.vsync: cmp.w 0x468.w,d0
beq.s .vsync

move.b #2,0xffff820a.w
clr.b 0xffff8260.w


letsGo:
			
	jsr	_main
			
	rts	

	vga50: dc.l 0x170011
	dc.l 0x2020E
	dc.l 0xD0012
	dc.l 0x4EB04D1
	dc.l 0x3F00F5
	dc.l 0x41504E7
	dc.w 0x0200
	dc.w 0x186
	dc.w 0x0
	dc.w 0x5
	dc.w 0x50

	rgb50: dc.l 0x300027
	dc.l 0x70229
	dc.l 0x1e002a
	dc.l 0x2710265
	dc.l 0x2f0081
	dc.l 0x211026b
	dc.w 0x0200
	dc.w 0x185
	dc.w 0x0
	dc.w 0x0
	dc.w 0x50

	bCT60: dc.b 0
			.even			
					
		
			.bss
		
_basepage:	ds.l	1
_program_length:
			ds.l	1

			.end
