/*
 *	Linkfile support for C - demo application
 *	(c) 2017 by Simon Sunnyboy / Paradize <marndt@asmsoftware.de>
 *	http://paradize.atari.org/
 *
 *	access to data linkfiles by "GFA Linkfile by MUG U.K¿"
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

#include "linkfile.h"

linkfile_offset_t testlink_offsets[] =
{

    /* C:\ANIME1.NEO */
    { 0,32128 },
    /* C:\ANIME2.NEO */
    { 32128,32128 },
    /* C:\MESSAGE.TXT */
    { 64256,24 }
};

linkfile_t testlink;

uint8_t buffer[32128];  /* buffer space for data loaded from linkfile */

static void Screen_ShowNeo(void * neochrome_pic)
{
	uint32_t * src = (uint32_t *)neochrome_pic;
	uint16_t * palette = (uint16_t *)&src[1];
	uint32_t * dest = (uint32_t *)Logbase();

	src = &src[32];

	int idx;

	for(idx = 0; idx < 2000; idx ++)
	{
		*dest++ = *src++;
		*dest++ = *src++;
		*dest++ = *src++;
		*dest++ = *src++;
	}

	Setpalette(palette);
}

int main(void)
{
    (void)Cconws("-- Linkfile demo --\r\n");
    (void)Cconws("TESTLINK.LNK shall be next to the\r\ntest program\r\n");
    if(Linkfile_Init("TESTLINK.LNK", &testlink, &testlink_offsets[0], 3) < 0)
    {
        (void)Cconws("!! GEMDOS ERROR File not not found!!\r\n");
        Bconin(2);
    }
    else
    {
        (void)Cconws("linkfile found\r\n");    
        (void)Cconws("Attempt test from RAM? (Y/N)\r\n");
        const int32_t answer = Bconin(2);

        if(((char)answer == 'Y') ||
           ((char)answer == 'y'))
        {
            if(Linkfile_AllocateInRAM(&testlink) == true)
            {
                Linkfile_ToRAM(&testlink);
                if(testlink.in_ram == true)
                {
                    (void)Cconws("RAM disk loaded\r\n");    
                }
                else
                {
                    (void)Cconws("RAM disk failed - use disk!\r\n");
                }
            }
            else
            {
                (void)Cconws("RAM allocation failed- use disk!\r\n");
            }
        }
        else
        {
            (void)Cconws("test from disk\r\n");
        }
        (void)Cconws("press key to test....\033f\r\n");
        Bconin(2);

        Linkfile_GetFile(&testlink, 2, &buffer[0]);
        buffer[Linkfile_GetFileLength(&testlink, 2)] = '\0';
        (void)Cconws(&buffer[0]);
        Bconin(2);

        Linkfile_GetFile(&testlink, 0, &buffer[0]);
        Screen_ShowNeo(buffer);
        Bconin(2);

        Linkfile_GetFile(&testlink, 1, &buffer[0]);
        Screen_ShowNeo(buffer);
        Bconin(2);

    }
    
    return 0;
}

