(0)main:
(0)	Enter(saved regs:0x0) (0)main  44 
(2)	(0)i = 0 
(4)	(0)res = 123 
(0)	goto _L1
(0)_L0:
(6)	(0)j = 0 
(0)	goto _L4
(0)_L3:
(7)	(0)_tvar2 = (0)i + (0)j
(9)	(0)_tvar2 = (0)_tvar2 / 2 
(10)	(0)k = (0)_tvar2 
(11)	if ( (0)k <= (0)i ) goto _L7
(0)_L6:
(13)	(0)a = 0 
(0)	goto _L9
(0)_L8:
(14)	(0)_tvar3 = (0)a + (0)_tvar2
(16)	(0)_tvar3 = (0)_tvar3 / 2 
(17)	(0)b = (0)_tvar3 
(18)	if ( (0)b <= (0)j ) goto _L12
(0)_L11:
(19)	(0)_tvar3 = (0)res + (0)_tvar3
(20)	(0)res = (0)_tvar3 
(0)	goto _L13
(0)_L12:
(21)	(0)_tvar3 = (0)res + (0)_tvar2
(22)	(0)res = (0)_tvar3 
(0)_L13:
(24)	(0)_tvar3 = (0)a + 1 
(25)	(0)a = (0)_tvar3 
(0)_L9:
(26)	(0)_tvar2 = 5 
(27)	if ( (0)a < 5  ) goto _L8
(0)_L7:
(29)	(0)_tvar3 = (0)j + 1 
(30)	(0)j = (0)_tvar3 
(0)_L4:
(32)	if ( (0)j < 5  ) goto _L3
(0)_L5:
(34)	(0)_tvar3 = (0)i + 1 
(35)	(0)i = (0)_tvar3 
(0)_L1:
(37)	if ( (0)i < 5  ) goto _L0
(0)_L2:
(38)	Param (0)res 
(0)	Call (0)print_int  1 
(0)	_tstr0 = "\n"
(39)	Param (0)_tstr0 
(0)	Call (0)print_string  1 
(40)	Return 

