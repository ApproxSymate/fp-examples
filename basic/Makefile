
KLEE_HOME=${HOME}/software/klee/Release+Asserts

TARGETS=$(patsubst %.c,%.klee,$(wildcard *c))

CC=clang

all: ${TARGETS}

clean:
	rm -rf *.klee *.bc

.SUFFIXES: .bc .klee

.c.bc:
	${CC} -c -emit-llvm -g $<

.bc.klee:
	${KLEE_HOME}/bin/klee -output-dir=$@ $<

