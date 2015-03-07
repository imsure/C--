main:
	Enter main  136 
	_tvar0 = 4 
	_tvar0 = _tvar0 * 4 
	_taddr0 = x + _tvar0
	*_taddr0(int) = 1111 
	_tvar0 = 5 
	_tvar0 = _tvar0 * 4 
	_taddr1 = x + _tvar0
	*_taddr1(int) = 2222 
	_tvar0 = 6 
	_tvar0 = _tvar0 * 4 
	_taddr2 = x + _tvar0
	*_taddr2(int) = 3333 
	_tvar0 = 7 
	_tvar0 = _tvar0 * 4 
	_taddr3 = y + _tvar0
	*_taddr3(int) = 4444 
	_tvar0 = 8 
	_tvar0 = _tvar0 * 4 
	_taddr4 = y + _tvar0
	*_taddr4(int) = 5555 
	_tvar0 = 9 
	_tvar0 = _tvar0 * 4 
	_taddr5 = y + _tvar0
	*_taddr5(int) = 6666 
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

