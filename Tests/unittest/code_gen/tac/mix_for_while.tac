main:
	Enter main 
	_tvar0 = 0 
	res = _tvar0 
	_tvar0 = 0 
	i = _tvar0 
	goto _L1
_L0:
	_tvar1 = 0 
	j = _tvar1 
	goto _L4
_L3:
	_tvar2 = 0 
	k = _tvar2 
	goto _L7
_L6:
	_tvar3 = i + j
	_tvar3 = _tvar3 + k
	_tvar4 = 3 
	_tvar3 = _tvar3 / _tvar4
	_tvar3 = res + _tvar3
	res = _tvar3 
	_tvar3 = 3 
	_tvar3 = k + _tvar3
	k = _tvar3 
_L7:
	_tvar2 = 15 
	if ( k < _tvar2 ) goto _L6
	goto _L8
_L8:
	_tvar3 = 2 
	_tvar3 = j + _tvar3
	j = _tvar3 
_L4:
	_tvar1 = 10 
	if ( j < _tvar1 ) goto _L3
	goto _L5
_L5:
	_tvar3 = 1 
	_tvar3 = i + _tvar3
	i = _tvar3 
_L1:
	_tvar0 = 5 
	if ( i < _tvar0 ) goto _L0
	goto _L2
_L2:
	Param res 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

