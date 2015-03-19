main:
	Enter main  52 
	i = 0 
	goto _L1
_L0:
	_tvar1 = i * 4 
	_taddr0 = x + _tvar1
	*_taddr0(int) = i 
	_tvar1 = i + 1 
	i = _tvar1 
_L1:
	_tvar0 = 5 
	if ( i < _tvar0 ) goto _L0
_L2:
	res = 123 
	goto _L4
_L3:
	_tvar1 = res * i
	res = _tvar1 
	_tvar1 = i - 1 
	i = _tvar1 
_L4:
	_tvar1 = i / 5 
	_tvar1 = _tvar1 * 4 
	_taddr1 = x + _tvar1
	_tvar1 = i / 4 
	_tvar1 = _tvar1 * 4 
	_taddr2 = x + _tvar1
	if ( *_taddr1(int) > *_taddr2(int)  ) goto _L3
_L7:
	_tvar1 = i / 4 
	_tvar1 = _tvar1 * 4 
	_taddr3 = x + _tvar1
	_tvar1 = i / 3 
	_tvar1 = _tvar1 * 4 
	_taddr4 = x + _tvar1
	if ( *_taddr3(int) > *_taddr4(int)  ) goto _L3
_L6:
	_tvar1 = i / 2 
	_tvar1 = _tvar1 * 4 
	_taddr5 = x + _tvar1
	_tvar1 = i / 3 
	_tvar1 = _tvar1 * 4 
	_taddr6 = x + _tvar1
	if ( *_taddr5(int) > *_taddr6(int)  ) goto _L3
_L9:
	_tvar1 = i / 3 
	_tvar1 = _tvar1 * 4 
	_taddr7 = x + _tvar1
	_tvar1 = i / 4 
	_tvar1 = _tvar1 * 4 
	_taddr8 = x + _tvar1
	if ( *_taddr7(int) > *_taddr8(int)  ) goto _L3
_L8:
	_tvar1 = i / 4 
	_tvar1 = _tvar1 * 4 
	_taddr9 = x + _tvar1
	_tvar1 = i / 5 
	_tvar1 = _tvar1 * 4 
	_taddr10 = x + _tvar1
	if ( *_taddr9(int) > *_taddr10(int)  ) goto _L3
_L5:
	Param res 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

