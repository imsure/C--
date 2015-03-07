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

main:
	Enter main  8 
	_tvar0 = 345 
	x = _tvar0 
	_tvar0 = 10 
	y = _tvar0 
	_tvar0 = x - y
	x = _tvar0 
	_tvar0 = 2 
	_tvar1 = -_tvar0 
	y = _tvar1 
	_tvar0 = x + y
	x = _tvar0 
	_tvar0 = x / y
	z = _tvar0 
	_tvar0 = z * y
	u = _tvar0 
	Param x 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Param y 
	Call print_int  1 
	_tstr1 = "\n"
	Param _tstr1 
	Call print_string  1 
	Param z 
	Call print_int  1 
	_tstr2 = "\n"
	Param _tstr2 
	Call print_string  1 
	Param u 
	Call print_int  1 
	_tstr3 = "\n"
	Param _tstr3 
	Call print_string  1 
	Return 

