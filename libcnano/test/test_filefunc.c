/**
 * libcnano for Atari ST
 * @file test_filefunc.c
 * @brief test program for TOS file access functions
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

#include <osbind.h>
#include <stdint.h>

#include "libcnano.h"

#define INT_DIGITS 19		/* enough for 64 bit integer */

char *myitoa(int32_t i)
{
  /* Room for INT_DIGITS digits, - and '\0' */
  static char buf[INT_DIGITS + 2];
  char *p = buf + INT_DIGITS + 1;	/* points to terminating '\0' */

  if (i >= 0) {
    do {
      *--p = '0' + (i % 10);
      i /= 10;
    } while (i != 0);
    return p;
  }
  else {			/* i < 0 */
    do {
      *--p = '0' - (i % 10);
      i /= 10;
    } while (i != 0);
    *--p = '-';
  }
  return p;
}


void Print(const char *str)
{
	(void)Cconws(str);
	return;
}

int main(void)
{
	Print("\033E"__FILE__ " " __DATE__ "\r\n\n");

	Print("Testcases FileExists()\r\n");

	if(FileExists("FILE.TOS") != true)
	{
		Print("ERROR FileExists 1\r\n");
	}
	if(FileExists("UNKNOWN") != false)
	{
		Print("ERROR FileExists 2\r\n");
	}

	Print("Testcases FileLengthName()\r\n");

	int32_t filelen = FileLengthName("FILE.TOS");

	if(filelen < 0)
	{
		Print("ERROR FileLengthName 1\r\n");
	}
	else
	{
		Print(".. file length in bytes:");
		Print(myitoa(filelen));
		//Print(myitoa(54321));
		Print("\r\n");
	}

	if(FileLengthName("UNKNOWN"))
	{
		Print("ERROR FileLengthName 2\r\n");
	}
	Print("...\r\n");

	Print("Testcases FileLength()\r\n");

	int32_t myhandle = Fopen("File.tos",0);
	if(myhandle < 0)
	{
			Print("ERROR FileLength Fopen failed\r\n");

	}
	else
	{
		int32_t length;

		Fseek(15, myhandle, 0);  // move into file
		length = FileLength(myhandle); // get length
		if(length < 0)
		{
			Print("ERROR FileLength 2\r\n");
		}

		if(Fseek(0, myhandle, 1) != 15)
		{
			Print("ERROR FileLength 3\r\n");
		}

		Fclose(myhandle);
	}



	Bconin(2);
	return 0;
}
