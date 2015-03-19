f:
	Enter f  12 
	y = 1 
	goto _L1
_L0:
	_tvar1 = x * i
	x = _tvar1 
	_tvar1 = 2 * y
	y = _tvar1 
	_tvar1 = i - 1 
	i = _tvar1 
_L1:
	_tvar0 = 0 
	if ( i > _tvar0 ) goto _L0
_L2:
	Return y 

main:
	Enter main  12 
	x = 1 
	_tvar2 = 6 
	Param _tvar2 
	Call f  1 
	Retrieve _tvar1 
	a = _tvar1 
	_tvar2 = _tvar1 + x
	x = _tvar2 
	Param x 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

