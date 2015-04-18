(0)f:
(0)	Enter(saved regs:0x0) (0)f  40 
(1)	(1)_tvar0 = 0 
(2)	(2)i = (1)_tvar0 
(0)	goto _L1
(0)_L0:
(3)	(0)_tvar4 = (2)i * 4 
(0)	(3)_tvar1 = (0)_tvar4 
(4)	(0)_taddr0 = (0)a + (3)_tvar1
(5)	(0)*_taddr0(int) = (2)i 
(6)	(3)_tvar1 = (0)_tvar4 
(7)	(0)_taddr1 = (0)x + (3)_tvar1
(8)	(3)_tvar1 = 1 
(9)	(3)_tvar1 = (2)i + (3)_tvar1
(10)	(0)*_taddr1(int) = (3)_tvar1 
(11)	(3)_tvar1 = 1 
(12)	(3)_tvar1 = (2)i + (3)_tvar1
(13)	(3)_tvar1 = (3)_tvar1 * 4 
(14)	(0)_taddr2 = (0)a + (3)_tvar1
(15)	(3)_tvar1 = 1 
(16)	(3)_tvar1 = (2)i + (3)_tvar1
(17)	(0)*_taddr2(int) = (3)_tvar1 
(18)	(3)_tvar1 = 1 
(19)	(3)_tvar1 = (2)i + (3)_tvar1
(20)	(3)_tvar1 = (3)_tvar1 * 4 
(21)	(0)_taddr3 = (0)x + (3)_tvar1
(22)	(3)_tvar1 = 2 
(23)	(3)_tvar1 = (2)i + (3)_tvar1
(24)	(0)*_taddr3(int) = (3)_tvar1 
(25)	(3)_tvar1 = 2 
(26)	(3)_tvar1 = (2)i + (3)_tvar1
(27)	(2)i = (3)_tvar1 
(0)_L1:
(28)	(1)_tvar0 = 10 
(29)	if ( (2)i < (1)_tvar0 ) goto _L0
(0)_L2:
(30)	(3)_tvar1 = 0 
(31)	(4)j = (3)_tvar1 
(32)	(3)_tvar1 = 0 
(33)	(2)i = (3)_tvar1 
(0)	goto _L4
(0)_L3:
(34)	(5)_tvar2 = (2)i * 4 
(35)	(0)_taddr4 = (0)a + (5)_tvar2
(36)	(5)_tvar2 = (4)j + (0)*_taddr4(int) 
(37)	(4)j = (5)_tvar2 
(38)	(5)_tvar2 = 1 
(39)	(5)_tvar2 = (2)i + (5)_tvar2
(40)	(2)i = (5)_tvar2 
(0)_L4:
(41)	(3)_tvar1 = 10 
(42)	if ( (2)i < (3)_tvar1 ) goto _L3
(0)_L5:
(43)	Return (4)j 

(0)main:
(0)	Enter(saved regs:0x0) (0)main  8 
(1)	Param (0)a 
(0)	Call (0)f  1 
(2)	Retrieve (1)_tvar19 
(3)	(2)x = (1)_tvar19 
(4)	Param (2)x 
(0)	Call (0)print_int  1 
(0)	_tstr0 = "\n"
(5)	Param (0)_tstr0 
(0)	Call (0)print_string  1 
(6)	Return 

