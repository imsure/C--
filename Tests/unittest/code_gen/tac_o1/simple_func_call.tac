id:
	Enter id  0 
	Return x 

main:
	Enter main  16 
	f = 1 
	n = 7 
	goto _L1
_L0:
	Param n 
	Call id  1 
	Retrieve _tvar1 
	_tvar1 = _tvar1 * f
	f = _tvar1 
	_tvar1 = 1 
	_tvar1 = n - 1 
	n = _tvar1 
_L1:
	_tvar0 = 0 
	if ( n > _tvar0 ) goto _L0
_L2:
	Param f 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

