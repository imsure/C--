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
	_tvar0 = 1 
	_tvar0 = x + _tvar0
	Return _tvar0 

main:
	Enter main  8 
	y = 1 
	Param y 
	Call f  1 
	Retrieve _tvar1 
	x = _tvar1 
	Param x 
	Call f  1 
	Retrieve _tvar1 
	_tvar1 = x + _tvar1
	y = _tvar1 
	_tvar2 = 'Q' 
	Param _tvar2 
	Call f  1 
	Retrieve _tvar1 
	_tvar2 = y + _tvar1
	x = _tvar2 
	Param x 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

