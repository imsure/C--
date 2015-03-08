f:
	Enter f  4 
	_tvar0 = 12345 
	_tvar0 = x + 12345 
	Return _tvar0 

main:
	Enter main  4 
	x = 12345 
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

