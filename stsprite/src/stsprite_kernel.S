|
| STFM Sprite kernel for GFABASIC
| (c) 2008/2009/2018 by Simon Sunnyboy / Paradize
| http://paradize.atari.org/
|
| Special thanks and acknowledgements:
|  -- ggn / Paradize (for writing the Blitter sprite routine for HOG mode
|                     and for finding the bugfix of the halftone mode)
|  -- Paranoid / Paradox  (for helping me making SHARED MODE work)
|  -- PeP (for finding a serious bug which did lead to strange effects)
|  -- LP  (for helping debugging the Halftone mode bug)
|
| Version 0.5a  24.03.2008 (different interface)
| Version 0.9   25.03.2008
| Version 0.99  06.06.2008 (beta version with support for Blitter)
| Version 1.00  25.02.2009 (first release version - Halftone mode bugfix)
|               10.04.2018 (gcc port)
| Version 1.01  16.04.2023 (bugfix C stack access for STSprite_Draw.... functions)
|
| Draws up to 16 sprites with different sizes on screen
|
| INPUTs:
|   spritelist - points to a buffer containing 16 sprite structures
|   logbase    - points to the screen where the next call of the
|                routine should draw the sprites to
|   blitter    - a flag to indicate whether the Blitter shall draw sprites
|
| data structure per sprite
| struct {
|                   WORD active;            /* !=0 means: draw sprite */
|                   WORD x;                 /* x coordinate */
|                   WORD y;                 /* y coordinate */
|                   WORD width;             /* width of sprite in 16pixel steps */
|                   WORD height;            /* height of sprite in scanlines */
|                   LONG *maskptr;          /* pointer to sprite mask */
|                   LONG *spriteptr;        /* pointer to sprite data */
| } sprite_record;
|
| The routine uses screen format so you can directly take sprites from
| a DEGAS picture.
|
| NO CLIPPING OF SPRITES!
|
| -- offsets into structure for sprite record --
.equ active,0
.equ x,2
.equ y,4
.equ width,6
.equ height,8
.equ maskptr,10
.equ sprptr,14
| -- the number of sprites to process --
.equ numbersprites,16

| -- Blitter equates
.equ halftone,0
.equ src_xinc,32
.equ src_yinc,34
.equ src_addr,36
.equ endmask1,40
.equ endmask2,42
.equ endmask3,44
.equ dst_xinc,46
.equ dst_yinc,48
.equ dst_addr,50
.equ x_count ,54
.equ y_count ,56
.equ hop     ,58
.equ op      ,59
.equ line_num,60
.equ skew    ,61

.equ blitter,0xFFFF8A00

.globl _STSprite_HandleDrawing
.globl _STSprite_DrawCPU
.globl _STSprite_DrawBlitter
.globl _STSprite_DrawBlitterHog
.globl _STSprite_SetBlitterMode
.globl _STSprite_SetLogbase

.text

_STSprite_HandleDrawing:
	move.l 4(sp),spritelist
	move.w 8(sp),nr_sprites
	bra spritekernel

_STSprite_DrawCPU:
	move.l a6,-(sp)	
	movea.l 8(sp),a6	    | get pointer from stack to register and
	movem.l D2-D7/A2-A5,-(sp)
	move.w  x(A6),D0        | load sprite parameters
	move.w  y(A6),D1
	move.w  width(A6),D6
	move.w  height(A6),D7
	movea.l maskptr(A6),A0
	movea.l sprptr(A6),A1
	move.l logbase, A2

	bsr draw_4bplsprite
	movem.l (SP)+,D2-D7/A2-A5
	move.l (SP)+,a6
	rts

_STSprite_DrawBlitter:
	move.l a6,-(sp)	
	movea.l 8(sp),a6	    | get pointer from stack to register and
	movem.l D2-D7/A2-A5,-(sp)

	move.w  x(A6),D0        | load sprite parameters
	move.w  y(A6),D1
	move.w  width(A6),D6
	move.w  height(A6),D7
	movea.l maskptr(A6),A0
	movea.l sprptr(A6),A1
	move.l logbase, A2

	bsr draw_4bplsprite_blitter
	movem.l (SP)+,D2-D7/A2-A5
	move.l (SP)+,a6
	rts

