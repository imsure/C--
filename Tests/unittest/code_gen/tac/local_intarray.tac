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
	Enter main  56 
	_tvar0 = 5 
	_tvar0 = _tvar0 * 4 
	_taddr0 = x + _tvar0
	_tvar0 = 4321 
	*_taddr0(int) = _tvar0 
	_tvar0 = 5 
	_tvar0 = _tvar0 * 4 
	_taddr1 = x + _tvar0
	y = *_taddr1(int) 
	Param y 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

