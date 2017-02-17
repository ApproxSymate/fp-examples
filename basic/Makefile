EXTRA_OPTIONS=-debug-fp-error

KLEE_HOME=${HOME}/software/klee/Release+Asserts

TARGETS=$(patsubst %.c,%.klee,$(wildcard *c))

CC=clang

all: ${TARGETS}

clean:
	rm -rf *.klee *.bc *.ll

.SUFFIXES: .bc .klee .ll

.c.bc:
	${CC} -c -emit-llvm -g $<

.c.ll:
	${CC} -c -emit-llvm -g -S $<


.bc.klee:
	${KLEE_HOME}/bin/klee -search=dfs -output-dir=$@ ${EXTRA_OPTIONS} $<

