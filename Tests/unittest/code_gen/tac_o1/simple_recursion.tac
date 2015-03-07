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

fact:
	Enter fact  16 
	_tvar0 = 0 
	if ( n == _tvar0 ) goto _L0
	goto _L1
_L0:
	_tvar1 = 1 
	Return _tvar1 
	goto _L2
_L1:
	_tvar3 = 1 
	_tvar3 = n - _tvar3
	Param _tvar3 
	Call fact  1 
	Retrieve _tvar2 
	_tvar3 = n * _tvar2
	Return _tvar3 
_L2:
	Return 

main:
	Enter main  12 
	_tvar5 = 7 
	Param _tvar5 
	Call fact  1 
	Retrieve _tvar4 
	x = _tvar4 
	Param x 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

