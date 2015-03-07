main:
	Enter main  24 
	_tvar0 = 7 
	_tvar0 = _tvar0 * 4 
	_taddr0 = y + _tvar0
	_tvar0 = 1234 
	*_taddr0(int) = _tvar0 
	_tvar0 = 0 
	_tvar0 = _tvar0 * 4 
	_taddr2 = x + _tvar0
	_tvar0 = 7 
	_tvar0 = _tvar0 * 4 
	_taddr1 = y + _tvar0
	*_taddr2(int) = *_taddr1(int) 
	_tvar0 = 0 
	_tvar0 = _tvar0 * 4 
	_taddr3 = x + _tvar0
	u = *_taddr3(int) 
	Param u 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

