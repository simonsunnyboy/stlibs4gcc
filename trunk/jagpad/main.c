/*
 * Demo program for Jagpad polling
 * (c) 2010 by Simon Sunnyboy / Paradize
 */
#include <stdio.h>
#include <stdlib.h>

#include <osbind.h>
#include <stdlib.h>

#include <stdint.h>

#include "jagpad.h"

#define JAGPAD pad0

#define PRINT (void)Cconws

long mymain()
{
	PRINT("\033w");

   while((JAGPAD & JAGPAD_BUT_HASH) == 0)
   {
   	Jagpad_Read();
   	JAGPAD = pad0;

   	if(JAGPAD & 1)
   		PRINT("UP\r\n");
   	if(JAGPAD & 2)
   		PRINT("DOWN\r\n");
   	if(JAGPAD & 4)
   		PRINT("LEFT\r\n");
   	if(JAGPAD & 8)
   		PRINT("RIGHT\r\n");
   	if(JAGPAD & 16)
   		PRINT("FIRE A\r\n");
   	if(JAGPAD & 32)
   		PRINT("FIRE B\r\n");
   	if(JAGPAD & 64)
   		PRINT("FIRE C\r\n");


   }

   return 0;
}


int main()
{
   return(Supexec(mymain));
}

