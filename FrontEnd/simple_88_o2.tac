(0)main:
(0)	Enter(saved regs:0x1c00) (0)main  64 
(1)	(1)_tvar0 = 0 
(2)	(2)j0 = (1)_tvar0 
(3)	(1)_tvar0 = 0 
(4)	(3)i = (1)_tvar0 
(0)	goto _L1
(0)_L0:
(5)	(4)_tvar1 = 1 
(6)	(4)_tvar1 = (2)j0 + (4)_tvar1
(7)	(5)j1 = (4)_tvar1 
(8)	(4)_tvar1 = 1 
(9)	(4)_tvar1 = (5)j1 - (4)_tvar1
(10)	(6)j2 = (4)_tvar1 
(11)	(4)_tvar1 = 2 
(12)	(4)_tvar1 = (6)j2 + (4)_tvar1
(13)	(7)j3 = (4)_tvar1 
(14)	(4)_tvar1 = 2 
(15)	(4)_tvar1 = (7)j3 - (4)_tvar1
(16)	(8)j4 = (4)_tvar1 
(17)	(4)_tvar1 = 3 
(18)	(4)_tvar1 = (8)j4 + (4)_tvar1
(19)	(9)j5 = (4)_tvar1 
(20)	(4)_tvar1 = 3 
(21)	(4)_tvar1 = (9)j5 - (4)_tvar1
(22)	(10)j6 = (4)_tvar1 
(23)	(4)_tvar1 = 4 
(24)	(4)_tvar1 = (10)j6 + (4)_tvar1
(25)	(11)j7 = (4)_tvar1 
(26)	(4)_tvar1 = 4 
(27)	(4)_tvar1 = (11)j7 - (4)_tvar1
(28)	(12)j8 = (4)_tvar1 
(29)	(4)_tvar1 = 5 
(30)	(4)_tvar1 = (12)j8 + (4)_tvar1
(31)	(13)j9 = (4)_tvar1 
(32)	(4)_tvar1 = 5 
(33)	(4)_tvar1 = (13)j9 - (4)_tvar1
(34)	(14)j10 = (4)_tvar1 
(35)	(4)_tvar1 = 6 
(36)	(4)_tvar1 = (14)j10 + (4)_tvar1
(37)	(15)j11 = (4)_tvar1 
(38)	(4)_tvar1 = 5 
(39)	(4)_tvar1 = (15)j11 - (4)_tvar1
(40)	(16)j12 = (4)_tvar1 
(41)	(4)_tvar1 = 1 
(42)	(4)_tvar1 = (3)i + (4)_tvar1
(43)	(3)i = (4)_tvar1 
(0)_L1:
(44)	(1)_tvar0 = 100 
(45)	if ( (3)i < (1)_tvar0 ) goto _L0
(0)_L2:
(46)	Param (16)j12 
(0)	Call (0)print_int  1 
(0)	_tstr0 = "\n"
(47)	Param (0)_tstr0 
(0)	Call (0)print_string  1 
(48)	Return 

