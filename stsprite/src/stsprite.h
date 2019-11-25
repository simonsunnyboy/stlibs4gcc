/**
 * @file stsprite.h
 *
 * STFM Sprite kernel for GCC
 * @author (c) 2008/2009/2018/2019 by Simon Sunnyboy / Paradize
 * @copyright http://paradize.atari.org/
 *
 * Special thanks and acknowledgements:
 *  -- ggn / Paradize (for writing the Blitter sprite routine for HOG mode
 *                     and for finding the bugfix of the halftone mode)
 *  -- Paranoid / Paradox  (for helping me making SHARED MODE work)
 *  -- PeP (for finding a serious bug which did lead to strange effects)
 *  -- LP  (for helping debugging the Halftone mode bug)
 *
 * Version 0.5a  24.03.2008 (different interface)
 * Version 0.9   25.03.2008
 * Version 0.99  06.06.2008 (beta version with support for Blitter)
 * Version 1.00  25.02.2009 (first release version - Halftone mode bugfix)
 *               10.04.2018 (gcc port)
 *
 * Draws up to 16 sprites with different sizes on screen
 *
 * The routine uses screen format so you can directly take sprites from
 * a DEGAS picture.
 *
 * NO CLIPPING OF SPRITES!
 */

/** @addtogroup STSprite
 *  @{
 */

#ifndef STSPRITE_H
#define STSPRITE_H

#include <stdint.h>

/**
 * @brief sprite handling object
 */
typedef struct
{
	uint16_t active;            /**< flag !=0 means: draw sprite */
	uint16_t x;                 /**< x coordinate */
	uint16_t y;                 /**< y coordinate */
	uint16_t width;             /**< width of sprite in 16pixel steps, e.q. 1 <=> 16 pixels, 2 <=> 32 pixels */
	uint16_t height;            /**< height of sprite in scanlines */
	void *maskptr;              /**< pointer to sprite mask (data in ST-LOW screen format) */
	void *spriteptr;            /**< pointer to sprite data (data in ST-LOW screen format) */
} st_sprite_t;

enum stsprite_blitter_mode
{
	STSPRITE_USE_CPU = 0,       /**< ... */
	STSPRITE_USE_HOGMODE = 1,   /**< ... */
	STSPRITE_USE_SHAREDMODE = 2 /**< ... */
};

/**
 * @brief   draws given list of sprites on screen
 * @details The destination screen address must have been set before with STSprite_SetLogbase
 * @param   spr_list points to sprite records
 * @param   nr_of_sprites_in_list contains number of available sprite records in list
 */
void STSprite_HandleDrawing ( st_sprite_t * spr_list, uint16_t nr_of_sprites_in_list );

/**
 * @brief set destination screen address in RAM for all drawing routines
 * @param dest_screen_ptr
 */
void STSprite_SetLogbase ( void * dest_screen_ptr );

/**
 * @brief draw given sprite to screen using CPU routines
 * @param sprdata points to sprite to be drawn (active setting is ignored)
 */
void STSprite_DrawCPU ( st_sprite_t * sprdata );

/**
 * @brief     draw given sprite to screen using Blitter in SHARED mode
 * @attention Availability of Blitter is not checked!
 * @param     sprdata points to sprite to be drawn (active setting is ignored)
 */
void STSprite_DrawBlitter ( st_sprite_t * sprdata );

/**
 * @brief     draw given sprite to screen using Blitter in HOG mode
 * @attention Availability of Blitter is not checked!
 * @param     sprdata points to sprite to be drawn (active setting is ignored)
 */
void STSprite_DrawBlitterHog ( st_sprite_t * sprdata );

/**
 * @brief configure sprite drawing routine used by STSprite_HandleDrawing
 * @param stsprite_blitter_mode according to STSPRITE_USE_... enums
 */
void STSprite_SetBlitterMode ( uint16_t stsprite_blitter_mode );

#endif

/** @} */
