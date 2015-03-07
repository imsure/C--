main:
	Enter main  24 
	i = 0 
	res = 0 
	goto _L1
_L0:
	_tvar1 = res + i
	res = _tvar1 
	_tvar1 = 1 
	_tvar1 = i + _tvar1
	i = _tvar1 
_L1:
	_tvar0 = 10 
	if ( i < _tvar0 ) goto _L0
	goto _L2
_L2:
	i = 0 
	goto _L4
_L3:
	_tvar2 = res + i
	res = _tvar2 
	_tvar2 = 1 
	_tvar2 = i + _tvar2
	i = _tvar2 
_L4:
	_tvar1 = 10 
	if ( i < _tvar1 ) goto _L3
	goto _L5
_L5:
	i = 0 
	goto _L7
_L6:
	_tvar2 = res + i
	res = _tvar2 
	_tvar2 = 10 
	if ( i > _tvar2 ) goto _L9
	goto _L10
_L9:
	Param res 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 
_L10:
	_tvar3 = 1 
	_tvar3 = i + _tvar3
	i = _tvar3 
_L7:
	goto _L6
_L8:
	Return 

