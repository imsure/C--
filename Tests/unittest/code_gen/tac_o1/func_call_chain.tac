add:
	Enter add  4 
	_tvar0 = x + y
	Return _tvar0 

main:
	Enter main  60 
	f = 1 
	i = 7 
	goto _L1
_L0:
	_tvar3 = 0 
	Param i 
	Param _tvar3 
	Call add  2 
	Retrieve _tvar2 
	a = _tvar2 
	_tvar4 = 1 
	Param a 
	Param _tvar4 
	Call add  2 
	Retrieve _tvar3 
	b = _tvar3 
	_tvar5 = 2 
	Param _tvar5 
	Param b 
	Call add  2 
	Retrieve _tvar4 
	c = _tvar4 
	_tvar6 = 5 
	_tvar7 = -5 
	Param c 
	Param _tvar7 
	Call add  2 
	Retrieve _tvar5 
	d = _tvar5 
	_tvar7 = 1 
	Param d 
	Param _tvar7 
	Call add  2 
	Retrieve _tvar6 
	e = _tvar6 
	_tvar8 = 1 
	Param e 
	Param _tvar8 
	Call add  2 
	Retrieve _tvar7 
	_tvar8 = f * _tvar7
	f = _tvar8 
	_tvar8 = i - 1 
	i = _tvar8 
_L1:
	_tvar1 = 0 
	if ( i > _tvar1 ) goto _L0
_L2:
	Param f 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

