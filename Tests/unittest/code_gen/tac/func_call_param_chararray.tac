copy:
	Enter copy 
	_tvar0 = 0 
	i = _tvar0 
	_tvar0 = 0 
	i = _tvar0 
	goto _L1
_L0:
	_tvar1 = i * 1 
	_taddr2 = b + _tvar1
	_tvar1 = i * 1 
	_taddr1 = a + _tvar1
	*_taddr2(char) = *_taddr1(char) 
	_tvar1 = 1 
	_tvar1 = i + _tvar1
	i = _tvar1 
_L1:
	_tvar0 = i * 1 
	_taddr0 = a + _tvar0
	_tvar0 = 0 
	if ( *_taddr0(char) > _tvar0 ) goto _L0
	goto _L2
_L2:
	_tvar1 = i * 1 
	_taddr3 = b + _tvar1
	_tvar1 = 0 
	*_taddr3(char) = _tvar1 
	Return i 

sum:
	Enter sum 
	_tvar1 = 0 
	i = _tvar1 
	_tvar1 = 0 
	sum = _tvar1 
	goto _L4
_L3:
	_tvar2 = i * 1 
	_taddr5 = b + _tvar2
	_tvar2 = sum +
	sum = _tvar2 
	_tvar2 = 1 
	_tvar2 = i + _tvar2
	i = _tvar2 
_L4:
	_tvar1 = i * 1 
	_taddr4 = b + _tvar1
	_tvar1 = 0 
	if ( *_taddr4(char) > _tvar1 ) goto _L3
	goto _L5
_L5:
	Return sum 

main:
	Enter main 
	_tstr0 = "hello world"
	Param _tstr0 
	Param x 
	Call copy  2 
	Retrieve _tvar2 
	y = _tvar2 
	Param x 
	Call sum  1 
	Retrieve _tvar2 
	_tvar2 = y + _tvar2
	y = _tvar2 
	Param y 
	Call print_int  1 
	_tstr1 = "\n"
	Param _tstr1 
	Call print_string  1 
	Return 

