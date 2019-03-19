#!/bin/bash
#B136013
#

FOLDER=./src_v3_data_structures_i

module load intel-compilers-17;
make -C $FOLDER clean;

make -C $FOLDER run;

echo "Test results:";
python correctness.py;
