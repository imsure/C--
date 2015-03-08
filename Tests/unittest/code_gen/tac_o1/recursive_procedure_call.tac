f:
	Enter f  16 
	_tvar0 = n * 1 
	_taddr0 = s + _tvar0
	_tvar0 = 0 
	if ( *_taddr0(char) != _tvar0 ) goto _L1
_L0:
	Return 
	goto _L2
_L1:
	_tvar1 = n * 1 
	_taddr1 = s + _tvar1
	_tvar1 = u + *_taddr1(char) 
	u = _tvar1 
	_tvar1 = 1 
	_tvar1 = n + 1 
	Param s 
	Param _tvar1 
	Call f  2 
_L2:
	Return 

main:
	Enter main  4 
	_tstr0 = "hello world"
	_tvar2 = 0 
	Param _tstr0 
	Param _tvar2 
	Call f  2 
	Param u 
	Call print_int  1 
	_tstr1 = "\n"
	Param _tstr1 
	Call print_string  1 
	Return 

