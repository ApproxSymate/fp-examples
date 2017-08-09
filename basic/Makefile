KLEE_HOME=${HOME}/software/fp-analysis-klee/Release+Asserts

TARGETS=$(patsubst %.c,%.klee,$(wildcard *c))

CC=clang
CFLAGS=-I${KLEE_HOME}/include -I${KLEE_HOME}/../include

all: ${TARGETS}

clean:
	rm -rf *.klee *.dklee *.loop *.dloop *.bc *.ll

.SUFFIXES: .bc .klee .dklee .ll .loop .dloop

.c.bc:
	${CC} ${CFLAGS} -c -emit-llvm -g -o $*_123.bc $<
	opt -mem2reg < $*_123.bc > $@
	rm -f $*_123.bc

.bc.ll:
	llvm-dis $<

.bc.klee:
	if [ -z "$$OUTPUT_DIR" ] ; then \
		OUTPUT_DIR="$@" ; \
	fi ; \
	${KLEE_HOME}/bin/klee -search=dfs -output-dir="$$OUTPUT_DIR" $$EXTRA_OPTIONS -precision $<

.bc.dklee:
	EXTRA_OPTIONS="-debug-precision" OUTPUT_DIR="$@" make $*.klee

.bc.loop:
	EXTRA_OPTIONS="-loop-breaking" OUTPUT_DIR="$@" make $*.klee

.bc.dloop:
	EXTRA_OPTIONS="-loop-breaking -debug-precision" OUTPUT_DIR="$@" make $*.klee
