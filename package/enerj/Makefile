KLEE_INCLUDE_PATH=${HOME}/software/fp-analysis-klee/include

CC=clang
CFLAGS=-g

TARGETS=$(patsubst %.c,%.bc,$(wildcard *c))

all: ${TARGETS}

clean:
	rm -f ${TARGETS} *~

.SUFFIXES: .bc

.c.bc:
	${CC} ${CFLAGS} -c -emit-llvm -I${KLEE_INCLUDE_PATH} $<

