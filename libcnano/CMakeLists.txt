cmake_minimum_required(VERSION 2.8)
project("libcnano")
# disable strange gcc assumptions
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

# select Atari ST cross compiler
enable_language("ASM")

set(CMAKE_C_COMPILER m68k-atari-mint-gcc)
set(CMAKE_ASM_COMPILER m68k-atari-mint-as)
set(CMAKE_AR m68k-atari-mint-ar)
set(CMAKE_RANLIB m68k-atari-mint-ranlib)
set(CMAKE_C_FLAGS "-m68000 -O3 -fomit-frame-pointer -Wall -mshort -nostdlib -std=c99")
set(CMAKE_ASM_FLAGS "-m68000 -I${PROJECT_SOURCE_DIR}")

# linker flags to compile excutables
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_C_FLAGS} ${PROJECT_SOURCE_DIR}/test/startup.S" )


link_directories(${CMAKE_SOURCE_DIR})
link_directories(test)

include_directories(
	src/
	test/
)

# the cnano library itself
add_library(cnano
	src/libcnano.h
	src/MemCpy32.c
	src/StrCpy.c
	src/StrLeft.c
	src/FileExists.c
	src/FileLength.c
)

# test program for basic file access functions
add_executable( file.tos
	test/test_filefunc.c
)

target_link_libraries(file.tos cnano)

