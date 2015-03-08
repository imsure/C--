main:
	Enter main  136 
	_taddr0 = x + 16 
	*_taddr0(int) = 1111 
	_taddr1 = x + 20 
	*_taddr1(int) = 2222 
	_taddr2 = x + 24 
	*_taddr2(int) = 3333 
	_taddr3 = y + 28 
	*_taddr3(int) = 4444 
	_taddr4 = y + 32 
	*_taddr4(int) = 5555 
	_taddr5 = y + 36 
	*_taddr5(int) = 6666 
	_taddr6 = x + 16 
	u = *_taddr6(int) 
	Param u 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	_taddr7 = x + 20 
	u = *_taddr7(int) 
	Param u 
	Call print_int  1 
	_tstr1 = "\n"
	Param _tstr1 
	Call print_string  1 
	_taddr8 = x + 24 
	u = *_taddr8(int) 
	Param u 
	Call print_int  1 
	_tstr2 = "\n"
	Param _tstr2 
	Call print_string  1 
	_taddr9 = y + 28 
	u = *_taddr9(int) 
	Param u 
	Call print_int  1 
	_tstr3 = "\n"
	Param _tstr3 
	Call print_string  1 
	_taddr10 = y + 32 
	u = *_taddr10(int) 
	Param u 
	Call print_int  1 
	_tstr4 = "\n"
	Param _tstr4 
	Call print_string  1 
	_taddr11 = y + 36 
	u = *_taddr11(int) 
	Param u 
	Call print_int  1 
	_tstr5 = "\n"
	Param _tstr5 
	Call print_string  1 
	Return 

