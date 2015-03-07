side_effect:
	Enter side_effect  8 
	_tvar0 = 1 
	_tvar1 = -_tvar0 
	flag = _tvar1 
	Return x 

main:
	Enter main  32 
	_tvar0 = 3 
	x = _tvar0 
	_tvar0 = 4 
	y = _tvar0 
	_tvar0 = 5 
	z = _tvar0 
	_tvar0 = 1 
	flag = _tvar0 
	_tvar0 = 1234 
	val = _tvar0 
	if ( x < y ) goto _L3
	goto _L1
_L3:
	if ( y > z ) goto _L2
	goto _L1
_L2:
	Param x 
	Call side_effect  1 
	Retrieve _tvar0 
	if ( _tvar0 < z ) goto _L0
	goto _L1
_L0:
	_tvar1 = 1 
	_tvar1 = x - _tvar1
	x = _tvar1 
_L1:
	_tvar1 = 0 
	if ( flag < _tvar1 ) goto _L4
	goto _L5
_L4:
	_tvar2 = 4321 
	val = _tvar2 
_L5:
	if ( x < y ) goto _L6
	goto _L9
_L9:
	if ( y > z ) goto _L6
	goto _L8
_L8:
	Param x 
	Call side_effect  1 
	Retrieve _tvar2 
	if ( _tvar2 < z ) goto _L6
	goto _L7
_L6:
	_tvar3 = 1 
	_tvar3 = x - _tvar3
	x = _tvar3 
_L7:
	_tvar3 = 0 
	if ( flag < _tvar3 ) goto _L10
	goto _L11
_L10:
	_tvar4 = 4321 
	val = _tvar4 
_L11:
	_tvar4 = x * val
	val = _tvar4 
	Param val 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

