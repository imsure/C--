	.text
print_int:
	li $v0, 1
	lw $a0, 0($sp)
	syscall
	jr $ra

	.text
print_string:
	li $v0, 4
	lw $a0, 0($sp)
	syscall
	jr $ra

f:
	Enter f  4 
	_tvar0 = x + y
	_tvar0 = _tvar0 + z
	Return _tvar0 

main:
	Enter main  20 
	_tvar2 = 111 
	_tvar3 = 222 
	_tvar4 = 0 
	Param _tvar2 
	Param _tvar3 
	Param _tvar4 
	Call f  3 
	Retrieve _tvar1 
	x = _tvar1 
	Param x 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

