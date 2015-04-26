(0)copy:
(0)	Enter(saved regs:0x0) (0)copy  40 
(4)	(2)i = 0 
(0)	goto _L1
(0)_L0:
(5)	(4)_tvar1 = (4)_tvar1 
(6)	(0)_taddr2 = (0)b + (4)_tvar1
(7)	(4)_tvar1 = (5)_tvar3 
(8)	(0)_taddr1 = (0)a + (4)_tvar1
(9)	(0)*_taddr2(char) = (0)*_taddr1(char) 
(11)	(4)_tvar1 = (2)i + 1 
(12)	(2)i = (4)_tvar1 
(0)_L1:
(13)	(6)_tvar8 = (2)i * 1 
(24)	(5)_tvar3 = (6)_tvar8 
(23)	(4)_tvar1 = (5)_tvar3 
(22)	(1)_tvar0 = (4)_tvar1 
(14)	(0)_taddr0 = (0)a + (1)_tvar0
(16)	if ( (0)*_taddr0(char) > 0  ) goto _L0
(0)_L2:
(17)	(4)_tvar1 = (6)_tvar8 
(18)	(0)_taddr3 = (0)b + (4)_tvar1
(20)	(0)*_taddr3(char) = 0 
(21)	Return (2)i 

(0)sum:
(0)	Enter(saved regs:0x0) (0)sum  24 
(1)	(0)_tvar10 = 0 
(2)	(0)i = (0)_tvar10 
(3)	(0)_tvar10 = 0 
(4)	(0)sum = (0)_tvar10 
(0)	goto _L4
(0)_L3:
(5)	(0)_tvar11 = (0)i * 1 
(6)	(0)_taddr5 = (0)b + (0)_tvar11
(7)	(0)_tvar11 = (0)sum + (0)*_taddr5(char) 
(8)	(0)sum = (0)_tvar11 
(9)	(0)_tvar11 = 1 
(10)	(0)_tvar11 = (0)i + (0)_tvar11
(11)	(0)i = (0)_tvar11 
(0)_L4:
(12)	(0)_tvar10 = (0)i * 1 
(13)	(0)_taddr4 = (0)b + (0)_tvar10
(14)	(0)_tvar10 = 0 
(15)	if ( (0)*_taddr4(char) > (0)_tvar10 ) goto _L3
(0)_L5:
(16)	Return (0)sum 

(0)main:
(0)	Enter(saved regs:0x0) (0)main  8 
(0)	_tstr0 = "hello world"
(1)	Param (0)_tstr0 
(2)	Param (0)x 
(0)	Call (0)copy  2 
(3)	Retrieve (0)_tvar11 
(4)	(0)y = (0)_tvar11 
(5)	Param (0)x 
(0)	Call (0)sum  1 
(6)	Retrieve (0)_tvar11 
(7)	(0)_tvar11 = (0)y + (0)_tvar11
(8)	(0)y = (0)_tvar11 
(9)	Param (0)y 
(0)	Call (0)print_int  1 
(0)	_tstr1 = "\n"
(10)	Param (0)_tstr1 
(0)	Call (0)print_string  1 
(11)	Return 

