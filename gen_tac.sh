#!/bin/bash

## Generate TAC from c files.

compiler_path=/Users/shuoyang/codebase/cs553/C--/FrontEnd
cd ./Tests/unittest/code_gen/c

for cfile in *.c
do
    tacfile=$(echo $cfile | sed 's/\.c/\.tac/')
    $compiler_path/compile < $cfile > ../tac/$tacfile
done
