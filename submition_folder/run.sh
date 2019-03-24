#!/bin/bash
#B136013
#

FOLDER=./src

module load intel-compilers-17;
module load gcc;

make -C $FOLDER clean;

make -C $FOLDER run;

echo "Test results:";
python correctness.py;
