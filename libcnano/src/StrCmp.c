/**
 * libcnano for Atari ST
 * @file StrCmp.c
 * @brief implementation of StrCmp() and derivates
 * @details This sums up functions for string comparison.
 *
 * @copyright (c) 2017 Matthias Arndt <marndt@asmsoftware.de>
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

#include "libcnano.h"

/**
 * @brief compares at most the first n bytes from str1  str2.
 * @details
 * @param[in] str1 points to the first string
 * @param[in] str2 points to the second string
 * @param[in] limit denotes the number of characters to compare
 * @returns value < 0 then it indicates str1 is less than str2.
 * @returns value > 0 then it indicates str2 is less than str1.
 * @returns value = 0 then it indicates str1 is equal to str2 within the limit of characters
 */
int32_t StrNcmp(char * str1, char * str2, int32_t limit)
{
    for(; ((--limit) && (*str1 == *str2)); ++str1, ++str2)
    {
        if(*str1 == '\0')
            return(0);
    }

    return(*str1 - *str2);
}

char * StrChr(char * string, char symbol)
{
    do
    {
        if(*string == symbol)
        {
            return(string);
        }
    }
    while(*string++);

    return(NULL);
}

int32_t StrCmp(char * str1, char * str2)
{
    for(; *str1 == *str2; ++str1, ++str2)
    {
        if(*str1 == '\0')
        {
            return(0);
        }
    }

    return(*str1 - *str2);
}
