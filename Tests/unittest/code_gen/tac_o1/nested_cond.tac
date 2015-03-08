main:
	Enter main  4 
	a = 1 
	b = 2 
	c = 3 
	d = 4 
	e = 5 
	f = 6 
	if ( a >= b ) goto _L1
_L0:
	if ( b < c ) goto _L4
_L3:
	if ( c >= d ) goto _L7
_L6:
	if ( d == e ) goto _L10
_L9:
	if ( e >= f ) goto _L13
_L12:
	if ( g >= f ) goto _L16
_L15:
	if ( g >= a ) goto _L19
_L18:
	res = 1111 
	goto _L2
_L19:
	res = 2222 
_L20:
	goto _L2
_L16:
	res = 3333 
_L17:
	goto _L2
_L13:
	res = 4444 
_L14:
	goto _L2
_L10:
	res = 5555 
_L11:
	goto _L2
_L7:
	res = 6666 
_L8:
	goto _L2
_L4:
	res = 7777 
_L5:
	goto _L2
_L1:
	res = 8888 
_L2:
	Param res 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

