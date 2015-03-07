f:
	Enter f  4 
	_tvar0 = d * e
	_tvar0 = c + _tvar0
	_tvar0 = b * _tvar0
	_tvar0 = a + _tvar0
	Return _tvar0 

main:
	Enter main  36 
	_tvar1 = 'a' 
	y = _tvar1 
	_tvar1 = 'b' 
	z = _tvar1 
	_tvar2 = 1 
	_tvar3 = 2 
	_tvar4 = 3 
	_tvar5 = 4 
	_tvar6 = 5 
	Param _tvar2 
	Param _tvar3 
	Param _tvar4 
	Param _tvar5 
	Param _tvar6 
	Call f  5 
	Retrieve _tvar1 
	x = _tvar1 
	Param x 
	Param y 
	Param x 
	Param z 
	Param x 
	Call f  5 
	Retrieve _tvar6 
	x = _tvar6 
	Param x 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

