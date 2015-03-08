main:
	Enter main  100 
	_taddr0 = x + 0 
	*_taddr0(int) = 0 
	_taddr1 = y + 0 
	*_taddr1(char) = 1 
	_taddr2 = x + 4 
	*_taddr2(int) = 1 
	_taddr3 = y + 1 
	*_taddr3(char) = 2 
	_taddr4 = x + 8 
	*_taddr4(int) = 2 
	_taddr5 = y + 2 
	*_taddr5(char) = 3 
	_taddr6 = x + 12 
	*_taddr6(int) = 3 
	_taddr7 = y + 3 
	*_taddr7(char) = 4 
	_taddr8 = x + 16 
	*_taddr8(int) = 4 
	_taddr9 = y + 4 
	*_taddr9(char) = 55 
	_tvar0 = 2 
	_taddr10 = x + 4 
	_tvar0 = 2 * *_taddr10(int) 
	_tvar1 = 1 
	_tvar0 = _tvar0 - 1 
	_tvar0 = _tvar0 * 4 
	_taddr11 = x + _tvar0
	_taddr12 = y + 4 
	_taddr13 = x + 8 
	_taddr14 = y + 0 
	_tvar0 = *_taddr13(int) + *_taddr14(char) 
	_tvar0 = _tvar0 * 1 
	_taddr15 = y + _tvar0
	_taddr16 = x + 4 
	_tvar0 = *_taddr15(char) + *_taddr16(int) 
	_tvar0 = *_taddr12(char) / _tvar0
	_tvar0 = *_taddr11(int) + _tvar0
	u = _tvar0 
	Param u 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

