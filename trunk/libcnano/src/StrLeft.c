/**
 * libcnano for Atari ST
 * @file StrLeft.c
 * @brief implementation of StrLeft(), StrRight() and derivatives
 * @copyright (c) 2014 Matthias Arndt <marndt@asmsoftware.de>
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
 * @brief compares the a string against the left part of the string 
 * @details The beginning of a string can be checked against a different string.
 * @param[in] src is main string
 * @param[in] left_part is the part to be matched on the left end of the main string
 * @return true if the left part matches
 */
bool StrLeft(char * src, char * left_part)
{
    bool match = true;
    
    do
    {
        if(*src++ != *left_part++)
        {
            match = false;
        }
    }
    while((match == true)&&(*left_part != '\0'));
    
    return match;
}

/**
 * @brief matches part of a string at an arbitrary position in the main string
 * @details A NULL string never matches.
 * @param[in] src is the main string to be searched
 * @param[in] start_pos is the index position inside the main string
 * @param[in] match_str is the substring searched in the main string
 * @returns true if the sub string is found
 */
bool StrMid(char * src, uint32_t start_pos, char * match_str)
{
    bool match = false;
    
    while((start_pos > 0)&&(*src != '\0'))
    {
        src++;
        start_pos--;
    }
    
    /* is the string longer than the desired starting position? */
    if(*src != '\0')
    {
        match = StrLeft(src, match_str);
    }
    
    return match;
}
