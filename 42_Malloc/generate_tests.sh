#!/bin/sh

dir=correction_tests

gcc -o test0 "$dir/test0.c"
gcc -o test1 "$dir/test1.c"
gcc -o test2 "$dir/test2.c"
gcc -o test3 "$dir/test3.c"
gcc -o test4 "$dir/test4.c"
gcc -o test5 "$dir/test5.c"
gcc -o test6 "$dir/test6.c" -L. -lft_malloc
