#
# Experimental File to build a basic file with custom startup code and without MiNTLib
# Version 17.7.2014
#

cmake_minimum_required(VERSION 2.8)

project(PreshiftScanlineSTLOW)

# disable strange gcc assumptions
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

# select Atari ST cross compiler
set(CMAKE_C_COMPILER m68k-atari-mint-gcc)
set(CMAKE_ASM_COMPILER m68k-atari-mint-as)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m68000 -fomit-frame-pointer -Wextra -Wall -Wl,--traditional-format -mshort -nostdlib -std=c99")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_C_FLAGS} ${PROJECT_SOURCE_DIR}/startup.S" )

# select Atari ST cross compiler and enable assembly language source files
enable_language("ASM")

# GNU as configuration
set(CMAKE_ASM_FLAGS_RELEASE "")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -m68000")

add_executable(preshift.tos
    main.c
    preshift.S
    preshift_block.c
)
