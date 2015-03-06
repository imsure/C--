main:
	Enter main 
	_tvar0 = 1 
	n = _tvar0 
	goto _L1
_L0:
	_tvar1 = n * 1 
	_taddr0 = A + _tvar1
	*_taddr0(char) = n 
	_tvar1 = 1 
	_tvar1 = n + _tvar1
	n = _tvar1 
_L1:
	_tvar0 = 10 
	if ( n <= _tvar0 ) goto _L0
	goto _L2
_L2:
	_tvar1 = 1 
	n = _tvar1 
	Return 

