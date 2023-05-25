/*
 *	Linkfile support for C
 *	(c) 2017/2023 by Simon Sunnyboy / Paradize <marndt@asmsoftware.de>
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

#include <osbind.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "linkfile.h"

/**
 * @brief   inits the basic linkfile object
 * @details There is no ramdisk allocated and no transfer from file to memory performed. The linkfile on disk is accessed once to check GEMDOS permissions.
 * @param   filename for linkfile
 * @param   link point to linkfile objects for further reference
 * @param   offsetlist points to linkfile specific file offset definitions
 * @param   nr_files within linkfile
 * @return  0 on success, GEMDOS error for file access otherwise
 */
int32_t Linkfile_Init(const char *filename, linkfile_t * link, linkfile_offset_t * offsetlist, const uint16_t nr_files)
{
    int32_t handle;

    /* init linkfile handling with given filename and offset definitions */
    link->filename = filename;
    handle = Fopen ( link->filename, 0 );
    Fclose(handle);

    if(handle >= 0)
    {
        /* file could be opened, success */
        handle = 0;
    }

    if((offsetlist != NULL)&&(nr_files > 0))
    {
        /* offset list and number of contained files is valid: */
        link->filelist = offsetlist;
        link->nr_files = nr_files;
    }
    else
    {
        /* bogus offset list or number of contained files: */
        link->filelist = NULL;
        link->nr_files = 0;
    }
    link->in_ram = false;    /* linkfile data not transferred to ramdisk yet */
    link->ramdisk = NULL;    /* no ramdisk allocated */

    return handle;
}

/**
 * @brief   deinits a ramdisk allocated with Linkfile_AllocateInRAM
 * @details Further reads from the linkfile can be made. They access the actual file then.
 * @param   link points to linkfile object
 * @see     Linkfile_AllocateInRAM
 */
void Linkfile_Deinit(linkfile_t * link)
{
    /* deallocate ramdisk if active */
    if(link->ramdisk != NULL)
    {
        (void)Mfree(link->ramdisk);
        link->in_ram = false;
    }
}

/**
 * @brief     transfers data from linkfile to a memory destination.
 * @details   Data is directly loaded from disk unless the ram disk is active. Otherwise data is transferred from the ram disk.
 * @param     link points to linkfile object
 * @param     file_nr indicates the desired file within the linkfile
 * @param     dest points to the memory destination
 * @attention The memory destination must beable to hold the data from the selected file. No memory size checks are performed.
 */
void Linkfile_GetFile(linkfile_t * link, const uint16_t file_nr, void * dest)
{
    if((dest != NULL)&&(link != NULL)&&(file_nr < link->nr_files))
    {
        uint32_t length = link->filelist[file_nr].length;
        uint32_t offset = link->filelist[file_nr].offset;

        if(link->in_ram == true)
        {
            /* Transfer from ramdisk to destination: */
            uint32_t * src_data = (uint32_t *)((uint32_t)link->ramdisk + (uint32_t)offset);
            uint32_t * dest_data = (uint32_t*) dest;
            while(length > 3)
            {
                *dest_data++ = *src_data++;
                length -= 4;
            }
            uint8_t * src_u8 = (uint8_t *)src_data;
            uint8_t * dest_u8 = (uint8_t *)dest_data;
            while(length)
            {
                *dest_u8++=*src_u8++;
                length--;
            }

        }
        else
        {
            /* Read from actual linkfile: */
            int32_t handle;
            handle = Fopen ( link->filename, 0 );
            if(handle >= 0)
            {
                Fseek ( offset, handle, 0 );
                Fread ( handle, length, dest);
            }
            Fclose ( handle );

        }
    }

    return;
}

/**
 * @brief returns the length of an individual file within the linkfile
 * @param link points to linkfile object
 * @param file_nr indicates the file within the linkfile
 * @return file length in bytes, 0 if file_nr is invalid
 */
uint32_t Linkfile_GetFileLength(linkfile_t * link, const uint16_t file_nr)
{
    uint32_t len = 0;

    /* fetch file length for valid files */
    if(file_nr < link->nr_files)
    {
        len = link->filelist[file_nr].length;
    }


    return len;
}

/**
 * @brief calculate actual linkfile data content size from offset list
 * @param link points to linkfile object
 * @return size in bytes
 */
uint32_t Linkfile_GetSize(linkfile_t * link)
{
    uint32_t overall_size_of_files = 0;

    if((link->nr_files > 0)&&(link->filelist != NULL))
    {
        overall_size_of_files = link->filelist[link->nr_files -1].offset + link->filelist[link->nr_files -1].length;
    }

    return overall_size_of_files;
}

/**
 * @brief   allocates a ramdisk for the given linkfile
 * @details Use Linkfile_ToRAM to load linkfile contents to freshly allocated ramdisk on success. Atleast one file must be within the linkfile for allocation to succeed.
 * @param   link points to linkfile object
 * @return true if ramdisk was allocated (success), otherwise false
 */
bool Linkfile_AllocateInRAM(linkfile_t * link)
{
    bool ramdisk_allocated = false;

    /* check if ramdisk is not allocated and allocate one if necessary */
    if((link->ramdisk == NULL)&&(link->nr_files > 0))
    {
        link->ramdisk = (void *)Malloc(Linkfile_GetSize(link));
        if(link->ramdisk != NULL)
        {
            ramdisk_allocated = true;
        }
    }

    return ramdisk_allocated;
}

/**
 * @brief reads linkfile data into the ramdisk
 * @details The ramdisk must have been allocated first with Linkfile_AllocateInRAM. GEMDOS errors on loading deactivate the ramdisk access.
 * @param link points to linkfile object
 */
void Linkfile_ToRAM(linkfile_t * link)
{
    /* successful transfer to ramdisk sets in_ram flag for Linkfile_Get() */
    if((link->ramdisk != NULL)&&(link->nr_files > 0))
    {
        int32_t handle;

        handle = Fopen ( link->filename, 0 );
        if(handle >= 0)
        {
            Fseek ( 0,handle, 0 );
            Fread ( handle, Linkfile_GetSize(link), link->ramdisk);
            link->in_ram = true;
        }
        Fclose ( handle );

    }

    return;
}
