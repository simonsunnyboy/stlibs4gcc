#include <stdint.h>
#include <osbind.h>

#include "stsprite.h"

extern uint8_t example_pi1[32034];

#define NR_SPRITES 16
st_sprite_t spr[NR_SPRITES];

int main ( void )
{
	void * logbase = Logbase();
	void * example_pi_data = ( void * ) &example_pi1[34];
	void * example_pi1_palette = ( void * ) &example_pi1[2];
	( void ) Setpalette ( example_pi1_palette );
	uint32_t * src = ( uint32_t * ) example_pi_data;
	uint32_t * dest = ( uint32_t * ) logbase;

	for ( uint16_t nr_longs = 0; nr_longs < 8000; nr_longs++ )
	{
		*dest++ = *src++;
	}

	for ( uint16_t idx = 0; idx < NR_SPRITES; idx ++ )
	{
		spr[idx].height = 16;
		spr[idx].width = 1;    /* 16 pixels */
		spr[idx].active = 1;
		spr[idx].maskptr = ( void * ) &example_pi1[34 + 8];
		spr[idx].spriteptr = ( void * ) &example_pi1[34];
		spr[idx].x = 19;
		spr[idx].y = 19 + idx * 10;
	}

	STSprite_SetLogbase ( logbase );
	STSprite_SetBlitterMode ( STSPRITE_USE_CPU );

	for ( uint16_t frames = 0; frames < 200; frames ++ )
	{
		Vsync();
		STSprite_DrawCPU ( &spr[0] );
		/*STSprite_HandleDrawing(&spr[0], NR_SPRITES); */
	}

	Cconin();
	return 0;
}

