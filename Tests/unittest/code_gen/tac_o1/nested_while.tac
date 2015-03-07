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
	Enter main  4 
	a = 0 
	LIM = 3 
	res = 0 
	goto _L1
_L0:
	b = 0 
	goto _L4
_L3:
	c = 0 
	goto _L7
_L6:
	d = 0 
	goto _L10
_L9:
	e = 0 
	goto _L13
_L12:
	_tvar0 = 1 
	_tvar0 = res + _tvar0
	res = _tvar0 
	_tvar0 = 1 
	_tvar0 = e + _tvar0
	e = _tvar0 
_L13:
	if ( e < LIM ) goto _L12
	goto _L14
_L14:
	_tvar0 = 1 
	_tvar0 = d + _tvar0
	d = _tvar0 
_L10:
	if ( d < LIM ) goto _L9
	goto _L11
_L11:
	_tvar0 = 1 
	_tvar0 = c + _tvar0
	c = _tvar0 
_L7:
	if ( c < LIM ) goto _L6
	goto _L8
_L8:
	_tvar0 = 1 
	_tvar0 = b + _tvar0
	b = _tvar0 
_L4:
	if ( b < LIM ) goto _L3
	goto _L5
_L5:
	_tvar0 = 1 
	_tvar0 = a + _tvar0
	a = _tvar0 
_L1:
	if ( a < LIM ) goto _L0
	goto _L2
_L2:
	Param res 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

