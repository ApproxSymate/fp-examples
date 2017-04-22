EXTRA_OPTIONS=-precision -debug-precision

KLEE_HOME=${HOME}/software/klee/Release+Asserts

TARGETS=$(patsubst %.c,%.klee,$(wildcard *c))

CC=clang

all: ${TARGETS}

clean:
	rm -rf *.klee *.bc *.ll

.SUFFIXES: .bc .klee .ll

.c.bc:
	${CC} -c -emit-llvm -g -o $*_123.bc $<
	opt -mem2reg < $*_123.bc > $@
	rm -f $*_123.bc

.bc.ll:
	llvm-dis $<

.bc.klee:
	${KLEE_HOME}/bin/klee -search=dfs -output-dir=$@ ${EXTRA_OPTIONS} $<

