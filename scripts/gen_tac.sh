#!/bin/bash

## Generate TAC from c files without optimization

compiler_path=/Users/shuoyang/codebase/cs553/C--/FrontEnd
cd ../Tests/unittest/code_gen/c

for cfile in *.c
do
    tacfile=$(echo $cfile | sed 's/\.c/\.tac/')
    $compiler_path/compile -TAC < $cfile > ../tac/$tacfile
done
