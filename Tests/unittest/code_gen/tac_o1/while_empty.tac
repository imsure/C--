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
	Enter main  12 
	n = 10 
	goto _L1
_L0:
_L1:
	_tvar0 = 10 
	if ( n < _tvar0 ) goto _L0
	goto _L2
_L2:
	_tvar1 = 4 
	_tvar1 = _tvar1 - n
	n = _tvar1 
	Return 

