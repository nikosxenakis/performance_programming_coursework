module load valgrind;

cd src;
make clean;
make MD;

valgrind --tool=cachegrind --cachegrind-out-file=cachegrind_output.txt ./MD
cg_annotate --auto=yes cachegrind_output.txt > valgrind_analysis.txt

cd ..;



# ./MD_gprof
# gprof -b MD_gprof gmon.out > analysis.txt


# valgrind --tool=cachegrind --cachegrind-out-file=cachegrind_output.txt ./src/MD
# cg_annotate --auto=yes cachegrind_output.txt



# module load intel-vtune-18/2018.4.0.573462