#!/bin/bash
#B136013
#

module load intel-compilers-17;
module load valgrind;

cd src;

make clean;
make MD;

valgrind --tool=cachegrind --cachegrind-out-file=cachegrind_output.txt ./MD
cg_annotate --auto=yes cachegrind_output.txt > valgrind_analysis.txt

rm cachegrind_output.txt;

cd ..;
