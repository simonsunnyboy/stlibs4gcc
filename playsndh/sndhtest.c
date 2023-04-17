/**
 *	SNDH player lib for GCC
 *	(c) 2010/2014/2019/2023 by Simon Sunnyboy / Paradize <marndt@asmsoftware.de>
 *	http://paradize.atari.org/
 *
 *	SNDH player library routines
 *	some parsing algorithms are derived from GODLIB
 *
 *	This library is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU Lesser General Public
 *	License as published by the Free Software Foundation; either
 *	version 2.1 of the License, or (at your option) any later version.
 *
 *	This library is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *	Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public
 *	License along with this library; if not, write to the Free Software
 *	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 */

#include <stdint.h>
#include <osbind.h>
#include "sndh.h"

#if (!defined NULL)
#define NULL 0
#endif

uint8_t ramdisk[20000];

static void PRINT ( const char *str1, const char *str2 )
{
	( void ) Cconws ( str1 );
    if ( str2 != NULL )
    {
	    ( void ) Cconws ( str2 );
    }
    else
    {
        ( void ) Cconws ( "undefined" );
    }
	( void ) Cconws ( "\r\n" );
	return;
}

int main ( void )
{
    SNDHTune mytune;
    void* tuneptr;
    tuneptr = &ramdisk[0];

    if ( tuneptr != NULL )
    {
        long handle;

        ( void ) Cconws ( "\033E" );

        /* load file into ramdisk
         * NOTE: The SNDH must be unpacked!
         */
        handle = Fopen ( "heroques.snd", 0 );

        if(handle < 0)
        {
            ( void ) Cconws ( "ERROR: SNDH file not found!\r\n" );
        }
        else
        {
            /* fiel found, read tune into RAM and play ...*/
            Fseek ( 0,handle, 0 );
            Fread ( handle, 20000, tuneptr );
            
            /* parse SNDH header */
            SNDH_GetTuneInfo ( tuneptr,&mytune );
            /* replay the first tune */
            SNDH_PlayTune ( &mytune,0 );
            /* display some information about the tune */
            
            PRINT ( "TITL: ",mytune.title );
            PRINT ( "COMP: ",mytune.composer );
            PRINT ( "RIPP: ",mytune.ripper );
            PRINT ( "CONV: ",mytune.conv );


        }
        Fclose ( handle );
        /* wait for keypress and terminate replay */
        Cconin();
        SNDH_StopTune();
    }

    return 0;
}
