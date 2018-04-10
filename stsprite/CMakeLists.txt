cmake_minimum_required(VERSION 2.8)

project(STSprite_GCC)
# disable strange gcc assumptions
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

# define some directories
set(SPRITE_SRC ${PROJECT_SOURCE_DIR}/src/)



# select Atari ST cross compiler and enable assembly language source files
enable_language("ASM")

set(CMAKE_C_COMPILER m68k-atari-mint-gcc)
set(CMAKE_ASM_COMPILER m68k-atari-mint-as)
set(CMAKE_AR m68k-atari-mint-ar)
set(CMAKE_RANLIB m68k-atari-mint-ranlib)
set(CMAKE_C_FLAGS "-m68000 -O3 -fomit-frame-pointer -Wextra -Wall -mshort -nostdlib -std=c99")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_C_FLAGS} ${PROJECT_SOURCE_DIR}/startup.S" )

# include directories for assembly sources
set(CMAKE_ASM_FLAGS "-m68000 -I${SPRITE_SRC}")

include_directories(${SPRITE_SRC})

# compile seperate library
add_subdirectory(src)

# test program
add_executable(stsprite.tos
	main.c
	README.md
	LICENSE
)

target_link_libraries(stsprite.tos stsprite)
