make clean; make MD_gprof
./MD_gprof
gprof -b MD_gprof gmon.out > analysis.txt


# valgrind --tool=cachegrind --cachegrind-out-file=cachegrind_output.txt ./MD_valgrind
# cg_annotate --auto=yes cachegrind_output.txt
