# basic build target for libcnano

include_directories(${CMAKE_CURRENT_LIST_DIR})

add_library(cnano
	libcnano.h
	MemCpy32.c
	StrCmp.c
	StrCpy.c
	StrLeft.c
)
