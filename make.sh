# use this file's commands to compile
icc -fast -c MD.c -o MD.o
icc -fast -c control.c -o control.o
icc MD.o control.o util.o -lm -lc -ldl -o MD