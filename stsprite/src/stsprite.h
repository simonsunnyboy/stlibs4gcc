
#ifndef STSPRITE_H
    #define STSPRITE_H

    #include <stdint.h>

    /**
     * @brief
     */
    typedef struct
    {
        uint16_t active;            /**< !=0 means: draw sprite */
        uint16_t x;                 /**< x coordinate */
        uint16_t y;                 /**< y coordinate */
        uint16_t width;             /**< width of sprite in 16pixel steps */
        uint16_t height;            /**< height of sprite in scanlines */
        void *maskptr;              /**< pointer to sprite mask */
        void *spriteptr;            /**< pointer to sprite data */
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
    void STSprite_HandleDrawing(st_sprite_t * spr_list, uint16_t nr_of_sprites_in_list);

    /**
     * @brief set destination screen address in RAM for all drawing routines
     * @param dest_screen_ptr
     */
    void STSprite_SetLogbase(void * dest_screen_ptr);

    /**
     * @brief draw given sprite to screen using CPU routines
     * @param sprdata points to sprite to be drawn (active setting is ignored)
     */
    void STSprite_DrawCPU(st_sprite_t * sprdata);

    /**
     * @brief     draw given sprite to screen using Blitter in SHARED mode
     * @attention Availability of Blitter is not checked!
     * @param     sprdata points to sprite to be drawn (active setting is ignored)
     */
    void STSprite_DrawBlitter(st_sprite_t * sprdata);

    /**
     * @brief     draw given sprite to screen using Blitter in HOG mode
     * @attention Availability of Blitter is not checked!
     * @param     sprdata points to sprite to be drawn (active setting is ignored)
     */
    void STSprite_DrawBlitterHog(st_sprite_t * sprdata);

    /**
     * @brief configure sprite drawing routine used by STSprite_HandleDrawing
     * @param stsprite_blitter_mode according to STSPRITE_USE_... enums
     */
    void STSprite_SetBlitterMode(uint16_t stsprite_blitter_mode);

#endif
