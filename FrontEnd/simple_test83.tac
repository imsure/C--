(0)main:
(0)	Enter(saved regs:0x0) (0)main  28 
(0)	(0)_tvar0 = 0 
(0)	(0)i = (0)_tvar0 
(0)	goto _L1
(0)_L0:
(0)	(0)_tvar1 = 2 
(0)	(0)_tvar1 = (0)i / (0)_tvar1
(0)	(0)_tvar2 = 0 
(0)	if ( (0)_tvar1 == (0)_tvar2 ) goto _L3
(0)	goto _L4
(0)_L3:
(0)	(0)_tvar3 = 3 
(0)	(0)_tvar3 = (0)_tvar3 * (0)i
(0)	(0)_tvar4 = 1 
(0)	(0)_tvar3 = (0)_tvar3 + (0)_tvar4
(0)	(0)j = (0)_tvar3 
(0)	goto _L5
(0)_L4:
(0)	(0)_tvar3 = 2 
(0)	(0)_tvar3 = (0)i / (0)_tvar3
(0)	(0)j = (0)_tvar3 
(0)_L5:
(0)	(0)_tvar3 = 1 
(0)	(0)_tvar3 = (0)i + (0)_tvar3
(0)	(0)i = (0)_tvar3 
(0)_L1:
(0)	(0)_tvar0 = 100 
(0)	if ( (0)i < (0)_tvar0 ) goto _L0
(0)	goto _L2
(0)_L2:
(0)	Param (0)i 
(0)	Call (0)print_int  1 
(0)	_tstr0 = "\n"
(0)	Param (0)_tstr0 
(0)	Call (0)print_string  1 
(0)	Return 

