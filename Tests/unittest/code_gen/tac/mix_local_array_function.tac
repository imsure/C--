id:
	Enter id  0 
	Return x 

main:
	Enter main  148 
	_tvar0 = 0 
	i = _tvar0 
	goto _L1
_L0:
	_tvar1 = i * 4 
	_taddr0 = x + _tvar1
	*_taddr0(int) = i 
	_tvar1 = 1 
	_tvar1 = i + _tvar1
	i = _tvar1 
_L1:
	_tvar0 = 10 
	if ( i < _tvar0 ) goto _L0
	goto _L2
_L2:
	_tvar5 = 5 
	Param _tvar5 
	Call id  1 
	Retrieve _tvar4 
	_tvar5 = _tvar4 * 4 
	_taddr1 = x + _tvar5
	Param *_taddr1(int) 
	Call id  1 
	Retrieve _tvar3 
	_tvar4 = _tvar3 * 4 
	_taddr2 = x + _tvar4
	Param *_taddr2(int) 
	Call id  1 
	Retrieve _tvar2 
	_tvar3 = _tvar2 * 4 
	_taddr3 = x + _tvar3
	Param *_taddr3(int) 
	Call id  1 
	Retrieve _tvar1 
	_tvar2 = _tvar1 * 4 
	_taddr4 = x + _tvar2
	res = *_taddr4(int) 
	_tvar6 = 0 
	Param _tvar6 
	Call id  1 
	Retrieve _tvar5 
	_tvar7 = 1 
	_tvar6 = _tvar5 + _tvar7
	_tvar6 = _tvar6 * 4 
	_taddr5 = x + _tvar6
	_tvar6 = 1 
	_tvar6 = *_taddr5(int) + _tvar6
	Param _tvar6 
	Call id  1 
	Retrieve _tvar4 
	_tvar7 = 1 
	_tvar6 = _tvar4 + _tvar7
	_tvar6 = _tvar6 * 4 
	_taddr6 = x + _tvar6
	_tvar6 = 1 
	_tvar6 = *_taddr6(int) + _tvar6
	Param _tvar6 
	Call id  1 
	Retrieve _tvar3 
	_tvar7 = 1 
	_tvar6 = _tvar3 + _tvar7
	_tvar6 = _tvar6 * 4 
	_taddr7 = x + _tvar6
	_tvar6 = 1 
	_tvar6 = *_taddr7(int) + _tvar6
	Param _tvar6 
	Call id  1 
	Retrieve _tvar2 
	_tvar7 = 1 
	_tvar6 = _tvar2 + _tvar7
	_tvar6 = _tvar6 * 4 
	_taddr8 = x + _tvar6
	_tvar2 = 1 
	_tvar2 = res + _tvar2
	*_taddr8(int) = _tvar2 
	_tvar10 = 0 
	Param _tvar10 
	Call id  1 
	Retrieve _tvar9 
	_tvar11 = 1 
	_tvar10 = _tvar9 + _tvar11
	_tvar10 = _tvar10 * 4 
	_taddr9 = x + _tvar10
	_tvar10 = 1 
	_tvar10 = *_taddr9(int) + _tvar10
	Param _tvar10 
	Call id  1 
	Retrieve _tvar8 
	_tvar11 = 1 
	_tvar10 = _tvar8 + _tvar11
	_tvar10 = _tvar10 * 4 
	_taddr10 = x + _tvar10
	_tvar10 = 1 
	_tvar10 = *_taddr10(int) + _tvar10
	Param _tvar10 
	Call id  1 
	Retrieve _tvar7 
	_tvar11 = 1 
	_tvar10 = _tvar7 + _tvar11
	_tvar10 = _tvar10 * 4 
	_taddr11 = x + _tvar10
	_tvar10 = 1 
	_tvar10 = *_taddr11(int) + _tvar10
	Param _tvar10 
	Call id  1 
	Retrieve _tvar6 
	_tvar11 = 1 
	_tvar10 = _tvar6 + _tvar11
	_tvar10 = _tvar10 * 4 
	_taddr12 = x + _tvar10
	res = *_taddr12(int) 
	Param res 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

