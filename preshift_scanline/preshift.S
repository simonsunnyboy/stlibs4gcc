|
| Atari ST ST-Low Scanline preshift
| (c) 2025 by Matthias Arndt <marndt@final-memory.org>
|
| The MIT License applies. See LICENSE for details.
|
| Preshifting a complete row of 320pixels to the right in ST-LOW
| (library function)
|

.text

.globl _Preshift4PlaneScanline

_Preshift4PlaneScanline:

move.l 4(sp),a0   | source pointer as first function argument
move.l 8(sp),a1   | destination pointer as second function argument

| bitplane 0
move.w 0(a0),d0
lsr.w #1,d0      | ... this inserts a bit of zero to the left
move.w d0,0(a1)
move.w 8(a0),d0
roxr.w #1,d0
move.w d0,8(a1)
move.w 16(a0),d0
roxr.w #1,d0
move.w d0,16(a1)
move.w 24(a0),d0
roxr.w #1,d0
move.w d0,24(a1)
move.w 32(a0),d0
roxr.w #1,d0
move.w d0,32(a1)
move.w 40(a0),d0
roxr.w #1,d0
move.w d0,40(a1)
move.w 48(a0),d0
roxr.w #1,d0
move.w d0,48(a1)
move.w 56(a0),d0
roxr.w #1,d0
move.w d0,56(a1)
move.w 64(a0),d0
roxr.w #1,d0
move.w d0,64(a1)
move.w 72(a0),d0
roxr.w #1,d0
move.w d0,72(a1)
move.w 80(a0),d0
roxr.w #1,d0
move.w d0,80(a1)
move.w 88(a0),d0
roxr.w #1,d0
move.w d0,88(a1)
move.w 96(a0),d0
roxr.w #1,d0
move.w d0,96(a1)
move.w 104(a0),d0
roxr.w #1,d0
move.w d0,104(a1)
move.w 112(a0),d0
roxr.w #1,d0
move.w d0,112(a1)
move.w 120(a0),d0
roxr.w #1,d0
move.w d0,120(a1)
move.w 128(a0),d0
roxr.w #1,d0
move.w d0,128(a1)
move.w 136(a0),d0
roxr.w #1,d0
move.w d0,136(a1)
move.w 144(a0),d0
roxr.w #1,d0
move.w d0,144(a1)
move.w 152(a0),d0
roxr.w #1,d0
move.w d0,152(a1)
| bitplane 1
move.w 2(a0),d0
lsr.w #1,d0      | ... this inserts a bit of zero to the left
move.w d0,2(a1)
move.w 10(a0),d0
roxr.w #1,d0
move.w d0,10(a1)
move.w 18(a0),d0
roxr.w #1,d0
move.w d0,18(a1)
move.w 26(a0),d0
roxr.w #1,d0
move.w d0,26(a1)
move.w 34(a0),d0
roxr.w #1,d0
move.w d0,34(a1)
move.w 42(a0),d0
roxr.w #1,d0
move.w d0,42(a1)
move.w 50(a0),d0
roxr.w #1,d0
move.w d0,50(a1)
move.w 58(a0),d0
roxr.w #1,d0
move.w d0,58(a1)
move.w 66(a0),d0
roxr.w #1,d0
move.w d0,66(a1)
move.w 74(a0),d0
roxr.w #1,d0
move.w d0,74(a1)
move.w 82(a0),d0
roxr.w #1,d0
move.w d0,82(a1)
move.w 90(a0),d0
roxr.w #1,d0
move.w d0,90(a1)
move.w 98(a0),d0
roxr.w #1,d0
move.w d0,98(a1)
move.w 106(a0),d0
roxr.w #1,d0
move.w d0,106(a1)
move.w 114(a0),d0
roxr.w #1,d0
move.w d0,114(a1)
move.w 122(a0),d0
roxr.w #1,d0
move.w d0,122(a1)
move.w 130(a0),d0
roxr.w #1,d0
move.w d0,130(a1)
move.w 138(a0),d0
roxr.w #1,d0
move.w d0,138(a1)
move.w 146(a0),d0
roxr.w #1,d0
move.w d0,146(a1)
move.w 154(a0),d0
roxr.w #1,d0
move.w d0,154(a1)
| bitplane 2
move.w 4(a0),d0
lsr.w #1,d0      | ... this inserts a bit of zero to the left
move.w d0,4(a1)
move.w 12(a0),d0
roxr.w #1,d0
move.w d0,12(a1)
move.w 20(a0),d0
roxr.w #1,d0
move.w d0,20(a1)
move.w 28(a0),d0
roxr.w #1,d0
move.w d0,28(a1)
move.w 36(a0),d0
roxr.w #1,d0
move.w d0,36(a1)
move.w 44(a0),d0
roxr.w #1,d0
move.w d0,44(a1)
move.w 52(a0),d0
roxr.w #1,d0
move.w d0,52(a1)
move.w 60(a0),d0
roxr.w #1,d0
move.w d0,60(a1)
move.w 68(a0),d0
roxr.w #1,d0
move.w d0,68(a1)
move.w 76(a0),d0
roxr.w #1,d0
move.w d0,76(a1)
move.w 84(a0),d0
roxr.w #1,d0
move.w d0,84(a1)
move.w 92(a0),d0
roxr.w #1,d0
move.w d0,92(a1)
move.w 100(a0),d0
roxr.w #1,d0
move.w d0,100(a1)
move.w 108(a0),d0
roxr.w #1,d0
move.w d0,108(a1)
move.w 116(a0),d0
roxr.w #1,d0
move.w d0,116(a1)
move.w 124(a0),d0
roxr.w #1,d0
move.w d0,124(a1)
move.w 132(a0),d0
roxr.w #1,d0
move.w d0,132(a1)
move.w 140(a0),d0
roxr.w #1,d0
move.w d0,140(a1)
move.w 148(a0),d0
roxr.w #1,d0
move.w d0,148(a1)
move.w 156(a0),d0
roxr.w #1,d0
move.w d0,156(a1)
| bitplane 3
move.w 6(a0),d0
lsr.w #1,d0      | ... this inserts a bit of zero to the left
move.w d0,6(a1)
move.w 14(a0),d0
roxr.w #1,d0
move.w d0,14(a1)
move.w 22(a0),d0
roxr.w #1,d0
move.w d0,22(a1)
move.w 30(a0),d0
roxr.w #1,d0
move.w d0,30(a1)
move.w 38(a0),d0
roxr.w #1,d0
move.w d0,38(a1)
move.w 46(a0),d0
roxr.w #1,d0
move.w d0,46(a1)
move.w 54(a0),d0
roxr.w #1,d0
move.w d0,54(a1)
move.w 62(a0),d0
roxr.w #1,d0
move.w d0,62(a1)
move.w 70(a0),d0
roxr.w #1,d0
move.w d0,70(a1)
move.w 78(a0),d0
roxr.w #1,d0
move.w d0,78(a1)
move.w 86(a0),d0
roxr.w #1,d0
move.w d0,86(a1)
move.w 94(a0),d0
roxr.w #1,d0
move.w d0,94(a1)
move.w 102(a0),d0
roxr.w #1,d0
move.w d0,102(a1)
move.w 110(a0),d0
roxr.w #1,d0
move.w d0,110(a1)
move.w 118(a0),d0
roxr.w #1,d0
move.w d0,118(a1)
move.w 126(a0),d0
roxr.w #1,d0
move.w d0,126(a1)
move.w 134(a0),d0
roxr.w #1,d0
move.w d0,134(a1)
move.w 142(a0),d0
roxr.w #1,d0
move.w d0,142(a1)
move.w 150(a0),d0
roxr.w #1,d0
move.w d0,150(a1)
move.w 158(a0),d0
roxr.w #1,d0
move.w d0,158(a1)
rts
