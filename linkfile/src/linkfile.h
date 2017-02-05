/*
 *	Linkfile support for C
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

#ifndef LINKFILE_H
    #define LINKFILE_H

    #include <stdint.h>
    #include <stdbool.h>

    /**
     * @brief structure of linkfile file offset definitions
     */
    typedef struct
    {
        uint32_t offset;  /**< offset within linkfile */
        uint32_t length;  /**< length of file within linkfile */
    } linkfile_offset_t;

    /**
     * @brief linkfile holding structure
     */
    typedef struct
    {
        const char        *filename;  /**< filename of linkfile */
        linkfile_offset_t *filelist;  /**< pointer to list of file offsets within linkfile */
        uint16_t          nr_files;   /**< number of files within linkfile */
        bool              in_ram;     /**< indicates linkfile is loaded within RAM */
        void              *ramdisk;   /**< pointer to allocated RAMDISK for linkfile */
    } linkfile_t;

    int32_t Linkfile_Init(const char *filename, linkfile_t * link, linkfile_offset_t * offsetlist, const uint16_t nr_files);
    void Linkfile_Deinit(linkfile_t * link);
    void Linkfile_GetFile(linkfile_t * link, const uint16_t file_nr, void * dest);
    uint32_t Linkfile_GetFileLength(linkfile_t * link, const uint16_t file_nr);
    uint32_t Linkfile_GetSize(linkfile_t * link);
    bool Linkfile_AllocateInRAM(linkfile_t * link);
    void Linkfile_ToRAM(linkfile_t * link);

#endif
