/**
 * Atari ST ST-Low Scanline preshift
 * Preshifting a complete row of 320pixels to the right in ST-LOW
 * (c) 2025 by Matthias Arndt <marndt@final-memory.org>
 *
 * The MIT License applies. See LICENSE for details.
 * 
 * @file main.c
 * @brief Demo program to shift a row of text 16 times and print the shifted. parts. 
 * 
 */

#include <stdint.h>
#include <osbind.h>

#include "preshift.h"

int main(void)
{
	(*(uint16_t *)0xFFFF8240) = 0x13; // blue
	(*(uint16_t *)0xFFFF825E) = 0xFFF; // white

	(void)Cconws("\033HHello...we preshift this text!        M\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\r++Hello...we preshift this text!\n");

	uint8_t * src = (uint8_t*)Physbase();
	uint8_t * dest = &src[8*160];

	for(uint16_t shifts=0; shifts < 15; shifts++)
	{
		Preshift4PlaneBlock8(src, dest);
		src += 160*8;
		dest += 160*8;
	}

	Cconin();

	return 0;
}

