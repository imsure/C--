acc:
	Enter acc  4 
	_tvar0 = y * x
	y = _tvar0 
	Return 

main:
	Enter main  16 
	_tvar0 = 1 
	y = _tvar0 
	_tvar0 = 7 
	n = _tvar0 
	goto _L1
_L0:
	Param n 
	Call acc  1 
	_tvar1 = 1 
	_tvar1 = n - _tvar1
	n = _tvar1 
_L1:
	_tvar0 = 0 
	if ( n > _tvar0 ) goto _L0
	goto _L2
_L2:
	Param y 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

