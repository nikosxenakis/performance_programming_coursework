#!/bin/bash
#B136013
#
module load intel-compilers-17
make -C ./src clean;
make -C ./src MD;
make -C ./src MD output.dat;
