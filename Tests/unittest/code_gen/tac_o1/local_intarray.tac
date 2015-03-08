main:
	Enter main  56 
	_taddr0 = x + 20 
	*_taddr0(int) = 4321 
	_taddr1 = x + 20 
	y = *_taddr1(int) 
	Param y 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

