/* Wizzcat Protracker replay for STE 12kHZ : */
#include <stdint.h>
#include <string.h>
#include <osbind.h>
#include "wizzcat.h"

#define BUFSIZE 20000

int main ( void )
{
	long handle;
	long lof;

	char * tune = NULL;

	(void)Cconws("\033E *** playing a .mod file *** \n\r");

	handle = Fopen ( "ALPHAC1.MOD", 0 );
	/* get length of file */
	lof = Fseek ( 0,handle, 2 );

	tune = (char *)Malloc((lof + BUFSIZE));

    /* load tune into RAM: */
	if((tune != NULL)&&(lof > 0))
    {
        Fseek(0, handle, 0);
        Fread ( handle, lof, tune );

        (void)Cconws("(loaded)\r\n");
    }


	Fclose ( handle );

    /* Init player and play file until keypress: */
	Wizzcat_Init();

	if(tune != NULL)
    {
        (void)Cconws("(play)\r\n");



        Wizzcat_Play(tune, &tune[lof + BUFSIZE]);
        (void)Cconws("press any key to stop\r\n");
    }

	Cconin();

	Wizzcat_Stop();

	/* return memory to OS: */
	Mfree(tune);
	return 0;
}

