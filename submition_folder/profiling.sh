#!/bin/bash
#B136013
#

FOLDER=./src

module load intel-compilers-17;
module load valgrind;

cd $FOLDER;

make clean;
make MD;

valgrind --tool=cachegrind --cachegrind-out-file=cachegrind_output.txt ./MD > memory_results.txt
cg_annotate --auto=yes cachegrind_output.txt > valgrind_analysis.txt

rm cachegrind_output.txt;

cd ..;
