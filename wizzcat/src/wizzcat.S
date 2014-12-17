    #
    # GCC interface for Wizzcat 12kHz Protracker replay (STE only)
    # based on the Wizzcat interface by GT Turbo / Cerebral Vortex for GFABASIC
    #
    # GCC interface (c) 2014 by Simon Sunnyboy / Paradize (based upon AHCC interface)
    #

    .globl _Wizzcat_Init
    .globl _Wizzcat_Play
    .globl _Wizzcat_Stop

    .equ Wizz, 0x57697A7A

    .text

_Wizzcat_Init:
    movem.l d0-a6,-(sp)
    cmpi.l #Wizz,wizzcat_initmark
    beq end_init
    # relocate Wizzcat routine:
    movem.l regs,d0-a6

    lea wizzcat_rout,a0
    bsr reloc
    # mark routine as ready
    move.l #Wizz,wizzcat_initmark
    clr.w wizzcat_playing
end_init:
    movem.l (sp)+,d0-a6
    rts

tunestart: dc.l 0
tuneend:   dc.l 0

_Wizzcat_Play:
    move.l 4(sp),tunestart
    move.l 8(sp),tuneend

    movem.l d0-a6,-(sp)
    cmpi.l #Wizz,wizzcat_initmark
    bne assert_wizzcat_failed
    cmpi.w #0,wizzcat_playing
    bne assert_wizzcat_failed
    move.w #-1,wizzcat_playing

    movem.l regs,d0-d7
    move.l  tunestart,a0
    move.l  tuneend,a1
    movem.l regs,a2-a6

    bsr wizzcat_rout

    movem.l (sp)+,d0-a6
    rts

_Wizzcat_Stop:
    movem.l d0-a6,-(sp)
    cmpi.l #Wizz,wizzcat_initmark
    bne assert_wizzcat_failed
    cmpi.w #-1,wizzcat_playing
    bne assert_wizzcat_failed
    clr.w wizzcat_playing

    movem.l regs,d0-a6

    bsr wizzcat_rout+2

assert_wizzcat_failed:
    movem.l (sp)+,d0-a6
    rts
    .even
reloc:
    .incbin "reloc.bin"
    .even
wizzcat_rout:
    .incbin "wizzcat.bin"
    .even
    dc.l 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    dc.l 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    dc.l 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    dc.l 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    .even
    .DATA
regs:
    dc.l 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    .even
wizzcat_initmark:
    dc.l 0
wizzcat_playing:
    dc.w 0
    .even

    .END
