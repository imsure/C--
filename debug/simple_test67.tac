(0)copy:
(0)	Enter(saved regs:0x0) (0)copy  28 
(0)	(0)_tvar0 = 0 
(0)	(0)i = (0)_tvar0 
(0)	(0)_tvar0 = 0 
(0)	(0)i = (0)_tvar0 
(0)	goto _L1
(0)_L0:
(0)	(0)_tvar1 = (0)i * 1 
(0)	(0)_taddr2 = (0)b + (0)_tvar1
(0)	(0)_tvar1 = (0)i * 1 
(0)	(0)_taddr1 = (0)a + (0)_tvar1
(0)	(0)*_taddr2(char) = (0)*_taddr1(char) 
(0)	(0)_tvar1 = 1 
(0)	(0)_tvar1 = (0)i + (0)_tvar1
(0)	(0)i = (0)_tvar1 
(0)_L1:
(0)	(0)_tvar0 = (0)i * 1 
(0)	(0)_taddr0 = (0)a + (0)_tvar0
(0)	(0)_tvar0 = 0 
(0)	if ( (0)*_taddr0(char) > (0)_tvar0 ) goto _L0
(0)	goto _L2
(0)_L2:
(0)	(0)_tvar1 = (0)i * 1 
(0)	(0)_taddr3 = (0)b + (0)_tvar1
(0)	(0)_tvar1 = 0 
(0)	(0)*_taddr3(char) = (0)_tvar1 
(0)	Return (0)i 

(0)sum:
(0)	Enter(saved regs:0x0) (0)sum  24 
(0)	(0)_tvar1 = 0 
(0)	(0)i = (0)_tvar1 
(0)	(0)_tvar1 = 0 
(0)	(0)sum = (0)_tvar1 
(0)	goto _L4
(0)_L3:
(0)	(0)_tvar2 = (0)i * 1 
(0)	(0)_taddr5 = (0)b + (0)_tvar2
(0)	(0)_tvar2 = (0)sum + (0)*_taddr5(char) 
(0)	(0)sum = (0)_tvar2 
(0)	(0)_tvar2 = 1 
(0)	(0)_tvar2 = (0)i + (0)_tvar2
(0)	(0)i = (0)_tvar2 
(0)_L4:
(0)	(0)_tvar1 = (0)i * 1 
(0)	(0)_taddr4 = (0)b + (0)_tvar1
(0)	(0)_tvar1 = 0 
(0)	if ( (0)*_taddr4(char) > (0)_tvar1 ) goto _L3
(0)	goto _L5
(0)_L5:
(0)	Return (0)sum 

(0)main:
(0)	Enter(saved regs:0x0) (0)main  8 
(0)	_tstr0 = "hello world"
(0)	Param (0)_tstr0 
(0)	Param (0)x 
(0)	Call (0)copy  2 
(0)	Retrieve (0)_tvar2 
(0)	(0)y = (0)_tvar2 
(0)	Param (0)x 
(0)	Call (0)sum  1 
(0)	Retrieve (0)_tvar2 
(0)	(0)_tvar2 = (0)y + (0)_tvar2
(0)	(0)y = (0)_tvar2 
(0)	Param (0)y 
(0)	Call (0)print_int  1 
(0)	_tstr1 = "\n"
(0)	Param (0)_tstr1 
(0)	Call (0)print_string  1 
(0)	Return 

