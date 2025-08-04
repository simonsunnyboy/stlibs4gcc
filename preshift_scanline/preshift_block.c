/**
 * Atari ST ST-Low Scanline preshift
 * Preshifting a complete row of 320pixels to the right in ST-LOW
 * (c) 2025 by Matthias Arndt <marndt@final-memory.org>
 *
 * The MIT License applies. See LICENSE for details.
 * 
 * @file preshift_block.c
 * @brief implementation of blockwise preshift for convenience
 * 
 */

#include <stdint.h>
#include "preshift.h"

/**
 * @brief      shift a given number of scanlines one pixel to the right
 * @details    Uses @ref Preshift4PlaneScanline
 * @param[in]  src points to source ST-LOW screen
 * @param[out] dest points to destination ST-LOW screen
 * @param[in]  scanlines to update
 */
void Preshift4PlaneBlockAny(void *src, void *dest, uint16_t scanlines)
{
    uint8_t * srcbuf = src;
    uint8_t * destbuf = dest;

    while(scanlines > 0)
    {
        Preshift4PlaneScanline(srcbuf, destbuf);
        srcbuf += 160;
        destbuf += 160;

        scanlines--;
    }
}
