main:
	Enter main 
	_tvar0 = 1 
	_tvar1 = 0 
	if ( _tvar0 > _tvar1 ) goto _L0
	goto _L1
_L0:
	_tvar2 = 1111 
	res1 = _tvar2 
	goto _L2
_L1:
	_tvar2 = 2222 
	res1 = _tvar2 
_L2:
	_tvar2 = 1 
	x = _tvar2 
	_tvar2 = 1 
	_tvar3 = -_tvar2 
	y = _tvar3 
	if ( x > y ) goto _L3
	goto _L4
_L3:
	_tvar2 = 3333 
	res2 = _tvar2 
	goto _L5
_L4:
	_tvar2 = 4444 
	res2 = _tvar2 
_L5:
	Param res1 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Param res2 
	Call print_int  1 
	_tstr1 = "\n"
	Param _tstr1 
	Call print_string  1 
	Return 

