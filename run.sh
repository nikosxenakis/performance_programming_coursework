#!/bin/bash
#B136013
#

FOLDER=./src_v12_vectorisation
FOLDER=./src_clang

module load intel-compilers-17;
module load gcc;
module load clang;

make -C $FOLDER clean;

cd src;

./MD 1;

cd ..;

echo "Test results:";
python correctness.py;
