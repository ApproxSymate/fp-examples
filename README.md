# Numerical Precision Examples

This repository contains examples from various sources as a benchmark suite for numerical precision.

* The `basic` directory contains basic, mainly floating-point programs. Say
  ```
  make <program_name>.klee
  ```
  where `<program_name>` is the name of a C program file `basic/<program_name>.c` to have KLEE symbolically execute the program.
* The `package` directory contains applications.
   * To build the bitcode files and run them using KLEE, first update the value of `LLVM_COMPILER` variable in `package/Makefile` to suit your system.
   * Change to the `package` directory.
     ```
     cd package
     ```
   * To run the the program bitcode using KLEE, say:
     ```
     make <program_name>.klee
     ```
     where `<program_name>` is either `rawcaudio`, `rawdaudio`, or `timing`.
   * To remove the KLEE output directories:
     ```
     make clean
     ```
   * To remove the KLEE output directories and the built application package:
     ```
     make realclean
     ```
     
