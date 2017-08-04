# Numerical Precision Examples

This repository contains examples from various sources as a benchmark
suite for numerical precision. This suite is for use with KLEE for
numerical precision in https://github.com/fp-analysis/klee.

* The `basic` directory contains basic, mainly floating-point
  programs. Before running, please set the `KLEE_HOME` variable in
  `basic/Makefile` to an appropriate value. There are four alternative
  ways to run KLEE for numerical precision analysis, as follows:
  1. To run KLEE for numerical precision using default options,
     execute the following in the `basic` directory:
     ```
     make <program_name>.klee
     ```
     where `<program_name>` is the name of a C program file
     `basic/<program_name>.c`.
     
  2. To run KLEE for numerical precision using default options but
     with displaying of debugging information, execute the following
     in the `basic` directory:
     ```
     make <program_name>.dklee
     ```
     where `<program_name>` is the name of a C program file
     `basic/<program_name>.c`.
  3. To run KLEE for numerical precision with loop breaking, execute
     the following in the `basic` directory:
     ```
     make <program_name>.loop
     ```
     where `<program_name>` is the name of a C program file
     `basic/<program_name>.c`.
  
  4. To run KLEE for numerical precision with loop breaking and with
     displaying of debugging information, execute the following in the
     `basic` directory:
     ```
     make <program_name>.dloop
     ```
     where `<program_name>` is the name of a C program file
     `basic/<program_name>.c`.
  
* The `package` directory contains applications.
   * To build the bitcode files and run them using KLEE, first update
     the value of `LLVM_COMPILER` variable in `package/Makefile` to
     suit your system.
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
   * To remove the KLEE output directories and the built application
     package:
     ```
     make realclean
     ```
     
