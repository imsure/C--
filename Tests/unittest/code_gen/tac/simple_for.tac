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
	Enter main  24 
	_tvar0 = 0 
	i = _tvar0 
	_tvar0 = 0 
	res = _tvar0 
	goto _L1
_L0:
	_tvar1 = res + i
	res = _tvar1 
	_tvar1 = 1 
	_tvar1 = i + _tvar1
	i = _tvar1 
_L1:
	_tvar0 = 10 
	if ( i < _tvar0 ) goto _L0
	goto _L2
_L2:
	_tvar1 = 0 
	i = _tvar1 
	goto _L4
_L3:
	_tvar2 = res + i
	res = _tvar2 
	_tvar2 = 1 
	_tvar2 = i + _tvar2
	i = _tvar2 
_L4:
	_tvar1 = 10 
	if ( i < _tvar1 ) goto _L3
	goto _L5
_L5:
	_tvar2 = 0 
	i = _tvar2 
	goto _L7
_L6:
	_tvar2 = res + i
	res = _tvar2 
	_tvar2 = 10 
	if ( i > _tvar2 ) goto _L9
	goto _L10
_L9:
	Param res 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 
_L10:
	_tvar3 = 1 
	_tvar3 = i + _tvar3
	i = _tvar3 
_L7:
	goto _L6
_L8:
	Return 

	.data
__tstr0:	.asciiz "\n"
	.align 2
	.text
main:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -24($sp) # Allocate stack frame for locals/tmps
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar0.
	lw $8, -8($fp) # Load tmp variable _tvar0.
	sw $8, -24($fp) # Store to local int i.
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar0.
	lw $8, -8($fp) # Load tmp variable _tvar0.
	sw $8, -4($fp) # Store to local int res.
	j _L1
	.text
_L0:	lw $8, -4($fp) # Load local int res.
	lw $9, -24($fp) # Load local int i.
	add $10, $8, $9
	sw $10, -12($fp) # Store to tmp variable _tvar1.
	lw $8, -12($fp) # Load tmp variable _tvar1.
	sw $8, -4($fp) # Store to local int res.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -12($fp) # Store to tmp variable _tvar1.
	lw $8, -24($fp) # Load local int i.
	lw $9, -12($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -12($fp) # Store to tmp variable _tvar1.
	lw $8, -12($fp) # Load tmp variable _tvar1.
	sw $8, -24($fp) # Store to local int i.
	.text
_L1:	li $8, 10 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar0.
	lw $8, -24($fp) # Load local int i.
	lw $9, -8($fp) # Load tmp variable _tvar0.
	blt $8, $9, _L0
	j _L2
	.text
_L2:	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -12($fp) # Store to tmp variable _tvar1.
	lw $8, -12($fp) # Load tmp variable _tvar1.
	sw $8, -24($fp) # Store to local int i.
	j _L4
	.text
_L3:	lw $8, -4($fp) # Load local int res.
	lw $9, -24($fp) # Load local int i.
	add $10, $8, $9
	sw $10, -16($fp) # Store to tmp variable _tvar2.
	lw $8, -16($fp) # Load tmp variable _tvar2.
	sw $8, -4($fp) # Store to local int res.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -16($fp) # Store to tmp variable _tvar2.
	lw $8, -24($fp) # Load local int i.
	lw $9, -16($fp) # Load tmp variable _tvar2.
	add $10, $8, $9
	sw $10, -16($fp) # Store to tmp variable _tvar2.
	lw $8, -16($fp) # Load tmp variable _tvar2.
	sw $8, -24($fp) # Store to local int i.
	.text
_L4:	li $8, 10 # Load int constant shorter than 16-bits
	sw $8, -12($fp) # Store to tmp variable _tvar1.
	lw $8, -24($fp) # Load local int i.
	lw $9, -12($fp) # Load tmp variable _tvar1.
	blt $8, $9, _L3
	j _L5
	.text
_L5:	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -16($fp) # Store to tmp variable _tvar2.
	lw $8, -16($fp) # Load tmp variable _tvar2.
	sw $8, -24($fp) # Store to local int i.
	j _L7
	.text
_L6:	lw $8, -4($fp) # Load local int res.
	lw $9, -24($fp) # Load local int i.
	add $10, $8, $9
	sw $10, -16($fp) # Store to tmp variable _tvar2.
	lw $8, -16($fp) # Load tmp variable _tvar2.
	sw $8, -4($fp) # Store to local int res.
	li $8, 10 # Load int constant shorter than 16-bits
	sw $8, -16($fp) # Store to tmp variable _tvar2.
	lw $8, -24($fp) # Load local int i.
	lw $9, -16($fp) # Load tmp variable _tvar2.
	bgt $8, $9, _L9
	j _L10
	.text
_L9:	lw $8, -4($fp) # Load local int res.
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
	.text
_L10:	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -20($fp) # Store to tmp variable _tvar3.
	lw $8, -24($fp) # Load local int i.
	lw $9, -20($fp) # Load tmp variable _tvar3.
	add $10, $8, $9
	sw $10, -20($fp) # Store to tmp variable _tvar3.
	lw $8, -20($fp) # Load tmp variable _tvar3.
	sw $8, -24($fp) # Store to local int i.
	.text
_L7:	j _L6
	.text
_L8:	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.
