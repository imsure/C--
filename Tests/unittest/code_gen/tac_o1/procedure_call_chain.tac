add:
	Enter add  4 
	_tvar0 = x + y
	y = _tvar0 
	Return 

main:
	Enter main  36 
	f = 1 
	i = 7 
	goto _L1
_L0:
	y = i 
	_tvar1 = 0 
	Param _tvar1 
	Call add  1 
	_tvar2 = 1 
	Param _tvar2 
	Call add  1 
	_tvar3 = 2 
	Param _tvar3 
	Call add  1 
	_tvar4 = 5 
	_tvar5 = -5 
	Param _tvar5 
	Call add  1 
	_tvar5 = 2 
	Param _tvar5 
	Call add  1 
	_tvar6 = f * y
	f = _tvar6 
	_tvar6 = i - 1 
	i = _tvar6 
_L1:
	_tvar0 = 0 
	if ( i > _tvar0 ) goto _L0
_L2:
	Param f 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

