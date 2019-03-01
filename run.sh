#!/bin/bash
#B136013
#
make -C ./src clean;
make -C ./src MD;
make -C ./src MD output.dat;
