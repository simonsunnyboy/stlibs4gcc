 GCC interface for Wizzcat 12kHz Protracker replay (STE only)
 based on the Wizzcat interface by GT Turbo / Cerebral Vortex for GFABASIC

GCC interface (c) 2014 by Simon Sunnyboy / Paradize
 
 USE AT YOUR OWN RISK!
  
You need the files:
 - wizzcat.S (gcc compiled Wizzcat replay interface)
 - wizzcat.bin (replay code)
 - reloc.bin (relocator)
 - wizzcat.h (the C header file with the function definitions)
 
To build wizzcat.o with gcc
 - wizzcat.S
 - wizzcat.bin (the 12KHz STE replay)
 - reloc.bin (relocator code)
 
Call order:

Wizzcat_Init() - this relocates the replay code and readies it for use.
Wizzcat_Play((void *)tune_start, (void *)tune_end) - this plays a tune

REMARKS:  tune_end is tune_start + (length of tune) + buffer
The buffer is normally around 16KB but can be larger. The replay code uses this
buffer to hold samples and internal data for the replay.

Wizzcat_Stop() - to stop playing the tune.

After issueing a Wizzcat_Stop(), another call to Wizzcat_Play() is allowed.

 
Don't forget to give credits for the replay code if you use this routines:
"Protracker replay by Wizzcat"

Have fun!

STay cool, STay Atari /|\
 - Simon Sunnyboy / Paradize <marndt@asmsoftware.de>
 

