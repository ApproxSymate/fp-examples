
WLLVM_HOME=${HOME}/.local
KLEE_HOME=${HOME}/software/fp-analysis-klee

SYM_OPTIONS=-sym-stdin 60000

LLVM_COMPILER=clang

%.klee: build
	if [ "$*" = "memdjpeg" ] ; then \
		opt -mem2reg PhirePhly/memdjpeg.whole.bc > PhirePhly/memdjpeg.whole_123.bc ; \
		mv -f PhirePhly/memdjpeg.whole_123.bc PhirePhly/memdjpeg.whole.bc ; \
		time ${KLEE_HOME}/build/bin/klee -precision -output-dir=$*.klee PhirePhly/memdjpeg.whole.bc ; \
	else \
		opt -mem2reg adpcm/src/$*.bc > adpcm/src/$*_123.bc ; \
		mv -f adpcm/src/$*_123.bc adpcm/src/$*.bc ; \
		time ${KLEE_HOME}/build/bin/klee -precision -debug-precision -posix-runtime -output-dir=$*.klee adpcm/src/$*.bc ${SYM_OPTIONS} ; \
	fi

build:
	(cd adpcm/src; LLVM_COMPILER='${LLVM_COMPILER}' WLLVM_HOME=${WLLVM_HOME} KLEE_HOME=${KLEE_HOME} make)
	(cd PhirePhly; KLEE_HOME=${KLEE_HOME} make)

clean:
	rm -rf *.klee

realclean: clean
	(cd adpcm/src; make clean)
	(cd PhirePhly; make clean)
