main:
	Enter main  12 
	i = 0 
	goto _L1
_L0:
	Param i 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	_tvar1 = i + i
	_tvar2 = 1 
	_tvar1 = _tvar1 + _tvar2
	i = _tvar1 
_L1:
	_tvar0 = 100 
	if ( i < _tvar0 ) goto _L0
	goto _L2
_L2:
	Return 

