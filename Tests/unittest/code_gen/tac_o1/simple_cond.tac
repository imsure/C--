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
	Enter main  32 
	_tvar0 = 1 
	_tvar1 = 0 
	if ( _tvar0 > _tvar1 ) goto _L0
	goto _L1
_L0:
	res1 = 1111 
	goto _L2
_L1:
	res1 = 2222 
_L2:
	x = 1 
	_tvar2 = 1 
	_tvar3 = -_tvar2 
	y = _tvar3 
	if ( x > y ) goto _L3
	goto _L4
_L3:
	res2 = 3333 
	goto _L5
_L4:
	res2 = 4444 
_L5:
	Param res1 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Param res2 
	Call print_int  1 
	_tstr1 = "\n"
	Param _tstr1 
	Call print_string  1 
	Return 

