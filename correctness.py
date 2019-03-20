#!/usr/bin/env python2
# B136013
# check_correctness.py
#
import os
import math


dataList = [
    'output.dat100',
    'output.dat200',
    'output.dat300',
    'output.dat400',
    'output.dat500',
]

SRC_FOLDER = './src_gcc/'

currDataPathList = [
    SRC_FOLDER+dataList[0],
    SRC_FOLDER+dataList[1],
    SRC_FOLDER+dataList[2],
    SRC_FOLDER+dataList[3],
    SRC_FOLDER+dataList[4],
]

def isnan(value):
  try:
      return math.isnan(float(value))
  except:
      return False


def checkNan():
    for path in currDataPathList:
        f = open(path, 'r')

        for line in f:
            data = line.strip().split('  ')
            for number in data:
                if number != '' and isnan(number):
                    f.close()
                    return 0

        f.close()
        
    return 1


def compareFiles():
    initDataPathList = [
        './data/'+dataList[0],
        './data/'+dataList[1],
        './data/'+dataList[2],
        './data/'+dataList[3],
        './data/'+dataList[4],
    ]

    for i in range(5):
        command = os.popen('./test/diff-output ' + initDataPathList[i] + ' ' + currDataPathList[i])
        if command.read().strip() != 'max=0.000000':
            return 0
    return 1


def main():
    command = os.popen('make -C ./test clean')
    command.read()
    command = os.popen('make -C ./test diff-output')
    command.read()

    if checkNan() and compareFiles():
        print 'Pass'
    else:
        print 'Fail'


if __name__ == "__main__":
    main()
