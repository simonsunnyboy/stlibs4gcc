/**
 * libcnano for Atari ST
 * @file libcnano.h
 * @brief common library header defining all available functions
 * @copyright (c) 2014/2016/2017 Matthias Arndt <marndt@asmsoftware.de>
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

#ifndef LIBCNANO_H
	#define LIBCNANO_H

	#include <stdbool.h>
	#include <stdint.h>

    #ifndef NULL
        #define NULL ((char *)0)  /* NULL definition if missing */
    #endif // NULL

	/* memory copy functions */
	void MemCpy32(void * src, void * dest, uint32_t len);

	/* String handling functions */
	bool StrLeft(char * src, char * left_part);
	bool StrMid(char * src, uint32_t start_pos, char * match);
	void StrCpy(char * src,  char * dest);
	void StrMidCpy(char * dest, uint32_t start_pos, char * src);
    int32_t StrNcmp(char * str1, char * str2, int32_t limit);

	/* File handling functions */
	bool FileExists(const char * fname);
	int32_t FileLength(const int32_t handle);
	int32_t FileLengthName(const char * fname);

#endif
