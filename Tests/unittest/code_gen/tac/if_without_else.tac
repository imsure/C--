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
	_tvar0 = 5 
	n = _tvar0 
	_tvar0 = 10 
	if ( n > _tvar0 ) goto _L0
	goto _L1
_L0:
	_tvar1 = 10 
	_tvar1 = n - _tvar1
	n = _tvar1 
_L1:
	_tvar1 = n * n
	n = _tvar1 
	Return 

