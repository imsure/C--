main:
	Enter main  44 
	i = 0 
	res = 123 
	goto _L1
_L0:
	j = 0 
	goto _L4
_L3:
	_tvar2 = i + j
	_tvar3 = 2 
	_tvar2 = _tvar2 / _tvar3
	k = _tvar2 
	if ( k <= i ) goto _L7
_L6:
	a = 0 
	goto _L9
_L8:
	_tvar3 = a + k
	_tvar4 = 2 
	_tvar3 = _tvar3 / _tvar4
	b = _tvar3 
	if ( b <= j ) goto _L12
_L11:
	_tvar3 = res + b
	res = _tvar3 
	goto _L13
_L12:
	_tvar3 = res + k
	res = _tvar3 
_L13:
	_tvar3 = 1 
	_tvar3 = a + _tvar3
	a = _tvar3 
_L9:
	_tvar2 = 5 
	if ( a < _tvar2 ) goto _L8
_L10:
_L7:
	_tvar3 = 1 
	_tvar3 = j + _tvar3
	j = _tvar3 
_L4:
	_tvar1 = 5 
	if ( j < _tvar1 ) goto _L3
_L5:
	_tvar3 = 1 
	_tvar3 = i + _tvar3
	i = _tvar3 
_L1:
	_tvar0 = 5 
	if ( i < _tvar0 ) goto _L0
_L2:
	Param res 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

