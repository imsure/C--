(0)main:
(0)	Enter(saved regs:0x0) (0)main  28 
(1)	(1)_tvar0 = 0 
(2)	(2)i = (1)_tvar0 
(0)	goto _L1
(0)_L0:
(3)	(3)_tvar1 = 2 
(4)	(3)_tvar1 = (2)i / (3)_tvar1
(5)	(4)_tvar2 = 0 
(6)	if ( (3)_tvar1 != (4)_tvar2 ) goto _L4
(0)_L3:
(7)	(5)_tvar3 = 3 
(8)	(5)_tvar3 = (5)_tvar3 * (2)i
(9)	(6)_tvar4 = 1 
(10)	(5)_tvar3 = (5)_tvar3 + (6)_tvar4
(11)	(7)j = (5)_tvar3 
(0)	goto _L5
(0)_L4:
(12)	(5)_tvar3 = 2 
(13)	(5)_tvar3 = (2)i / (5)_tvar3
(14)	(7)j = (5)_tvar3 
(0)_L5:
(15)	(5)_tvar3 = 1 
(16)	(5)_tvar3 = (2)i + (5)_tvar3
(17)	(2)i = (5)_tvar3 
(0)_L1:
(18)	(1)_tvar0 = 100 
(19)	if ( (2)i < (1)_tvar0 ) goto _L0
(0)_L2:
(20)	Param (2)i 
(0)	Call (0)print_int  1 
(0)	_tstr0 = "\n"
(21)	Param (0)_tstr0 
(0)	Call (0)print_string  1 
(22)	Return 