_STSprite_DrawBlitterHog:
	move.l a6,-(sp)	
	movea.l 8(sp),a6	    | get pointer from stack to register and
	movem.l D2-D7/A2-A5,-(sp)

	move.w  x(A6),D0        | load sprite parameters
	move.w  y(A6),D1
	move.w  width(A6),D6
	move.w  height(A6),D7
	movea.l maskptr(A6),A0
	movea.l sprptr(A6),A1
	move.l logbase, A2

	bsr draw_4bplsprite_hog
	movem.l (SP)+,D2-D7/A2-A5
	move.l (SP)+,a6
	rts

_STSprite_SetBlitterMode:
	move.w 4(sp),use_blitter
	rts

_STSprite_SetLogbase:
	move.l 4(sp),logbase
	rts


| jump table
entry:              bra     spritekernel    | +0 draw sprites
					bra     draw_4bplsprite | +4 draw single sprite with CPU
					bra     draw_4bplsprite_blitter | +8 draw sprite with Blitter

| data interface for GFABASIC:
spritelist:         DC.L 0      | +12 pointer to sprite records
logbase:            DC.L 0      | +16 pointer to screen
use_blitter:        DC.W 0      | +20 flag to indicate: draw sprite with Blitter
nr_sprites:         DC.W 16     | +22 number of sprites to draw
					DC.W 0
					DC.L 0,0,0,0,0,0,0 | space for future additions
					.even
					.asciz "STFM Sprite Kernel by Paradize v1.01 (gcc version)"
					.even
spritekernel:
                    movem.l D0-A6,-(SP)
| 'Choose Sprite routine'
                    move.w  use_blitter(PC),D0
					tst.w   D0              | use Blitter?
					bne.s   use_blitterrout | !=0 then yes
| no Blitter => use CPU sprite blit
					lea     draw_4bplsprite(PC),A6 | draw routine to use
					bra.s   continue_kernel
| Blitter activated => use Blitter sprite blit
use_blitterrout:
					cmpi.w  #1,D0           | Blitter == 1
					bne     use_shared_mode | if == 1 then use hogmode
                    lea     draw_4bplsprite_hog(PC),A6
                    bra.s   continue_kernel
use_shared_mode:
                    lea     draw_4bplsprite_blitter(PC),A6
continue_kernel:

					move.w  nr_sprites(PC),D3 | loop counter
					subq.w #1,D3

					movea.l logbase(PC),A2    | load logbase to use
					movea.l spritelist(PC),A5 | start of sprite records
| --- main loop sprite kernel ---
for_i_in_sprites:
                    tst.w   active(A5)
					beq.s   next_sprite     | if not active skip sprite
| 'copy sprite parameters'
					move.w  x(A5),D0        | load sprite parameters
                    move.w  y(A5),D1
                    move.w  width(A5),D6
                    move.w  height(A5),D7
                    movea.l maskptr(A5),A0
                    movea.l sprptr(A5),A1

					jsr     (A6)            | draw with selected routine

next_sprite:
					lea     18(A5),A5       | next sprite in list
                    dbra    D3,for_i_in_sprites
                    movem.l (SP)+,D0-A6
                    rts

