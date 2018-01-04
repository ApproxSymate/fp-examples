# To build:
# KLEE_HOME=<klee_source_path> make

KLEE=${KLEE_HOME}/build/bin/klee
KLEE_INCLUDE=${KLEE_HOME}/include
CC=clang
CFLAGS=-g
LIBSRC=jaricom.c \
	jerror.c \
	jcapimin.c \
	jcapistd.c \
	jccoefct.c \
	jccolor.c \
	jcdctmgr.c \
	jchuff.c \
	jcinit.c \
	jcmainct.c \
	jcmarker.c \
	jcmaster.c \
	jcparam.c \
	jcprepct.c \
	jcsample.c \
	jdapimin.c \
	jdatadst.c \
	jfdctint.c \
	jmemmgr.c \
	jmemnobs.c \
	jdapistd.c \
	jdarith.c \
	jdcoefct.c \
	jdcolor.c \
	jddctmgr.c \
	jdhuff.c \
	jdmainct.c \
	jdmarker.c \
	jdmaster.c \
	jdmerge.c \
	jdinput.c \
	jdpostct.c \
	jdsample.c \
	jdatasrc.c \
	jcomapi.c \
	jidctint.c \
	jidctflt.c \
	jidctfst.c \
	jutils.c \
	jquant1.c \
	jquant2.c

LIBBITCODE=$(patsubst %.c,%.bc,${LIBSRC})

TARGETBITCODE=memdjpeg.whole.bc memcjpeg.whole.bc

all: ${TARGETBITCODE}

%.whole.bc: ${LIBBITCODE}
	make $*.bc
	llvm-link ${LIBBITCODE} $*.bc > $*.whole.bc

memdjpeg.klee: all
	${KLEE} -output-dir=$@ -precision memdjpeg.whole.bc

clean:
	rm -rf *.bc *~ klee-out-* klee-last *.klee

.SUFFIXES: .bc

.c.bc:
	${CC} ${CFLAGS} -I ${KLEE_INCLUDE} -c -emit-llvm $<
