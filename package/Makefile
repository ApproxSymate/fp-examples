
EXTRA_OPTIONS=

LLVM_COMPILER=clang-3.4

%.klee: build
	time klee ${EXTRA_OPTIONS} -output-dir=$*.klee adpcm/src/$*.bc

build:
	(cd adpcm/src; LLVM_COMPILER='${LLVM_COMPILER}' make)

clean:
	rm -rf *.klee

realclean: clean
	(cd adpcm/src; make clean)
