(0)main:
(0)	Enter(saved regs:0x0) (0)main  44 
(2)	(2)i = 0 
(4)	(3)res = 123 
(0)	goto _L1
(0)_L0:
(6)	(5)j = 0 
(0)	goto _L4
(0)_L3:
(7)	(6)_tvar2 = (2)i + (5)j
(9)	(6)_tvar2 = (6)_tvar2 / 2 
(10)	(8)k = (6)_tvar2 
(11)	if ( (8)k <= (2)i ) goto _L7
(0)_L6:
(13)	(9)a = 0 
(0)	goto _L9
(0)_L8:
(14)	(7)_tvar3 = (9)a + (8)k
(16)	(7)_tvar3 = (7)_tvar3 / 2 
(17)	(11)b = (7)_tvar3 
(18)	if ( (11)b <= (5)j ) goto _L12
(0)_L11:
(19)	(7)_tvar3 = (3)res + (11)b
(20)	(3)res = (7)_tvar3 
(0)	goto _L13
(0)_L12:
(21)	(7)_tvar3 = (3)res + (8)k
(22)	(3)res = (7)_tvar3 
(0)_L13:
(24)	(7)_tvar3 = (9)a + 1 
(25)	(9)a = (7)_tvar3 
(0)_L9:
(27)	if ( (9)a < 5  ) goto _L8
(0)_L7:
(29)	(7)_tvar3 = (5)j + 1 
(30)	(5)j = (7)_tvar3 
(0)_L4:
(32)	if ( (5)j < 5  ) goto _L3
(0)_L5:
(34)	(7)_tvar3 = (2)i + 1 
(35)	(2)i = (7)_tvar3 
(0)_L1:
(37)	if ( (2)i < 5  ) goto _L0
(0)_L2:
(38)	Param (3)res 
(0)	Call (0)print_int  1 
(0)	_tstr0 = "\n"
(39)	Param (0)_tstr0 
(0)	Call (0)print_string  1 
(40)	Return 

