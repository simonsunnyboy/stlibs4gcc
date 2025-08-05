# Startup code to parse the commandline given in the basepage
# The basepage pointer is passed to a function parse_basepage()
# This function in turn calls the main function of the user.
#
# (c) 2025 by Matthias Arndt <marndt@final-memory.org>
#
# The MIT License applies. See the file LICENSE for details.
#
# Example program
#

project(ttp_startup)

cmake_minimum_required(VERSION 2.8)

# disable strange gcc assumptions
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

# select Atari ST cross compiler
set(CMAKE_C_COMPILER m68k-atari-mint-gcc)
set(CMAKE_ASM_COMPILER m68k-atari-mint-as)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m68000 -fomit-frame-pointer -Wextra -Wall -Wl,--traditional-format -mshort -nostdlib -std=c99")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_C_FLAGS} ${PROJECT_SOURCE_DIR}/startup.S" )

add_executable(ttpstart.ttp
    parse_basepage.c
    main.c
)
