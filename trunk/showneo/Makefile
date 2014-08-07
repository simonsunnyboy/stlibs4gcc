# SHOWNEO shows a .NEO picture from disk file on screen
# based upon startup code and Makefile by mfro
# (c) 2014 by Matthias Arndt

TOOLCHAIN_PREFIX=m68k-atari-mint-
CC=$(TOOLCHAIN_PREFIX)gcc

UNAME := $(shell uname)
ifeq ($(UNAME),Linux)
PREFIX=m68k-atari-mint
HATARI=hatari
else
PREFIX=/opt/cross-mint/m68k-atari-mint
HATARI=/usr/local/bin/hatari
endif

# compile for 68000 and optimize
CFLAGS=-m68000 \
	-O3\
	-fomit-frame-pointer \
	-Wall\
	-mshort\
	-nostdlib\
	-std=c99

all: SHOWNEO.TOS

SOURCES=startup.S main.c

OBJECTS=$(SOURCES:.c=.o)

SHOWNEO.TOS: $(OBJECTS) depend
	$(CC) $(CFLAGS) $(OBJECTS) -o SHOWNEO.TOS
	m68k-atari-mint-strip SHOWNEO.TOS

.PHONY clean:
	- rm -rf *.o depend SHOWNEO.TOS

depend: $(SOURCES)
		$(CC) $(CFLAGS) $(INCLUDE) -M $(SOURCES) > depend


ifneq (clean,$(MAKECMDGOALS))
-include depend
endif
