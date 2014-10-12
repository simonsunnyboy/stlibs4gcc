/*
 *	SNDH player lib for AHCC
 *	(c) 2010 by Simon Sunnyboy / Paradize <marndt@asmsoftware.de>
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

#include "sndh.h"
#include <stdint.h>

#if (!defined NULL)
#define NULL 0
#endif

/* internal variables */
SNDHTune *SNDH_ActiveTune;	/* this is not NULL if a tune has been hookedup for play */

/* prototype of internal functions */
void 		SNDH_PlayTuneISR(void *tuneptr, uint16_t freq, uint16_t subtune);
void		SNDH_StopTuneISR(void);
char*		SNDH_FindLongInHeader(char* chunk, char *tag);
char*		SNDH_FindWordInHeader(char* chunk, char *tag);
uint16_t	SNDH_ParseDecimal(char *chunk);

/* functions */
void SNDH_GetTuneInfo(void *tuneptr, SNDHTune *tune)
{
	char *parser, *freqtag;

	/* assert valid SNDH tune */
	if(tuneptr == NULL)
	{
		tune = NULL;
		return;
	}

	parser = (char *)tuneptr;
	if(SNDH_FindLongInHeader(parser, "SNDH") != 0)
	{
		/* SNDH file is valid */
		tune->tuneadr  = tuneptr;
		/* get pointers to SNDH meta data */
		tune->title    = SNDH_FindLongInHeader(parser, "TITL");
		tune->composer = SNDH_FindLongInHeader(parser, "COMM");
		tune->ripper   = SNDH_FindLongInHeader(parser, "RIPP");
		tune->conv     = SNDH_FindLongInHeader(parser, "CONV");
		/* try to parse replay frequency */
		if( (freqtag = SNDH_FindWordInHeader(parser,"TC")))
		{
			/* Timer C tunes have priority in detection */
			tune->freq = SNDH_ParseDecimal(freqtag);
		}
		else if( (freqtag = SNDH_FindWordInHeader(parser,"TA")))
		{
			tune->freq = SNDH_ParseDecimal(freqtag);
		}
		else if( (freqtag = SNDH_FindWordInHeader(parser,"TB")))
		{
			tune->freq = SNDH_ParseDecimal(freqtag);
		}
		else if( (freqtag = SNDH_FindWordInHeader(parser,"TD")))
		{
			tune->freq = SNDH_ParseDecimal(freqtag);
		}
		else if( (freqtag = SNDH_FindWordInHeader(parser,"V!")))
		{
			tune->freq = SNDH_ParseDecimal(freqtag);
		}
		else
		{
			/* unknown replay speed - default to 50Hz */
			tune->freq = 50;
		}
	}
	else
	{
		tune = NULL;
	}
	return;
}

void SNDH_PlayTune(SNDHTune *tune, uint16_t subtune)
{
	if(tune == NULL)
	{
		/* tune is not valid */
		return;
	}

	if(SNDH_ActiveTune != NULL)
	{
		SNDH_StopTune();
	}
	if(tune->tuneadr != NULL)
	{
		SNDH_ActiveTune = tune;
		SNDH_PlayTuneISR(tune->tuneadr, tune->freq, subtune);
	}
	return;
}

void SNDH_StopTune(void)
{
	SNDH_ActiveTune = NULL;
	SNDH_StopTuneISR();
	return;
}

char* SNDH_FindLongInHeader(char* chunk, char *tag)
{
	uint16_t i;

	for( i=0; i<1024; i++ )
	{
		if(  (chunk[i]   == tag[ 0 ] )
		   &&(chunk[i+1] == tag[ 1 ] )
		   &&(chunk[i+2] == tag[ 2 ] )
		   &&(chunk[i+3] == tag[ 3 ] )
		  )
		{
			return( &chunk[i+4] );
		}
	}
	return( NULL );
}

char* SNDH_FindWordInHeader(char* chunk, char *tag)
{
	uint16_t i;

	for( i=0; i<1024; i++ )
	{
		if(  (chunk[i]   == tag[ 0 ] )
				    &&(chunk[i+1] == tag[ 1 ] )
		  )
		{
			return( &chunk[i+2] );
		}
	}
	return( NULL );
}

uint16_t SNDH_ParseDecimal(char *chunk)
{
	uint16_t value = 0;

	while( *chunk != 0)
	{
		value *= 10;
		value += (*chunk++) - '0';
	}

	return( value );
}
