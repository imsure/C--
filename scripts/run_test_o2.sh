#!/bin/bash

## Run all the test cases with -O1 optimization.

compiler_path=../FrontEnd
#test_path=../Tests/codegen_tests_from_professor
test_path=../Tests/codeopt1_tests
tmp_asm="tmp.s"
tmp_output="output.txt"
tmp_output2="output2.txt"
test_counter=1
pass_counter=0
fail_counter=0

for cfile in $test_path/*.c
do
    output=$(echo $cfile | sed 's/\/test/\/OUTPUTS\/out/')
    output=$(echo $output | sed 's/\.c$//')
    $compiler_path/compile -O2 < $cfile > $tmp_asm
    spim -f $tmp_asm > $tmp_output
    sed '1 d' $tmp_output > $tmp_output2
    if diff -q "$tmp_output2" "$output";
    then
	pass_counter=$(( $pass_counter + 1 ))
    	echo "passed test-case $test_counter"
    else
	fail_counter=$(( $fail_counter + 1 ))
    	echo "faild test-case $test_counter"
    fi
    test_counter=$(( $test_counter + 1 ))
done

rm $tmp_asm $tmp_output $tmp_output2
echo
echo "$pass_counter test cases passed"
echo "$fail_counter test cases failed"

