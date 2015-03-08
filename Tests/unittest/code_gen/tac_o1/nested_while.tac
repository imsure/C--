main:
	Enter main  4 
	a = 0 
	LIM = 3 
	res = 0 
	goto _L1
_L0:
	b = 0 
	goto _L4
_L3:
	c = 0 
	goto _L7
_L6:
	d = 0 
	goto _L10
_L9:
	e = 0 
	goto _L13
_L12:
	_tvar0 = 1 
	_tvar0 = res + 1 
	res = _tvar0 
	_tvar0 = 1 
	_tvar0 = e + 1 
	e = _tvar0 
_L13:
	if ( e < LIM ) goto _L12
_L14:
	_tvar0 = 1 
	_tvar0 = d + 1 
	d = _tvar0 
_L10:
	if ( d < LIM ) goto _L9
_L11:
	_tvar0 = 1 
	_tvar0 = c + 1 
	c = _tvar0 
_L7:
	if ( c < LIM ) goto _L6
_L8:
	_tvar0 = 1 
	_tvar0 = b + 1 
	b = _tvar0 
_L4:
	if ( b < LIM ) goto _L3
_L5:
	_tvar0 = 1 
	_tvar0 = a + 1 
	a = _tvar0 
_L1:
	if ( a < LIM ) goto _L0
_L2:
	Param res 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

