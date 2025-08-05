# Atari ST TTP command line parser
(c) 2025 by Matthias Arndt <marndt@final-memory.org>
 The MIT License applies. See LICENSE for details.

## Abstract
This is a TTP command line parser if no C library is used by the user.

The startup code passes the basepage of the current program to a function.

This function decodes the command line into C strings and passes them to the
main() function provided by the user.

## System requirements

- Atari ST
- GCC cross compiler (typically from V.Riviere or T.Otto)

## Features

- a maximum of MAX_ARGS is parsed (default is 16)
- leading spaces or TAB characters are ignored
- arguments on the given command line may be in quotes with " character
- tokens are separated by space or TAB characters

## Caveats

- limitation to the 126/127 character limit given by TOS
- no support for xargs or other command line extensions
- No environment variable decoding or passing
- limitation of numbers of parameters passed to main()
- no globbing (the user program needs to decode *.* arguments)

## How to use

- link the provided startup code startup.S
- link the compiler parse_basepage.c file
- link custom main() and program
