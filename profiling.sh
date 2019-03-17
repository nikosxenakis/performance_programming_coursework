#!/bin/bash
#B136013
#

module load intel-compilers-17;
module load valgrind;

cd src;

make clean;
make MD_icc;

valgrind --tool=cachegrind --cachegrind-out-file=cachegrind_output.txt ./MD_icc
cg_annotate --auto=yes cachegrind_output.txt > valgrind_analysis.txt

rm cachegrind_output.txt;

cd ..;

# ./MD_gprof
# gprof -b MD_gprof gmon.out > analysis.txt


# module load intel-vtune-18/2018.4.0.573462
