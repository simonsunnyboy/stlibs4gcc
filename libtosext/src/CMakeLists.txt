# basic build target for libtosext

include_directories(${CMAKE_CURRENT_LIST_DIR})

add_library(tosext
	libtosext.h
	FileExists.c
	FileLength.c	
)
