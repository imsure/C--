f:
	Enter f  24 
	_tvar0 = 1 
	if ( n > _tvar0 ) goto _L1
_L0:
	_tvar1 = 1 
	Return _tvar1 
	goto _L2
_L1:
	_tvar3 = 1 
	_tvar3 = n - 1 
	Param _tvar3 
	Call g  1 
	Retrieve _tvar2 
	_tvar5 = 2 
	_tvar5 = n - 2 
	Param _tvar5 
	Call f  1 
	Retrieve _tvar4 
	_tvar4 = _tvar2 + _tvar4
	Return _tvar4 
_L2:
	Return 

g:
	Enter g  24 
	_tvar5 = 1 
	if ( n > _tvar5 ) goto _L4
_L3:
	_tvar6 = 1 
	Return _tvar6 
	goto _L5
_L4:
	_tvar8 = 1 
	_tvar8 = n - 1 
	Param _tvar8 
	Call f  1 
	Retrieve _tvar7 
	_tvar10 = 2 
	_tvar10 = n - 2 
	Param _tvar10 
	Call g  1 
	Retrieve _tvar9 
	_tvar9 = _tvar7 + _tvar9
	Return _tvar9 
_L5:
	Return 

main:
	Enter main  12 
	_tvar11 = 5 
	Param _tvar11 
	Call f  1 
	Retrieve _tvar10 
	x = _tvar10 
	Param x 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

