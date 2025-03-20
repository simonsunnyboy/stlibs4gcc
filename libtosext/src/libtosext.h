/**
 * libtosext for Atari ST
 * @file libtosext.h
 * @brief common library header defining all available functions for libtosext
 * @copyright (c) 2016/2025 Matthias Arndt <marndt@final-memory.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef LIBTOSEXT_H
	#define LIBTOSEXT_H

	#include <stdbool.h>
	#include <stdint.h>

    #ifndef NULL
        #define NULL ((char *)0)  /* NULL definition if missing */
    #endif // NULL

	/**
	 * @brief checks if a file given by filename does exist
	 * @param[in] fname is the filename to check for#
	 * @returns true if file exists
	 * @returns false if file does not exist
	 */
	bool FileExists(const char * fname);
	
	/**
     * @brief   returns length of file given by GEMDOS file handle
     * @param[in] handle of file
     * @returns length in bytes OR negative GEMDOS error code
     */
	int32_t FileLength(const int32_t handle);
	
	/**
	 * @brief   returns length of file given by filename
	 * @param[in] fname is the file to check the size for
	 * @returns length in bytes OR negative GEMDOS error code
	 */
	int32_t FileLengthName(const char * fname);

#endif
