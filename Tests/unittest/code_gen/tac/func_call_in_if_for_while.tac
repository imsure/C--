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

id:
	Enter id  0 
	Return x 

main:
	Enter main  76 
	_tvar0 = 123 
	x = _tvar0 
	_tvar2 = 3 
	Param _tvar2 
	Call id  1 
	Retrieve _tvar1 
	Param _tvar1 
	Call id  1 
	Retrieve _tvar0 
	_tvar6 = 4 
	Param _tvar6 
	Call id  1 
	Retrieve _tvar5 
	Param _tvar5 
	Call id  1 
	Retrieve _tvar4 
	Param _tvar4 
	Call id  1 
	Retrieve _tvar3 
	if ( _tvar0 > _tvar3 ) goto _L0
	goto _L1
_L0:
	_tvar7 = 321 
	x = _tvar7 
_L1:
	_tvar7 = 12 
	i = _tvar7 
	goto _L3
_L2:
	_tvar11 = 1 
	_tvar11 = x - _tvar11
	x = _tvar11 
	_tvar11 = 1 
	_tvar11 = i - _tvar11
	i = _tvar11 
_L3:
	Param i 
	Call id  1 
	Retrieve _tvar9 
	Param _tvar9 
	Call id  1 
	Retrieve _tvar8 
	Param _tvar8 
	Call id  1 
	Retrieve _tvar7 
	_tvar10 = 0 
	if ( _tvar7 > _tvar10 ) goto _L2
	goto _L4
_L4:
	_tvar12 = 0 
	Param _tvar12 
	Call id  1 
	Retrieve _tvar11 
	i = _tvar11 
	goto _L6
_L5:
	_tvar15 = 2 
	_tvar15 = x + _tvar15
	x = _tvar15 
	Param i 
	Call id  1 
	Retrieve _tvar15 
	_tvar16 = 1 
	_tvar15 = _tvar15 + _tvar16
	i = _tvar15 
_L6:
	Param i 
	Call id  1 
	Retrieve _tvar13 
	Param _tvar13 
	Call id  1 
	Retrieve _tvar12 
	_tvar14 = 6 
	if ( _tvar12 < _tvar14 ) goto _L5
	goto _L7
_L7:
	Param x 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

