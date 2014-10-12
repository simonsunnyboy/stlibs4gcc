/* Test program for SNDH routines */

#include <stdint.h>
#include <osbind.h>
#include "sndh.h"

uint8_t ramdisk[20000];

static void PRINT(const char *str1, const char *str2)
{
    (void)Cconws(str1);
    (void)Cconws(str2);
    (void)Cconws("\r\n");
    return;
}

int main(void)
{
	SNDHTune mytune;
	void* tuneptr;

	tuneptr = &ramdisk[0];
	if(tuneptr != 0)
	{
	    long handle;
        /* load file into ramdisk */
  	    handle = Fopen ( "heroques.snd", 0 );
        Fseek ( 0,handle, 0 );
        Fread ( handle, 20000, tuneptr);
        Fclose ( handle );
        /* parse SNDH header */
		SNDH_GetTuneInfo(tuneptr,&mytune);
        /* replay the tune */
		SNDH_PlayTune(&mytune,0);
        /* display some information about the tune */
        (void)Cconws("\033E");
		PRINT("TITL: ",mytune.title);
		PRINT("COMP: ",mytune.composer);
		PRINT("RIPP: ",mytune.ripper);
		PRINT("CONV: ",mytune.conv);
		/*PRINT("FREQ: ",mytune.freq); */

        /* wait for keypress and terminate replay */
		Cconin();
		SNDH_StopTune();
	}

	return 0;
}
