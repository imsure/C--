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
	_tvar0 = 0 
	a = _tvar0 
	_tvar0 = 3 
	LIM = _tvar0 
	_tvar0 = 0 
	res = _tvar0 
	goto _L1
_L0:
	_tvar0 = 0 
	b = _tvar0 
	goto _L4
_L3:
	_tvar0 = 0 
	c = _tvar0 
	goto _L7
_L6:
	_tvar0 = 0 
	d = _tvar0 
	goto _L10
_L9:
	_tvar0 = 0 
	e = _tvar0 
	goto _L13
_L12:
	_tvar0 = 1 
	_tvar0 = res + _tvar0
	res = _tvar0 
	_tvar0 = 1 
	_tvar0 = e + _tvar0
	e = _tvar0 
_L13:
	if ( e < LIM ) goto _L12
	goto _L14
_L14:
	_tvar0 = 1 
	_tvar0 = d + _tvar0
	d = _tvar0 
_L10:
	if ( d < LIM ) goto _L9
	goto _L11
_L11:
	_tvar0 = 1 
	_tvar0 = c + _tvar0
	c = _tvar0 
_L7:
	if ( c < LIM ) goto _L6
	goto _L8
_L8:
	_tvar0 = 1 
	_tvar0 = b + _tvar0
	b = _tvar0 
_L4:
	if ( b < LIM ) goto _L3
	goto _L5
_L5:
	_tvar0 = 1 
	_tvar0 = a + _tvar0
	a = _tvar0 
_L1:
	if ( a < LIM ) goto _L0
	goto _L2
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
_LIM:	.space 4
	.text
main:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -4($sp) # Allocate stack frame for locals/tmps
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _a # Store to global int a.
	li $8, 3 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _LIM # Store to global int LIM.
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _res # Store to global int res.
	j _L1
	.text
_L0:	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _b # Store to global int b.
	j _L4
	.text
_L3:	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _c # Store to global int c.
	j _L7
	.text
_L6:	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _d # Store to global int d.
	j _L10
	.text
_L9:	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _e # Store to global int e.
	j _L13
	.text
_L12:	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, _res # Load global int res.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _res # Store to global int res.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, _e # Load global int e.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _e # Store to global int e.
	.text
_L13:	lw $8, _e # Load global int e.
	lw $9, _LIM # Load global int LIM.
	blt $8, $9, _L12
	j _L14
	.text
_L14:	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, _d # Load global int d.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _d # Store to global int d.
	.text
_L10:	lw $8, _d # Load global int d.
	lw $9, _LIM # Load global int LIM.
	blt $8, $9, _L9
	j _L11
	.text
_L11:	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, _c # Load global int c.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _c # Store to global int c.
	.text
_L7:	lw $8, _c # Load global int c.
	lw $9, _LIM # Load global int LIM.
	blt $8, $9, _L6
	j _L8
	.text
_L8:	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, _b # Load global int b.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _b # Store to global int b.
	.text
_L4:	lw $8, _b # Load global int b.
	lw $9, _LIM # Load global int LIM.
	blt $8, $9, _L3
	j _L5
	.text
_L5:	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, _a # Load global int a.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _a # Store to global int a.
	.text
_L1:	lw $8, _a # Load global int a.
	lw $9, _LIM # Load global int LIM.
	blt $8, $9, _L0
	j _L2
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
