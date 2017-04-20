
EXTRA_OPTIONS=-precision -debug-precision -posix-runtime

SYM_OPTIONS=-sym-stdin 60000

LLVM_COMPILER=clang

%.klee: build
	opt -mem2reg adpcm/src/$*.bc > adpcm/src/$*1.bc
	mv -f adpcm/src/$*1.bc adpcm/src/$*.bc
	time klee ${EXTRA_OPTIONS} -output-dir=$*.klee adpcm/src/$*.bc ${SYM_OPTIONS}

build:
	(cd adpcm/src; LLVM_COMPILER='${LLVM_COMPILER}' make)

clean:
	rm -rf *.klee

realclean: clean
	(cd adpcm/src; make clean)
