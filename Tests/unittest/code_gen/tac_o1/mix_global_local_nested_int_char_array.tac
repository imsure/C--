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
	Enter main  108 
	_tvar0 = 0 
	_tvar0 = _tvar0 * 4 
	_taddr0 = x + _tvar0
	*_taddr0(int) = 0 
	_tvar0 = 0 
	_tvar0 = _tvar0 * 1 
	_taddr1 = y + _tvar0
	*_taddr1(char) = 1 
	_tvar0 = 1 
	_tvar0 = _tvar0 * 4 
	_taddr2 = x + _tvar0
	*_taddr2(int) = 1 
	_tvar0 = 1 
	_tvar0 = _tvar0 * 1 
	_taddr3 = y + _tvar0
	*_taddr3(char) = 2 
	_tvar0 = 2 
	_tvar0 = _tvar0 * 4 
	_taddr4 = x + _tvar0
	*_taddr4(int) = 2 
	_tvar0 = 2 
	_tvar0 = _tvar0 * 1 
	_taddr5 = y + _tvar0
	*_taddr5(char) = 3 
	_tvar0 = 3 
	_tvar0 = _tvar0 * 4 
	_taddr6 = x + _tvar0
	*_taddr6(int) = 3 
	_tvar0 = 3 
	_tvar0 = _tvar0 * 1 
	_taddr7 = y + _tvar0
	*_taddr7(char) = 4 
	_tvar0 = 4 
	_tvar0 = _tvar0 * 4 
	_taddr8 = x + _tvar0
	*_taddr8(int) = 4 
	_tvar0 = 4 
	_tvar0 = _tvar0 * 1 
	_taddr9 = y + _tvar0
	*_taddr9(char) = 55 
	_tvar0 = 0 
	_tvar0 = _tvar0 * 4 
	_taddr10 = x + _tvar0
	_tvar0 = *_taddr10(int) * 1 
	_taddr11 = y + _tvar0
	_tvar0 = *_taddr11(char) * 4 
	_taddr12 = x + _tvar0
	_tvar0 = *_taddr12(int) * 1 
	_taddr13 = y + _tvar0
	_tvar0 = *_taddr13(char) * 4 
	_taddr14 = x + _tvar0
	_tvar0 = *_taddr14(int) * 1 
	_taddr15 = y + _tvar0
	_tvar0 = *_taddr15(char) * 4 
	_taddr16 = x + _tvar0
	_tvar0 = *_taddr16(int) * 1 
	_taddr17 = y + _tvar0
	_tvar0 = *_taddr17(char) * 4 
	_taddr18 = x + _tvar0
	_tvar0 = *_taddr18(int) * 1 
	_taddr19 = y + _tvar0
	u = *_taddr19(char) 
	Param u 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

