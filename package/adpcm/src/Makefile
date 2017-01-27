#
# Makefile for adpcm and test programs
# -------------------
#
# Modified for compilation with wllvm and KLEE runtime for producing
# whole-program bitcode for running with KLEE.
# By Andrew Santosa (santosa_1999@yahoo.com)

#####################################################################
# Added by C. Lee.
#
# On Sun machines, gcc need to be informed whether the machines have
# integer multipliers by specifying this option: -mv8.
#
# Also, on Sun machines, in order to use the SPIXTOOLS and SHADE,
# uncomment this option: -static.
#
CC = clang-3.4
LFLAGS = -mv8
LFLAGS = $(LFLAGS) -static
#
# End of addition
######################################################################
CFLAGS = -static -O3

# May need this on a sun:
# CFLAGS=-O -I/usr/demo/SOUND

WLLVM_HOME=${HOME}/software/whole-program-llvm
KLEE_HOME=${HOME}/software/klee/Release+Asserts
LLVM_COMPILER=clang
CC=${WLLVM_HOME}/wllvm
CFLAGS=-g -I${KLEE_HOME}/include
LDFLAGS=-L${KLEE_HOME}/lib
LDLIBS=-lkleeRuntest

ALLSRC=README adpcm.2 Makefile adpcm.h libst.h adpcm.c timing.c rawcaudio.c \
	rawdaudio.c suncaudio.c sgicaudio.c sgidaudio.c hello.adpcm.uu

all: adpcm.o rawcaudio rawdaudio timing
	cp rawcaudio rawdaudio timing ../bin/.

sgi: all sgicaudio sgidaudio

sun: all suncaudio sundaudio

adpcm.o: adpcm.h

suncaudio: suncaudio.o adpcm.o
	$(CC) adpcm.o suncaudio.o -o suncaudio -L/usr/demo/SOUND -laudio

sundaudio: suncaudio
	cp suncaudio sundaudio

sgicaudio: sgicaudio.o adpcm.o
	$(CC) sgicaudio.o adpcm.o -o sgicaudio -laudiofile -lm

sgidaudio: sgidaudio.o adpcm.o
	$(CC) sgidaudio.o adpcm.o -o sgidaudio -laudiofile -lm

rawcaudio: rawcaudio.o adpcm.o
	$(CC) $(CFLAGS) $(LDFLAGS) rawcaudio.o adpcm.o -o rawcaudio $(LDLIBS)
	$(WLLVM_HOME)/extract-bc $@

rawdaudio: rawdaudio.o adpcm.o
	$(CC) $(CFLAGS) $(LDFLAGS) rawdaudio.o adpcm.o -o rawdaudio $(LDLIBS)
	$(WLLVM_HOME)/extract-bc $@

timing: timing.o adpcm.o
	$(CC) $(CFLAGS) $(LDFLAGS) timing.o adpcm.o -o timing $(LDLIBS)
	$(WLLVM_HOME)/extract-bc $@

adpcm.shar: $(ALLSRC)
	shar $(ALLSRC) > adpcm.shar

# Added by C. Lee
clean:
	rm -f *.o ; rm rawcaudio rawdaudio timing ; rm -f ../bin/* ../output*
