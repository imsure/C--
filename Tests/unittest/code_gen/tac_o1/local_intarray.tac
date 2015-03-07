main:
	Enter main  56 
	_tvar0 = 5 
	_tvar0 = _tvar0 * 4 
	_taddr0 = x + _tvar0
	*_taddr0(int) = 4321 
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

