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
	Enter f  16 
	_tvar0 = 0 
	if ( u == _tvar0 ) goto _L0
	goto _L1
_L0:
	_tvar1 = 1 
	Return _tvar1 
	goto _L2
_L1:
	Param u 
	Call incr  1 
	_tvar3 = 1 
	_tvar3 = u - _tvar3
	Param _tvar3 
	Call f  1 
	Retrieve _tvar2 
	Return _tvar2 
_L2:
	Return 

incr:
	Enter incr  4 
	_tvar4 = x + u
	u = _tvar4 
	Return 

main:
	Enter main  12 
	_tvar4 = 1 
	u = _tvar4 
	_tvar5 = 6 
	Param _tvar5 
	Call f  1 
	Retrieve _tvar4 
	x = _tvar4 
	_tvar5 = u + x
	x = _tvar5 
	Param x 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

