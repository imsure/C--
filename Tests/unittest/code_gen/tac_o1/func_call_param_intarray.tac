init:
	Enter init  12 
	i = 0 
	goto _L1
_L0:
	_tvar0 = i * 4 
	_taddr0 = x + _tvar0
	*_taddr0(int) = i 
	_tvar0 = 1 
	_tvar0 = i + _tvar0
	i = _tvar0 
_L1:
	if ( i < n ) goto _L0
_L2:
	Return n 

count:
	Enter count  16 
	c = 0 
	_tvar0 = 1 
	_tvar0 = n - _tvar0
	n = _tvar0 
	goto _L4
_L3:
	_tvar1 = n * 4 
	_taddr1 = x + _tvar1
	_tvar1 = c +
	c = _tvar1 
	_tvar1 = 1 
	_tvar1 = n - _tvar1
	n = _tvar1 
_L4:
	_tvar0 = 0 
	if ( n >= _tvar0 ) goto _L3
_L5:
	Return c 

main:
	Enter main  16 
	_tvar2 = 10 
	Param x 
	Param _tvar2 
	Call init  2 
	Retrieve _tvar1 
	z = _tvar1 
	_tvar3 = 10 
	Param x 
	Param _tvar3 
	Call count  2 
	Retrieve _tvar2 
	_tvar3 = z + _tvar2
	z = _tvar3 
	Param z 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

