TOOLCHAIN_PREFIX=m68k-atari-mint-
CC=$(TOOLCHAIN_PREFIX)gcc

# compile for 68000 and optimize
CFLAGS=-m68000\
	-g\
	-O3\
	-fomit-frame-pointer\
	-Wall\
	-mshort\
	-nostdlib\
	-std=c99

EXE=SPOKE.TOS

SOURCES=main.c 

OBJECTS=$(SOURCES:.c=.o) shortpoke.o

all: $(OBJECTS) depend
	$(CC) $(CFLAGS) -Wl,--traditional-format startup.S $(OBJECTS) -o $(EXE)
	#$(TOOLCHAIN_PREFIX)strip $(EXE)
	$(TOOLCHAIN_PREFIX)objdump -g -D $(EXE) >$(EXE).lst

.PHONY clean:
	- rm -rf *.o depend $(EXE)

shortpoke.o: shortpoke.s
	$(CC) $(CFLAGS) -c shortpoke.s

depend: $(SOURCES)
		$(CC) $(CFLAGS) $(INCLUDE) -M $(SOURCES) shortpoke.s > depend

ifneq (clean,$(MAKECMDGOALS))
-include depend
endif
