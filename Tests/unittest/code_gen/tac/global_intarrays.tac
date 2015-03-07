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
	_tvar0 = 4 
	_tvar0 = _tvar0 * 4 
	_taddr0 = x + _tvar0
	_tvar0 = 111111 
	*_taddr0(int) = _tvar0 
	_tvar0 = 5 
	_tvar0 = _tvar0 * 4 
	_taddr1 = x + _tvar0
	_tvar0 = 222222 
	*_taddr1(int) = _tvar0 
	_tvar0 = 6 
	_tvar0 = _tvar0 * 4 
	_taddr2 = x + _tvar0
	_tvar0 = 333333 
	*_taddr2(int) = _tvar0 
	_tvar0 = 7 
	_tvar0 = _tvar0 * 4 
	_taddr3 = y + _tvar0
	_tvar0 = 444444 
	*_taddr3(int) = _tvar0 
	_tvar0 = 8 
	_tvar0 = _tvar0 * 4 
	_taddr4 = y + _tvar0
	_tvar0 = 555555 
	*_taddr4(int) = _tvar0 
	_tvar0 = 9 
	_tvar0 = _tvar0 * 4 
	_taddr5 = y + _tvar0
	_tvar0 = 666666 
	*_taddr5(int) = _tvar0 
	_tvar0 = 4 
	_tvar0 = _tvar0 * 4 
	_taddr6 = x + _tvar0
	u = *_taddr6(int) 
	Param u 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	_tvar0 = 5 
	_tvar0 = _tvar0 * 4 
	_taddr7 = x + _tvar0
	u = *_taddr7(int) 
	Param u 
	Call print_int  1 
	_tstr1 = "\n"
	Param _tstr1 
	Call print_string  1 
	_tvar0 = 6 
	_tvar0 = _tvar0 * 4 
	_taddr8 = x + _tvar0
	u = *_taddr8(int) 
	Param u 
	Call print_int  1 
	_tstr2 = "\n"
	Param _tstr2 
	Call print_string  1 
	_tvar0 = 7 
	_tvar0 = _tvar0 * 4 
	_taddr9 = y + _tvar0
	u = *_taddr9(int) 
	Param u 
	Call print_int  1 
	_tstr3 = "\n"
	Param _tstr3 
	Call print_string  1 
	_tvar0 = 8 
	_tvar0 = _tvar0 * 4 
	_taddr10 = y + _tvar0
	u = *_taddr10(int) 
	Param u 
	Call print_int  1 
	_tstr4 = "\n"
	Param _tstr4 
	Call print_string  1 
	_tvar0 = 9 
	_tvar0 = _tvar0 * 4 
	_taddr11 = y + _tvar0
	u = *_taddr11(int) 
	Param u 
	Call print_int  1 
	_tstr5 = "\n"
	Param _tstr5 
	Call print_string  1 
	Return 

