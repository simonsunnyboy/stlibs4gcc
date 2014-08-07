/**
 * @file      jagpad.h
 * @brief     API for reading Atarai STE and Falcon 030 Pads 
 * @author    Simon Sunnyboy / Paradize
 * @copyright The MIT License applies.
 */

#ifndef JAGPAD_H
	#define JAGPAD_H
	#include <stdint.h>

	/* Button bitmap: 1 4 7 * 3 6 9 # 2 5 8 0 o p c b a r l d u */

	#define JAGPAD_UP   		0x00000001
    #define JAGPAD_DOWN 		0x00000002
	#define JAGPAD_LEFT		 	0x00000004
	#define JAGPAD_RIGHT 		0x00000008
	#define JAGPAD_BUT_A   		0x00000010
	#define JAGPAD_BUT_B   		0x00000020
	#define JAGPAD_BUT_C    	0x00000040
	#define JAGPAD_BUT_PAUSE    0x00000080
	#define JAGPAD_BUT_OPTION   0x00000100
	#define JAGPAD_BUT_0        0x00000200
	#define JAGPAD_BUT_8        0x00000400
	#define JAGPAD_BUT_5        0x00000800
	#define JAGPAD_BUT_2        0x00001000
	#define JAGPAD_BUT_HASH     0x00002000
	#define JAGPAD_BUT_9        0x00004000
	#define JAGPAD_BUT_6        0x00008000
	#define JAGPAD_BUT_3        0x00010000
	#define JAGPAD_BUT_STAR     0x00020000
	#define JAGPAD_BUT_7        0x00040000
	#define JAGPAD_BUT_4        0x00080000
	#define JAGPAD_BUT_1        0x00100000

	#define JAGPAD_FIRE         (JAGPAD_BUT_A|JAGPAD_BUT_B|JAGPAD_BUT_C)

	/**
	 * @brief    read jagpad A and B state into the global variables
	 * @details  This routine is to be called cyclic, e.q. from a VBL interrupt.
	 */
	extern void Jagpad_Read(void);

	/**
     * @brief  Jagpad A state 
     */
	extern uint32_t pad0;

	/**
     * @brief  Jagpad A state 
     */
	extern uint32_t pad1;
#endif

