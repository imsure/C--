main:
	Enter main 
	_tvar0 = 0 
	i = _tvar0 
	goto _L1
_L0:
	_tvar1 = i * 4 
	_taddr0 = x + _tvar1
	*_taddr0(int) = i 
	_tvar1 = 1 
	_tvar1 = i + _tvar1
	i = _tvar1 
_L1:
	_tvar0 = 5 
	if ( i < _tvar0 ) goto _L0
	goto _L2
_L2:
	_tvar1 = 123 
	res = _tvar1 
	goto _L4
_L3:
	_tvar1 = res * i
	res = _tvar1 
	_tvar1 = 1 
	_tvar1 = i - _tvar1
	i = _tvar1 
_L4:
	_tvar1 = 5 
	_tvar1 = i / _tvar1
	_tvar1 = _tvar1 * 4 
	_taddr1 = x + _tvar1
	_tvar1 = 4 
	_tvar1 = i / _tvar1
	_tvar1 = _tvar1 * 4 
	_taddr2 = x + _tvar1
	if ( *_taddr1(int) <= *_taddr1(int)  ) goto _L7
	goto _L3
_L7:
	_tvar1 = 4 
	_tvar1 = i / _tvar1
	_tvar1 = _tvar1 * 4 
	_taddr3 = x + _tvar1
	_tvar1 = 3 
	_tvar1 = i / _tvar1
	_tvar1 = _tvar1 * 4 
	_taddr4 = x + _tvar1
	if ( *_taddr3(int) <= *_taddr3(int)  ) goto _L6
	goto _L3
_L6:
	_tvar1 = 2 
	_tvar1 = i / _tvar1
	_tvar1 = _tvar1 * 4 
	_taddr5 = x + _tvar1
	_tvar1 = 3 
	_tvar1 = i / _tvar1
	_tvar1 = _tvar1 * 4 
	_taddr6 = x + _tvar1
	if ( *_taddr5(int) > *_taddr5(int)  ) goto _L3
	goto _L9
_L9:
	_tvar1 = 3 
	_tvar1 = i / _tvar1
	_tvar1 = _tvar1 * 4 
	_taddr7 = x + _tvar1
	_tvar1 = 4 
	_tvar1 = i / _tvar1
	_tvar1 = _tvar1 * 4 
	_taddr8 = x + _tvar1
	if ( *_taddr7(int) > *_taddr7(int)  ) goto _L3
	goto _L8
_L8:
	_tvar1 = 4 
	_tvar1 = i / _tvar1
	_tvar1 = _tvar1 * 4 
	_taddr9 = x + _tvar1
	_tvar1 = 5 
	_tvar1 = i / _tvar1
	_tvar1 = _tvar1 * 4 
	_taddr10 = x + _tvar1
	if ( *_taddr9(int) > *_taddr9(int)  ) goto _L3
	goto _L5
_L5:
	Param res 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

