#!/bin/bash
#B136013
#

module load intel-compilers-17;
make -C ./src clean;

make -C ./src run_icc;

echo "Test results:";
python correctness.py;
