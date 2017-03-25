LLVM_COMPILER=clang-3.4

%.klee: build
	time klee -output-dir=$< adpcm/src/$*.bc

build:
	(cd adpcm/src; make)

clean:
	rm -rf *.klee

realclean: clean
	(cd adpcm/src; make clean)
