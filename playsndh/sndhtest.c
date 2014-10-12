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

  	    handle = Fopen ( "heroques.snd", 0 );
        Fseek ( 0,handle, 0 );
        Fread ( handle, 20000, tuneptr);
        Fclose ( handle );

		SNDH_GetTuneInfo(tuneptr,&mytune);

		SNDH_PlayTune(&mytune,0);


		PRINT("TITL: ",mytune.title);
		PRINT("COMP: ",mytune.composer);
		PRINT("RIPP: ",mytune.ripper);
		PRINT("CONV: ",mytune.conv);
		/*PRINT("FREQ: ",mytune.freq); */

		Cconin();
		SNDH_StopTune();
	}

	return 0;
}
