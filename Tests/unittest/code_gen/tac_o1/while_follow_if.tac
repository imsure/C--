main:
	Enter main  20 
	x = 123 
	_tvar0 = 123 
	if ( x != _tvar0 ) goto _L1
_L0:
	x = 321 
_L1:
	goto _L3
_L2:
	_tvar2 = 1 
	_tvar2 = x - _tvar2
	x = _tvar2 
_L3:
	_tvar1 = 0 
	if ( x > _tvar1 ) goto _L2
	goto _L4
_L4:
	Param x 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

