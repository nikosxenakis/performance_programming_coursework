#!/bin/bash
#B136013
#

# FOLDER=./src_v1_remove_flags
# FOLDER=./src_v4_array_interchange
FOLDER=./src_v3_mem_alloc_kind
FOLDER=./src_clang

module load intel-compilers-17;
module load valgrind;
module load clang;

cd $FOLDER;

make clean;
make MD;

valgrind --tool=cachegrind --cachegrind-out-file=cachegrind_output.txt ./MD > memory_results.txt
cg_annotate --auto=yes cachegrind_output.txt > valgrind_analysis.txt

rm cachegrind_output.txt;

cd ..;
