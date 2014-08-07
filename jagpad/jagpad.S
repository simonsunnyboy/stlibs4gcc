#
# Jagpad Routine
# reading Jagpad A & B
# from some code found on the web
#
# (c) 2007 by Simon Sunnyboy / Paradize
#
# Returns :-
# pad0 = c1numpad,c1midbuts,c1firebuts,c1joypad
# pad1 = c2numpad,c2midbuts,c2firebuts,c2joypad
# contain bitwise representation in the form
# 1 4 7 * 3 6 9 # 2 5 8 0 o p c b a r l d u
# where o=option, p=pause, a/b/c=fire, r/l/d/u=directions. and rest are the phone pad.
#

.globl _Jagpad_Read
.globl _pad0
.globl _pad1

.text
# jagpad return values after call
_pad0:               DC.L 0
_pad1:               DC.L 0

# local variables
c1numpad:           DC.L 1
c2numpad:           DC.L 1


_Jagpad_Read:       movem.l D0-A2,-(SP)
                    clr.l   D0
                    clr.l   D1
                    clr.l   D2
                    clr.l   D3
                    clr.l   D4
                    clr.l   D5
                    clr.l   D6
                    clr.l   D7
                    movea.l #0,A0
                    lea     c1numpad(PC),A1
                    lea     c2numpad(PC),A2
                    move.l  #0,(A1)
                    move.l  #0,(A2)

# read row 1

                    move.w  #0xFFEE,D0
                    bsr     read_controller

                    move.w  D1,D0
                    andi.w  #1,D0
                    move.b  D0,D3

                    move.w  D1,D0
                    andi.w  #2,D0
                    lsr.w   #1,D0
                    move.b  D0,D4

                    move.w  D1,D0
                    andi.w  #4,D0
                    lsr.w   #2,D0
                    move.b  D0,D6

                    move.w  D1,D0
                    andi.w  #8,D0
                    lsr.w   #3,D0
                    move.b  D0,D7

                    move.w  D2,D0
                    andi.w  #0x0F00,D0
                    lsr.w   #8,D0
                    move.b  D0,D5

                    move.w  D2,D0
                    andi.w  #0xF000,D0
                    lsr.w   #8,D0
                    lsr.w   #4,D0
                    movea.l D0,A0

# read row 2

                    move.w  #0xFFDD,D0
                    bsr     read_controller

                    move.w  D1,D0
                    andi.w  #2,D0
                    or.b    D0,D4

                    move.w  D1,D0
                    andi.w  #8,D0
                    lsr.w   #2,D0
                    or.b    D0,D7

                    move.w  D2,D0
                    andi.w  #0x0F00,D0
                    lsr.w   #8,D0
                    move.w  D0,(A1)

                    move.w  D2,D0
                    andi.w  #0xF000,D0
                    lsr.w   #8,D0
                    lsr.w   #4,D0
                    move.w  D0,(A2)

# read row 3

                    move.w  #0xFFBB,D0
                    bsr     read_controller

                    move.w  D1,D0
                    andi.w  #2,D0
                    lsl.w   #1,D0
                    or.b    D0,D4

                    move.w  D1,D0
                    andi.w  #8,D0
                    lsr.w   #1,D0
                    or.b    D0,D7

                    move.w  D2,D0
                    andi.w  #0x0F00,D0
                    lsr.w   #4,D0
                    or.l    D0,(A1)

                    move.w  D2,D0
                    andi.w  #0xF000,D0
                    lsr.w   #8,D0
                    or.l    D0,(A2)

# read row 4

                    move.w  #0xFF77,D0
                    bsr     read_controller

                    move.w  D1,D0
                    andi.w  #2,D0
                    or.b    D0,D3

                    move.w  D1,D0
                    andi.w  #8,D0
                    lsr.w   #2,D0
                    or.b    D0,D6

                    move.w  D2,D0
                    andi.w  #0x0F00,D0
                    or.l    D0,(A1)

                    move.w  D2,D0
                    andi.w  #0xF000,D0
                    lsr.w   #4,D0
                    or.l    D0,(A2)

                    lsl.l   #7,D3
                    lsl.l   #4,D4
                    or.l    D4,D3
                    or.l    D5,D3

                    lsl.l   #7,D6
                    lsl.l   #4,D7
                    or.l    D7,D6
                    move.l  A0,D2
                    or.l    D2,D6

                    move.l  (A1),D2         ; d2 = c1numpad
                    lsl.l   #5,D2
                    move.l  (A2),D5         ; d5 = c2numpad
                    lsl.l   #5,D5

                    or.l    D2,D3
                    or.l    D5,D6

                    move.l  D3,D4
                    andi.l  #0b1111000000000000000000000,D4
                    lsr.l   #4,D4
                    andi.l  #0b11111111111111111,D3
                    or.l    D4,D3

                    move.l  D6,D4
                    andi.l  #0b1111000000000000000000000,D4
                    lsr.l   #4,D4
                    andi.l  #0b11111111111111111,D6
                    or.l    D4,D6

                    lea     _pad0(PC),A0
                    move.l  D3,(A0)
                    move.l  D6,4(A0)
                    movem.l (SP)+,D0-A2
                    rts

read_controller:
                    move.w  D0,0xFF9202
                    move.w  0xFF9200,D1
                    move.w  0xFF9202,D2

                    andi.w  #0x0F,D1
                    andi.w  #0xFF00,D2

                    not.w   D1
                    not.w   D2

                    rts
.end

