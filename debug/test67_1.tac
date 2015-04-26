(0)copy:
(0)	Enter(saved regs:0x0) (0)copy  40 
(4)	(0)i = 0 
(0)	goto _L1
(0)_L0:
(5)	(1)_tvar1 = (1)_tvar1 
(6)	(0)_taddr2 = (0)b + (1)_tvar1
(7)	(1)_tvar1 = (2)_tvar3 
(8)	(0)_taddr1 = (0)a + (1)_tvar1
(9)	(0)*_taddr2(char) = (0)*_taddr1(char) 
(11)	(1)_tvar1 = (0)i + 1 
(12)	(0)i = (1)_tvar1 
(0)_L1:
(13)	(3)_tvar8 = (0)i * 1 
(24)	(2)_tvar3 = (3)_tvar8 
(23)	(1)_tvar1 = (2)_tvar3 
(22)	(0)_tvar0 = (1)_tvar1 
(14)	(0)_taddr0 = (0)a + (0)_tvar0
(16)	if ( (0)*_taddr0(char) > 0  ) goto _L0
(0)_L2:
(17)	(1)_tvar1 = (3)_tvar8 
(18)	(0)_taddr3 = (0)b + (1)_tvar1
(20)	(0)*_taddr3(char) = 0 
(21)	Return (0)i 

(0)sum:
(0)	Enter(saved regs:0x0) (0)sum  28 
(1)	(0)_tvar10 = 0 
(2)	(0)i = (0)_tvar10 
(3)	(0)_tvar10 = 0 
(4)	(0)sum = (0)_tvar10 
(0)	goto _L4
(0)_L3:
(5)	(4)_tvar11 = (4)_tvar11 
(6)	(0)_taddr5 = (0)b + (4)_tvar11
(7)	(4)_tvar11 = (0)sum + (0)*_taddr5(char) 
(8)	(0)sum = (4)_tvar11 
(9)	(4)_tvar11 = 1 
(10)	(4)_tvar11 = (0)i + (4)_tvar11
(11)	(0)i = (4)_tvar11 
(0)_L4:
(12)	(4)_tvar11 = (0)i * 1 
(17)	(0)_tvar10 = (4)_tvar11 
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
(3)	Retrieve (0)_tvar16 
(4)	(0)y = (0)_tvar16 
(5)	Param (0)x 
(0)	Call (0)sum  1 
(6)	Retrieve (0)_tvar16 
(7)	(0)_tvar16 = (0)y + (0)_tvar16
(8)	(0)y = (0)_tvar16 
(9)	Param (0)y 
(0)	Call (0)print_int  1 
(0)	_tstr1 = "\n"
(10)	Param (0)_tstr1 
(0)	Call (0)print_string  1 
(11)	Return 

