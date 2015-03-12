#!/bin/bash

## Generate MIPS assembly from c files without optimization.

compiler_path=/Users/shuoyang/codebase/cs553/C--/FrontEnd
cd ../Tests/unittest/code_gen/c

for cfile in *.c
do
    sfile=$(echo $cfile | sed 's/\.c/\.s/')
    $compiler_path/compile < $cfile > ../mips/$sfile
done
