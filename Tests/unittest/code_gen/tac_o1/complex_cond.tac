main:
	Enter main  4 
	a = 1 
	b = 2 
	c = 3 
	d = 4 
	e = 5 
	f = 6 
	g = 7 
	h = 8 
	i = 9 
	j = 10 
	if ( a > b ) goto _L1
_L6:
	if ( b > c ) goto _L1
_L5:
	if ( c > d ) goto _L1
_L4:
	if ( d > e ) goto _L1
_L3:
	if ( e > f ) goto _L1
_L10:
	if ( f > g ) goto _L1
_L9:
	if ( g > h ) goto _L1
_L8:
	if ( h > i ) goto _L1
_L7:
	if ( i > j ) goto _L1
_L0:
	res = 1111 
	goto _L2
_L1:
	res = 2222 
_L2:
	Param res 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

