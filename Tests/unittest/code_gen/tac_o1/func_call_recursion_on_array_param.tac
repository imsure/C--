sum:
	Enter sum  24 
	_tvar0 = i * 1 
	_taddr0 = x + _tvar0
	_tvar0 = 0 
	if ( *_taddr0(char) != _tvar0 ) goto _L1
_L0:
	_tvar1 = 0 
	Return _tvar1 
	goto _L2
_L1:
	_tvar2 = i * 1 
	_taddr1 = x + _tvar2
	_tvar3 = i + 1 
	Param x 
	Param _tvar3 
	Call sum  2 
	Retrieve _tvar2 
	_tvar3 = *_taddr1(char) + _tvar2
	Return _tvar3 
_L2:
	Return 

main:
	Enter main  12 
	_tstr0 = "hello world"
	_tvar5 = 0 
	Param _tstr0 
	Param _tvar5 
	Call sum  2 
	Retrieve _tvar4 
	x = _tvar4 
	Param x 
	Call print_int  1 
	_tstr1 = "\n"
	Param _tstr1 
	Call print_string  1 
	Return 