| 'CPU Sprite w/o preshift'
|
| Universal Sprite routine for STFM and STE
| (c) 2008 by Simon Sunnyboy / Paradize
| http://paradize.atari.org/
|
| This source is based upon a snippet I found ages ago on the net.
| It was buggy and didn't work as expected. After understanding what's
| going on, I could fix pointer offsets and parameter calculation
| so that it is now working now.
| Credits to whoever wrote the first sketch of this code :)
|
| Draws a 4 bitplane sprite at any position on screen. This routine is for
| 320*200 ST-LOW.
|
| Sprite width : any multiple of 16pixel (the more the slower)
| Sprite height: any amount of scanlines
|
| Coordinates and sprites will not be clipped so be careful with borders!
| No preshift necessary (slower but saves memory)
| No background saving and restoring
|
| INPUT: d0.w: x position of sprite on screen (left side)
|        d1.w: y position of sprite on screen (top side)
|        d6.w: number of 16pixel blocks to do
|        d7.w: number of Y lines to to
|        a0: address of maskdata (screen format)
|        a1: address of bitmapdata (screen format)
|        a2: screen start address
|
draw_4bplsprite:
                    movem.l D0-A6,-(SP)

                    clr.l   D2
					move.w  D0,D2           | shifts = x AND 16 = x MOD 16
					andi.w  #0x0F,D2         | number of shifts

					andi.w  #0xFFF0,D0       | xoffset = x DIV 8
                    lsr.w   #1,D0
					adda.w  D0,A2           | screenstart + xoffset
					mulu    #160,D1         | y=y*160
					adda.l  D1,A2           | screenstart + yoffset

					move.w  #160,D4         | length of a scanline
					move.w  D6,D3           | get number of 16pixel rows
					lsl.w   #3,D3           | rows=rows*8
					sub.w   D3,D4           | skip = 160 - rows*8 bytes

					subq.w  #1,D7           | adjust loop counter
					subq.w  #1,D6           | adjust loop counter
					move.w  D6,D5           | backup xloop counter in d5.w.

yloop:

xloop:              moveq   #-1,D0         | prepare for maskshifting.
					move.w  (A0)+,D0        | get 16pixel maskdata in d0.w.
					addq.l  #6,A0           | skip 3 planes
					ror.l   D2,D0           | shift it!
					and.w   D0,0(A2)        | mask bitplane 0.
					and.w   D0,2(A2)        | mask bitplane 1.
					and.w   D0,4(A2)        | mask bitplane 2.
					and.w   D0,6(A2)        | mask bitplane 3.
					swap    D0              | get mask overspill in loword.
					and.w   D0,8(A2)        | mask overspill bitplane 0.
					and.w   D0,10(A2)       | mask overspill bitplane 1.
					and.w   D0,12(A2)       | mask overspill bitplane 2.
					and.w   D0,14(A2)       | mask overspill bitplane 3.
					.rept 4
					moveq   #0,D0           | prepare for bitmapshifting.
					move.w  (A1)+,D0        | get bitplane word in d0.w.
					ror.l   D2,D0           | shift it.
					or.w    D0,(A2)+        | paint bitplane into hole
					swap    D0              | get overspill in loword.
					or.w    D0,6(A2)        | paint overspill bitplane
					.endr
					dbra    D6,xloop        | loop until all blocks done.

					adda.l  D4,A0           | next scanline mask
					adda.l  D4,A1           | next scanline sprite data
					adda.l  D4,A2           | goto next screenline.
					move.w  D5,D6           | restore xloop counter.
					dbra    D7,yloop        | loop until all lines done.

                    movem.l (SP)+,D0-A6
                    rts

| 'Blitter sprite HOT RESTART'
| Sprite routine for Blitter in SHARED MODE
| designed and coded by ggn / Paradize
|
| same interfacing as CPU routine

draw_4bplsprite_blitter:
                    movem.l D0-A6,-(SP)
                    lea     blitter.w,A5

|
| Step 1: blit the mask
|

                    addq.w  #1,D6
                    move.w  D6,x_count(A5)
                    move.w  #8,src_xinc(A5)
                    move.w  #8,dst_xinc(A5)
                    move.w  #160,D2
                    subq.w  #1,D6
                    lsl.w   #3,D6
                    sub.w   D6,D2

                    move.w  D2,src_yinc(A5)
                    move.w  D2,dst_yinc(A5)
					mulu    #160,D1         |eek! mulu!!!
                    move.w  D0,D2
                    lsr.w   #1,D2
					andi.w  #~0b111,D2       |(x/16)*8
					add.w   D2,D1           |dest offset
					lea     0(A2,D1.w),A2   |a2=dest address
					moveq   #-1,D2
                    move.w  D2,endmask2(A5)
                    and.b   #15,D0
                    lsr.w   D0,D2
                    move.w  D2,endmask1(A5)
                    not.w   D2
                    move.w  D2,endmask3(A5)
					move.b  #2,hop(A5)      | Halftone mode
					move.b  #1,op(A5)       |S AND D
                    move.b  D0,skew(A5)

                    moveq   #3,D2
