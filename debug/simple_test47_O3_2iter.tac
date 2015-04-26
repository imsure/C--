(0)main:
(0)	Enter(saved regs:0x0) (0)main  44 
(1)	(2)i = 0 
(2)	(3)res = 123 
(0)	goto _L1
(0)_L0:
(3)	(5)j = 0 
(0)	goto _L4
(0)_L3:
(4)	(6)_tvar2 = (2)i + (5)j
(5)	(6)_tvar2 = (6)_tvar2 / 2 
(6)	(8)k = (6)_tvar2 
(7)	if ( (8)k <= (2)i ) goto _L7
(0)_L6:
(8)	(9)a = 0 
(0)	goto _L9
(0)_L8:
(9)	(7)_tvar3 = (9)a + (8)k
(10)	(7)_tvar3 = (7)_tvar3 / 2 
(11)	(11)b = (7)_tvar3 
(12)	if ( (11)b <= (5)j ) goto _L12
(0)_L11:
(13)	(7)_tvar3 = 123 + (11)b
(14)	(3)res = (7)_tvar3 
(0)	goto _L13
(0)_L12:
(15)	(7)_tvar3 = 123 + (8)k
(16)	(3)res = (7)_tvar3 
(0)_L13:
(17)	(7)_tvar3 = (9)a + 1 
(18)	(9)a = (7)_tvar3 
(0)_L9:
(19)	if ( (9)a < 5  ) goto _L8
(0)_L7:
(20)	(7)_tvar3 = (5)j + 1 
(21)	(5)j = (7)_tvar3 
(0)_L4:
(22)	if ( (5)j < 5  ) goto _L3
(0)_L5:
(23)	(7)_tvar3 = (2)i + 1 
(24)	(2)i = (7)_tvar3 
(0)_L1:
(25)	if ( (2)i < 5  ) goto _L0
(0)_L2:
(26)	Param (3)res 
(0)	Call (0)print_int  1 
(0)	_tstr0 = "\n"
(27)	Param (0)_tstr0 
(0)	Call (0)print_string  1 
(28)	Return 

