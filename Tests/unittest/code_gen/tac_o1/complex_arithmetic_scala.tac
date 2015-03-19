main:
	Enter main  16 
	x = 2 
	y = 3 
	z = 4 
	_tvar0 = 'a' * x
	a = _tvar0 
	_tvar0 = x + y
	_tvar0 = a / _tvar0
	_tvar0 = _tvar0 * z
	b = _tvar0 
	_tvar0 = x + y
	_tvar0 = a / _tvar0
	_tvar0 = _tvar0 * z
	_tvar0 = _tvar0 - a
	_tvar0 = _tvar0 + b
	c = _tvar0 
	Param c 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

