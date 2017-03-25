# Numerical Precision Examples

This repository contains examples from various sources as a benchmark suite for numerical precision.

* The `basic` directory contains basic, mainly floating-point programs.
* The `package` directory contains applications.
   * To build `adpcm` for running with KLEE, one needs LLVM compiler, e.g., `clang-3.4`.
   * Execute the following:
     ```
     cd package/adpcm/src
     LLVM_COMPILER=clang-3.4 make
     ```

