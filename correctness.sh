#!/bin/bash
#B136013
#
#define variables
DATA_FOLDER_INITIAL=./data/initial
DATA_FOLDER=./data
TEST_FOLDER=./test

$TEST_FOLDER/diff-output $DATA_FOLDER_INITIAL/output_100.dat $DATA_FOLDER/output_100.dat
$TEST_FOLDER/diff-output $DATA_FOLDER_INITIAL/output_200.dat $DATA_FOLDER/output_200.dat
$TEST_FOLDER/diff-output $DATA_FOLDER_INITIAL/output_300.dat $DATA_FOLDER/output_300.dat
$TEST_FOLDER/diff-output $DATA_FOLDER_INITIAL/output_400.dat $DATA_FOLDER/output_400.dat
$TEST_FOLDER/diff-output $DATA_FOLDER_INITIAL/output_500.dat $DATA_FOLDER/output_500.dat
