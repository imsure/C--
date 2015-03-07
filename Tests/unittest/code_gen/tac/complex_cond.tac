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
	_tvar0 = 1 
	a = _tvar0 
	_tvar0 = 2 
	b = _tvar0 
	_tvar0 = 3 
	c = _tvar0 
	_tvar0 = 4 
	d = _tvar0 
	_tvar0 = 5 
	e = _tvar0 
	_tvar0 = 6 
	f = _tvar0 
	_tvar0 = 7 
	g = _tvar0 
	_tvar0 = 8 
	h = _tvar0 
	_tvar0 = 9 
	i = _tvar0 
	_tvar0 = 10 
	j = _tvar0 
	if ( a <= b ) goto _L6
	goto _L1
_L6:
	if ( b <= c ) goto _L5
	goto _L1
_L5:
	if ( c <= d ) goto _L4
	goto _L1
_L4:
	if ( d <= e ) goto _L3
	goto _L1
_L3:
	if ( e > f ) goto _L1
	goto _L10
_L10:
	if ( f > g ) goto _L1
	goto _L9
_L9:
	if ( g > h ) goto _L1
	goto _L8
_L8:
	if ( h > i ) goto _L1
	goto _L7
_L7:
	if ( i > j ) goto _L1
	goto _L0
_L0:
	_tvar0 = 1111 
	res = _tvar0 
	goto _L2
_L1:
	_tvar0 = 2222 
	res = _tvar0 
_L2:
	Param res 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

