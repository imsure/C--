f:
	Enter f  4 
	_tvar0 = 12345 
	_tvar0 = x + _tvar0
	Return _tvar0 

main:
	Enter main  4 
	_tvar1 = 12345 
	x = _tvar1 
	Param x 
	Call f  1 
	Retrieve _tvar1 
	x = _tvar1 
	Param x 
	Call f  1 
	Retrieve _tvar1 
	_tvar1 = x + _tvar1
	x = _tvar1 
	Param x 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

