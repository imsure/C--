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

side_effect:
	Enter side_effect  8 
	_tvar0 = 1 
	_tvar1 = -_tvar0 
	flag = _tvar1 
	Return x 

	.data
_val:	.space 4
_flag:	.space 4
	.text
_side_effect:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -8($sp) # Allocate stack frame for locals/tmps
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	neg $10, $8
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	sw $8, _flag # Store to global int flag.
	lw $2, 8($fp) # Load int formal x.
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.
main:
	Enter main  32 
	_tvar0 = 3 
	x = _tvar0 
	_tvar0 = 4 
	y = _tvar0 
	_tvar0 = 5 
	z = _tvar0 
	_tvar0 = 1 
	flag = _tvar0 
	_tvar0 = 1234 
	val = _tvar0 
	if ( x < y ) goto _L3
	goto _L1
_L3:
	if ( y > z ) goto _L2
	goto _L1
_L2:
	Param x 
	Call side_effect  1 
	Retrieve _tvar0 
	if ( _tvar0 < z ) goto _L0
	goto _L1
_L0:
	_tvar1 = 1 
	_tvar1 = x - _tvar1
	x = _tvar1 
_L1:
	_tvar1 = 0 
	if ( flag < _tvar1 ) goto _L4
	goto _L5
_L4:
	_tvar2 = 4321 
	val = _tvar2 
_L5:
	if ( x < y ) goto _L6
	goto _L9
_L9:
	if ( y > z ) goto _L6
	goto _L8
_L8:
	Param x 
	Call side_effect  1 
	Retrieve _tvar2 
	if ( _tvar2 < z ) goto _L6
	goto _L7
_L6:
	_tvar3 = 1 
	_tvar3 = x - _tvar3
	x = _tvar3 
_L7:
	_tvar3 = 0 
	if ( flag < _tvar3 ) goto _L10
	goto _L11
_L10:
	_tvar4 = 4321 
	val = _tvar4 
_L11:
	_tvar4 = x * val
	val = _tvar4 
	Param val 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

	.data
__tstr0:	.asciiz "\n"
	.align 2
	.text
main:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -32($sp) # Allocate stack frame for locals/tmps
	li $8, 3 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, -24($fp) # Store to local int x.
	li $8, 4 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, -28($fp) # Store to local int y.
	li $8, 5 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, -32($fp) # Store to local int z.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _flag # Store to global int flag.
	li $8, 1234 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _val # Store to global int val.
	lw $8, -24($fp) # Load local int x.
	lw $9, -28($fp) # Load local int y.
	blt $8, $9, _L3
	j _L1
	.text
_L3:	lw $8, -28($fp) # Load local int y.
	lw $9, -32($fp) # Load local int z.
	bgt $8, $9, _L2
	j _L1
	.text
_L2:	lw $8, -24($fp) # Load local int x.
	la $sp, -4($sp) # Allocate stack space for parameter x.
	sw $8, 0($sp) # Push the parameter value.
	jal _side_effect
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -4($fp) # Store returned value to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lw $9, -32($fp) # Load local int z.
	blt $8, $9, _L0
	j _L1
	.text
_L0:	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -24($fp) # Load local int x.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	sub $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	sw $8, -24($fp) # Store to local int x.
	.text
_L1:	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, _flag # Load global int flag.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	blt $8, $9, _L4
	j _L5
	.text
_L4:	li $8, 4321 # Load int constant shorter than 16-bits
	sw $8, -12($fp) # Store to tmp variable _tvar2.
	lw $8, -12($fp) # Load tmp variable _tvar2.
	sw $8, _val # Store to global int val.
	.text
_L5:	lw $8, -24($fp) # Load local int x.
	lw $9, -28($fp) # Load local int y.
	blt $8, $9, _L6
	j _L9
	.text
_L9:	lw $8, -28($fp) # Load local int y.
	lw $9, -32($fp) # Load local int z.
	bgt $8, $9, _L6
	j _L8
	.text
_L8:	lw $8, -24($fp) # Load local int x.
	la $sp, -4($sp) # Allocate stack space for parameter x.
	sw $8, 0($sp) # Push the parameter value.
	jal _side_effect
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -12($fp) # Store returned value to tmp variable _tvar2.
	lw $8, -12($fp) # Load tmp variable _tvar2.
	lw $9, -32($fp) # Load local int z.
	blt $8, $9, _L6
	j _L7
	.text
_L6:	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -16($fp) # Store to tmp variable _tvar3.
	lw $8, -24($fp) # Load local int x.
	lw $9, -16($fp) # Load tmp variable _tvar3.
	sub $10, $8, $9
	sw $10, -16($fp) # Store to tmp variable _tvar3.
	lw $8, -16($fp) # Load tmp variable _tvar3.
	sw $8, -24($fp) # Store to local int x.
	.text
_L7:	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -16($fp) # Store to tmp variable _tvar3.
	lw $8, _flag # Load global int flag.
	lw $9, -16($fp) # Load tmp variable _tvar3.
	blt $8, $9, _L10
	j _L11
	.text
_L10:	li $8, 4321 # Load int constant shorter than 16-bits
	sw $8, -20($fp) # Store to tmp variable _tvar4.
	lw $8, -20($fp) # Load tmp variable _tvar4.
	sw $8, _val # Store to global int val.
	.text
_L11:	lw $8, -24($fp) # Load local int x.
	lw $9, _val # Load global int val.
	mul $10, $8, $9
	sw $10, -20($fp) # Store to tmp variable _tvar4.
	lw $8, -20($fp) # Load tmp variable _tvar4.
	sw $8, _val # Store to global int val.
	lw $8, _val # Load global int val.
	la $sp, -4($sp) # Allocate stack space for parameter val.
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
