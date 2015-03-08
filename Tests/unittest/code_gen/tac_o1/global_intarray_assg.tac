main:
	Enter main  24 
	_taddr0 = y + 28 
	*_taddr0(int) = 1234 
	_taddr2 = x + 0 
	_taddr1 = y + 28 
	*_taddr2(int) = *_taddr1(int) 
	_taddr3 = x + 0 
	u = *_taddr3(int) 
	Param u 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

