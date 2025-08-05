| Startup code to parse the commandline given in the basepage
| The basepage pointer is passed to a function parse_basepage()
| This function in turn calls the main function of the user.
|
| (c) 2025 by Matthias Arndt <marndt@final-memory.org>
|
| The MIT License applies. See the file LICENSE for details.
|
		
		
			.equ 	BASEPAGE_SIZE,0x100
			.equ	STACK_SIZE,0x4000
					
			.text
			.globl ___main
			.extern _parse_basepage         | int parse_basepage(void *basepage)

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

			move.l  a5,-(sp)                | save address on basepage on the stack for future invocation

			move.l	d0,-(sp)				| mshrink()
			move.l	a5,-(sp)
			clr.w	-(sp)
			move.w	#0x4a,-(sp)
			trap	#1
			lea.l	12(sp),sp

			jsr 	_parse_basepage         | this function invokes main()
			add.l   #4,sp                   | correction of stack, return of main() in d0


			move.w  d0,-(sp)                | convert return code to int16_t
			move.w  #0x4c,-(sp)             | Pterm()
			trap    #1             
			addq.l  #4,sp                   | Correct stack (maybe unnecessary?)
		
___main:
			rts
			.even			
			.end
