add:
	Enter add  4 
	_tvar0 = x + y
	Return _tvar0 

main:
	Enter main  80 
	_tvar1 = 1 
	f = _tvar1 
	_tvar1 = 7 
	i = _tvar1 
	goto _L1
_L0:
	_tvar4 = 1 
	_tvar7 = 2 
	_tvar10 = 0 
	Param i 
	Param _tvar10 
	Call add  2 
	Retrieve _tvar9 
	_tvar11 = 1 
	Param _tvar9 
	Param _tvar11 
	Call add  2 
	Retrieve _tvar8 
	Param _tvar7 
	Param _tvar8 
	Call add  2 
	Retrieve _tvar6 
	_tvar12 = 5 
	_tvar13 = -_tvar12 
	Param _tvar6 
	Param _tvar13 
	Call add  2 
	Retrieve _tvar5 
	Param _tvar4 
	Param _tvar5 
	Call add  2 
	Retrieve _tvar3 
	_tvar13 = 1 
	Param _tvar3 
	Param _tvar13 
	Call add  2 
	Retrieve _tvar2 
	_tvar13 = f * _tvar2
	f = _tvar13 
	_tvar13 = 1 
	_tvar13 = i - _tvar13
	i = _tvar13 
_L1:
	_tvar1 = 0 
	if ( i > _tvar1 ) goto _L0
	goto _L2
_L2:
	Param f 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

