#!/usr/bin/env python2
# B136013
# check_correctness.py
#
import os
import math


dataList = [
    'output_100.dat',
    'output_200.dat',
    'output_300.dat',
    'output_400.dat',
    'output_500.dat'
]

currDataPathList = [
    './data/'+dataList[0],
    './data/'+dataList[1],
    './data/'+dataList[2],
    './data/'+dataList[3],
    './data/'+dataList[4],
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
        './data/initial/'+dataList[0],
        './data/initial/'+dataList[1],
        './data/initial/'+dataList[2],
        './data/initial/'+dataList[3],
        './data/initial/'+dataList[4],
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