blitmasks_shared:   btst    #7,0xFFFF8A3C    | wait for Blitter to have finished
                    nop
                    bne.s   blitmasks_shared


                    move.l  A0,src_addr(A5)
                    move.l  A2,dst_addr(A5)
                    move.w  D7,y_count(A5)
					move.b  #128,line_num(A5) | hot restart
poll_blitter1:      bset    #7,0xFFFF8A3C      | test and set Blitter busy bit
					nop                       | idle a bit - to leave time for IRQs
                    bne.s   poll_blitter1

                    addq.w  #2,A0
                    addq.w  #2,A2
                    dbra    D2,blitmasks_shared

|
| Step 2: blit the sprite
|
wait_blitter:       btst    #7,0xFFFF8A3C    | wait for Blitter to finish
                    nop
                    bne.s   wait_blitter


					move.b  #7,op(A5)       |S OR D
                    subq.w  #8,A2
                    moveq   #3,D2
blitsprite_shared:  btst    #7,0xFFFF8A3C
                    nop
                    bne.s   blitsprite_shared


                    move.l  A1,src_addr(A5)
                    move.l  A2,dst_addr(A5)
                    move.w  D7,y_count(A5)
                    move.b  #128,line_num(A5)
poll_blitter2:      bset    #7,0xFFFF8A3C    | test and set Blitter busy bit
					nop                     | idle a bit - to leave time for IRQs
                    bne.s   poll_blitter2


                    addq.w  #2,A1
                    addq.w  #2,A2
                    dbra    D2,blitsprite
                    movem.l (SP)+,D0-A6
                    rts

| 'Blitter sprite HOGMODE'
| same but with using HOGMODE

draw_4bplsprite_hog:
                    movem.l D0-A6,-(SP)
                    lea     blitter.w,A5

|
| Step 1: blit the mask
|

                    addq.w  #1,D6
                    move.w  D6,x_count(A5)
                    move.w  #8,src_xinc(A5)
                    move.w  #8,dst_xinc(A5)
                    move.w  #160,D2
                    subq.w  #1,D6
                    lsl.w   #3,D6
                    sub.w   D6,D2

                    move.w  D2,src_yinc(A5)
                    move.w  D2,dst_yinc(A5)
					mulu    #160,D1         |eek! mulu!!!
                    move.w  D0,D2
                    lsr.w   #1,D2
					andi.w  #~0b111,D2       |(x/16)*8
					add.w   D2,D1           |dest offset
					lea     0(A2,D1.w),A2   |a2=dest address
					moveq   #-1,D2
                    move.w  D2,endmask2(A5)
                    and.b   #15,D0
                    lsr.w   D0,D2
                    move.w  D2,endmask1(A5)
                    not.w   D2
                    move.w  D2,endmask3(A5)
					move.b  #2,hop(A5)      |Halftone mode
					move.b  #1,op(A5)       |S AND D
                    move.b  D0,skew(A5)

                    moveq   #3,D2
blitmasks:          move.l  A0,src_addr(A5)
                    move.l  A2,dst_addr(A5)
                    move.w  D7,y_count(A5)
					move.b  #192,line_num(A5) | Hogmode
                    addq.w  #2,A0
                    addq.w  #2,A2
                    dbra    D2,blitmasks

|
| Step 2: blit the sprite
|

					move.b  #7,op(A5)       |S OR D
                    subq.w  #8,A2
                    moveq   #3,D2
blitsprite:         move.l  A1,src_addr(A5)
                    move.l  A2,dst_addr(A5)
                    move.w  D7,y_count(A5)
					move.b  #192,line_num(A5) | Hog Mode
                    addq.w  #2,A1
                    addq.w  #2,A2
                    dbra    D2,blitsprite

                    movem.l (SP)+,D0-A6
                    rts

.end
