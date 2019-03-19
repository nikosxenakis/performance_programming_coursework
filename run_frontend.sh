#!/bin/bash
#B136013
#

FOLDER=./src_v10_memory_accesses

module load intel-compilers-17;
make -C $FOLDER clean;

make -C $FOLDER run;

echo "Test results:";
python correctness.py;
