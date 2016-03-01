/**
 * libcnano for Atari ST
 * @file FileLength.c
 * @brief implementation of FileLength() and FileLengthName()
 * @copyright (c) 2016 Matthias Arndt <marndt@asmsoftware.de>
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

#include <stdint.h>
#include <stdbool.h>
#include <osbind.h>

#include "libcnano.h"

/**
 * @brief   returns length of file given by filename
 * @returns length in bytes OR negative GEMDOS error code
 */
int32_t FileLengthName(const char *fname)
{
	int32_t handle;
	int32_t length;

	handle = Fopen(fname, 0);

	if(handle)
	{
		length = Fseek( 0, handle, 2);  // final byte of file
		Fclose(handle);  // close file
	}
	else
	{
		length = handle; // GEMDOS error
	}

	return length;
}


int32_t FileLength(const int32_t handle)
{

	int32_t length;

	if(handle < 0)
	{
		length = handle;  // GEMDOS error
	}
	else
	{
		int32_t offset;

		offset = Fseek(0, handle, 1); // get actual position in file
		length = Fseek(0, handle, 2);  // final byte of file

		Fseek(offset, handle, 0); // set handle positon back to given position, allow seek accesses together with reading the file name

	}

	return length;
}
