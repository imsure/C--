main:
	Enter main 
	_tvar0 = 1 
	a = _tvar0 
	_tvar0 = 2 
	b = _tvar0 
	_tvar0 = 3 
	c = _tvar0 
	_tvar0 = 4 
	d = _tvar0 
	_tvar0 = 5 
	e = _tvar0 
	_tvar0 = 6 
	f = _tvar0 
	if ( a < b ) goto _L0
	goto _L1
_L0:
	if ( b >= c ) goto _L3
	goto _L4
_L3:
	if ( c < d ) goto _L6
	goto _L7
_L6:
	if ( d == e ) goto _L10
	goto _L9
_L9:
	if ( e < f ) goto _L12
	goto _L13
_L12:
	if ( g < f ) goto _L15
	goto _L16
_L15:
	if ( g < a ) goto _L18
	goto _L19
_L18:
	_tvar0 = 1111 
	res = _tvar0 
	goto _L20
_L19:
	_tvar0 = 2222 
	res = _tvar0 
_L20:
	goto _L17
_L16:
	_tvar0 = 3333 
	res = _tvar0 
_L17:
	goto _L14
_L13:
	_tvar0 = 4444 
	res = _tvar0 
_L14:
	goto _L11
_L10:
	_tvar0 = 5555 
	res = _tvar0 
_L11:
	goto _L8
_L7:
	_tvar0 = 6666 
	res = _tvar0 
_L8:
	goto _L5
_L4:
	_tvar0 = 7777 
	res = _tvar0 
_L5:
	goto _L2
_L1:
	_tvar0 = 8888 
	res = _tvar0 
_L2:
	Param res 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

