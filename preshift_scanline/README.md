# Atari ST ST-Low Scanline preshift

(c) 2025 by Matthias Arndt <marndt@final-memory.org>
 The MIT License applies. See LICENSE for details.

## Abstract
This is a sample routine to handle preshifting of pixel data in the 4 bitplane
format of the Atari ST low resolution of 320x200 pixels.

A basic routine is provided to handle a single scanline in M68K assembly
language.

An improved API for use with C code as well as a code sample is provided.

## System requirements

- Atari ST with color monitor
- GCC cross compiler (typically from V.Riviere or T.Otto)
