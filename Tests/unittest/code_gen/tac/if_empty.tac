main:
	Enter main  12 
	_tvar0 = 5 
	n = _tvar0 
	_tvar0 = 10 
	if ( n > _tvar0 ) goto _L1
	goto _L0
_L0:
	_tvar1 = 1 
	_tvar1 = _tvar1 + n
	n = _tvar1 
_L1:
	_tvar1 = n * n
	n = _tvar1 
	Return 

