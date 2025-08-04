/**
 * Atari ST ST-Low Scanline preshift
 * Preshifting a complete row of 320pixels to the right in ST-LOW
 * (c) 2025 by Matthias Arndt <marndt@final-memory.org>
 *
 * The MIT License applies. See LICENSE for details.
 * 
 * @file preshift.h
 * @brief API header for ST-LOW scanline preshift
 * 
 */

#ifndef PRESHIFT_SCANLINE_H
	#define PRESHIFT_SCANLINE_H
	
	/**
	 * @brief      shifts a single ST-LOW scanline of 160 bytes one pixel to the right
	 * @details    A pixel in color 0 is added on the left most column
	 * @param[in]  src points to source ST-LOW screen
	 * @param[out] dest points to destination ST-LOW screen
	 */
	void Preshift4PlaneScanline(void *src, void *dest);

	/**
	 * @brief shift a given number of scanlines one pixel to the right
	 * @details Uses @ref Preshift4PlaneScanline
	 * @param[in]  src points to source ST-LOW screen
	 * @param[out] dest points to destination ST-LOW screen
	 * @param[in] scanlines to update
	 */
	void Preshift4PlaneBlockAny(void *src, void *dest, uint16_t scanlines);

	/**
	 * @brief shifts a block of 8 ST-LOW scanlines of 160 bytes one pixel to the right
	 * @details Uses @ref Preshift4PlaneScanline underneath
	 * @param[in]  src points to source ST-LOW screen
	 * @param[out] dest points to destination ST-LOW screen
	 */
	#define Preshift4PlaneBlock8(s,d) Preshift4PlaneBlockAny((s),(d), 8u);

	/**
	 * @brief shifts a block of 16 ST-LOW scanlines of 160 bytes one pixel to the right
	 * @details Uses @ref Preshift4PlaneScanline underneath
	 * @param[in]  src points to source ST-LOW screen
	 * @param[out] dest points to destination ST-LOW screen
	 */
	#define Preshift4PlaneBlock16(s,d) Preshift4PlaneBlockAny((s),(d), 16u);

	/**
	 * @brief shifts a block of 32 ST-LOW scanlines of 160 bytes one pixel to the right
	 * @details Uses @ref Preshift4PlaneScanline underneath
	 * @param[in]  src points to source ST-LOW screen
	 * @param[out] dest points to destination ST-LOW screen
	 */
	#define Preshift4PlaneBlock32(s,d) Preshift4PlaneBlockAny((s),(d), 32u);	
#endif
