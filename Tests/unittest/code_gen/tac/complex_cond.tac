	.text
print_int:
	li $v0, 1
	lw $a0, 0($sp)
	syscall
	jr $ra

	.text
print_string:
	li $v0, 4
	lw $a0, 0($sp)
	syscall
	jr $ra

main:
	Enter main  4 
	_tvar0 = 1 
	a = _tvar0 
	_tvar0 = 2 
	b = _tvar0 
	_tvar0 = 3 
	c = _tvar0 
	_tvar0 = 4 
	d = _tvar0 
	_tvar0 = 5 
	e = _tvar0 
	_tvar0 = 6 
	f = _tvar0 
	_tvar0 = 7 
	g = _tvar0 
	_tvar0 = 8 
	h = _tvar0 
	_tvar0 = 9 
	i = _tvar0 
	_tvar0 = 10 
	j = _tvar0 
	if ( a <= b ) goto _L6
	goto _L1
_L6:
	if ( b <= c ) goto _L5
	goto _L1
_L5:
	if ( c <= d ) goto _L4
	goto _L1
_L4:
	if ( d <= e ) goto _L3
	goto _L1
_L3:
	if ( e > f ) goto _L1
	goto _L10
_L10:
	if ( f > g ) goto _L1
	goto _L9
_L9:
	if ( g > h ) goto _L1
	goto _L8
_L8:
	if ( h > i ) goto _L1
	goto _L7
_L7:
	if ( i > j ) goto _L1
	goto _L0
_L0:
	_tvar0 = 1111 
	res = _tvar0 
	goto _L2
_L1:
	_tvar0 = 2222 
	res = _tvar0 
_L2:
	Param res 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

	.data
_res:	.space 4
__tstr0:	.asciiz "\n"
	.align 2
_a:	.space 4
_b:	.space 4
_c:	.space 4
_d:	.space 4
_e:	.space 4
_f:	.space 4
_g:	.space 4
_h:	.space 4
_i:	.space 4
_j:	.space 4
	.text
main:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -4($sp) # Allocate stack frame for locals/tmps
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _a # Store to global int a.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _b # Store to global int b.
	li $8, 3 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _c # Store to global int c.
	li $8, 4 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _d # Store to global int d.
	li $8, 5 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _e # Store to global int e.
	li $8, 6 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _f # Store to global int f.
	li $8, 7 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _g # Store to global int g.
	li $8, 8 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _h # Store to global int h.
	li $8, 9 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _i # Store to global int i.
	li $8, 10 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _j # Store to global int j.
	lw $8, _a # Load global int a.
	lw $9, _b # Load global int b.
	ble $8, $9, _L6
	j _L1
	.text
_L6:	lw $8, _b # Load global int b.
	lw $9, _c # Load global int c.
	ble $8, $9, _L5
	j _L1
	.text
_L5:	lw $8, _c # Load global int c.
	lw $9, _d # Load global int d.
	ble $8, $9, _L4
	j _L1
	.text
_L4:	lw $8, _d # Load global int d.
	lw $9, _e # Load global int e.
	ble $8, $9, _L3
	j _L1
	.text
_L3:	lw $8, _e # Load global int e.
	lw $9, _f # Load global int f.
	bgt $8, $9, _L1
	j _L10
	.text
_L10:	lw $8, _f # Load global int f.
	lw $9, _g # Load global int g.
	bgt $8, $9, _L1
	j _L9
	.text
_L9:	lw $8, _g # Load global int g.
	lw $9, _h # Load global int h.
	bgt $8, $9, _L1
	j _L8
	.text
_L8:	lw $8, _h # Load global int h.
	lw $9, _i # Load global int i.
	bgt $8, $9, _L1
	j _L7
	.text
_L7:	lw $8, _i # Load global int i.
	lw $9, _j # Load global int j.
	bgt $8, $9, _L1
	j _L0
	.text
_L0:	li $8, 1111 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _res # Store to global int res.
	j _L2
	.text
_L1:	li $8, 2222 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _res # Store to global int res.
	.text
_L2:	lw $8, _res # Load global int res.
	la $sp, -4($sp) # Allocate stack space for parameter res.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr0 # Load string const address _tstr0.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr0.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.
