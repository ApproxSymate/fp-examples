KLEE_HOME=${HOME}/software/fp-analysis-klee/
KLEE_INCLUDE_PATH=${KLEE_HOME}/include

CC=clang
CFLAGS=-g

TARGETS=$(patsubst %.c,%.bc,$(wildcard *c))

all: ${TARGETS}

clean:
	rm -rf ${TARGETS} *~ klee-last klee-out-* *.klee

.SUFFIXES: .bc .klee

.bc.klee:
	@if [ "$*"=="FloodFiller" ] ; then \
		EXTRA_OPTIONS="--max-depth=2" ; \
	fi ; \
	${KLEE_HOME}/Release+Asserts/bin/klee --precision --output-dir=$@ $*.bc

.c.bc:
	${CC} ${CFLAGS} -c -emit-llvm -I${KLEE_INCLUDE_PATH} $<

