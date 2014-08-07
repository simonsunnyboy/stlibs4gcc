/* SHOWNEO with GEMDOS calls */
#include <stdint.h>
#include <osbind.h>

uint16_t palette[16];

int main ( void )
{
	long handle;
	void * scr = ( void * ) Logbase();
	handle = Fopen ( "TEST.NEO", 0 );
	/* load palette */
	Fseek ( 4,handle, 0 );
	Fread ( handle, 32, &palette[0] );
	Setpalette ( &palette[0] );
	/* load picture data */
	Fseek ( 128, handle, 0 );
	Fread ( handle, 32000, scr );
	Fclose ( handle );
	Cconin();
	return 0;
}

