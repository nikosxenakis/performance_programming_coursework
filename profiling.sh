make clean; make MD_gprof
./MD_gprof
gprof -b MD_gprof gmon.out > analysis.txt
