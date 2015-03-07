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

add:
	Enter add  4 
	_tvar0 = x + y
	Return _tvar0 

	.data
	.text
_add:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -4($sp) # Allocate stack frame for locals/tmps
	lw $8, 12($fp) # Load int formal x.
	lw $9, 8($fp) # Load int formal y.
	add $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $2, -4($fp) # Load tmp variable _tvar0.
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.
main:
	Enter main  80 
	_tvar1 = 1 
	f = _tvar1 
	_tvar1 = 7 
	i = _tvar1 
	goto _L1
_L0:
	_tvar4 = 1 
	_tvar7 = 2 
	_tvar10 = 0 
	Param i 
	Param _tvar10 
	Call add  2 
	Retrieve _tvar9 
	_tvar11 = 1 
	Param _tvar9 
	Param _tvar11 
	Call add  2 
	Retrieve _tvar8 
	Param _tvar7 
	Param _tvar8 
	Call add  2 
	Retrieve _tvar6 
	_tvar12 = 5 
	_tvar13 = -_tvar12 
	Param _tvar6 
	Param _tvar13 
	Call add  2 
	Retrieve _tvar5 
	Param _tvar4 
	Param _tvar5 
	Call add  2 
	Retrieve _tvar3 
	_tvar13 = 1 
	Param _tvar3 
	Param _tvar13 
	Call add  2 
	Retrieve _tvar2 
	_tvar13 = f * _tvar2
	f = _tvar13 
	_tvar13 = 1 
	_tvar13 = i - _tvar13
	i = _tvar13 
_L1:
	_tvar1 = 0 
	if ( i > _tvar1 ) goto _L0
	goto _L2
_L2:
	Param f 
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
	la $sp, -80($sp) # Allocate stack frame for locals/tmps
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar1.
	lw $8, -4($fp) # Load tmp variable _tvar1.
	sw $8, -60($fp) # Store to local int f.
	li $8, 7 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar1.
	lw $8, -4($fp) # Load tmp variable _tvar1.
	sw $8, -64($fp) # Store to local int i.
	j _L1
	.text
_L0:	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -16($fp) # Store to tmp variable _tvar4.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -28($fp) # Store to tmp variable _tvar7.
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -68($fp) # Store to tmp variable _tvar10.
	lw $8, -64($fp) # Load local int i.
	la $sp, -4($sp) # Allocate stack space for parameter i.
	sw $8, 0($sp) # Push the parameter value.
	lw $8, -68($fp) # Load tmp variable _tvar10.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar10.
	sw $8, 0($sp) # Push the parameter value.
	jal _add
	la $sp, 8($sp) # Pop parameters off the stack.
	sw $2, -36($fp) # Store returned value to tmp variable _tvar9.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -72($fp) # Store to tmp variable _tvar11.
	lw $8, -36($fp) # Load tmp variable _tvar9.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar9.
	sw $8, 0($sp) # Push the parameter value.
	lw $8, -72($fp) # Load tmp variable _tvar11.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar11.
	sw $8, 0($sp) # Push the parameter value.
	jal _add
	la $sp, 8($sp) # Pop parameters off the stack.
	sw $2, -32($fp) # Store returned value to tmp variable _tvar8.
	lw $8, -28($fp) # Load tmp variable _tvar7.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar7.
	sw $8, 0($sp) # Push the parameter value.
	lw $8, -32($fp) # Load tmp variable _tvar8.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar8.
	sw $8, 0($sp) # Push the parameter value.
	jal _add
	la $sp, 8($sp) # Pop parameters off the stack.
	sw $2, -24($fp) # Store returned value to tmp variable _tvar6.
	li $8, 5 # Load int constant shorter than 16-bits
	sw $8, -76($fp) # Store to tmp variable _tvar12.
	lw $8, -76($fp) # Load tmp variable _tvar12.
	neg $10, $8
	sw $10, -80($fp) # Store to tmp variable _tvar13.
	lw $8, -24($fp) # Load tmp variable _tvar6.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar6.
	sw $8, 0($sp) # Push the parameter value.
	lw $8, -80($fp) # Load tmp variable _tvar13.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar13.
	sw $8, 0($sp) # Push the parameter value.
	jal _add
	la $sp, 8($sp) # Pop parameters off the stack.
	sw $2, -20($fp) # Store returned value to tmp variable _tvar5.
	lw $8, -16($fp) # Load tmp variable _tvar4.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar4.
	sw $8, 0($sp) # Push the parameter value.
	lw $8, -20($fp) # Load tmp variable _tvar5.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar5.
	sw $8, 0($sp) # Push the parameter value.
	jal _add
	la $sp, 8($sp) # Pop parameters off the stack.
	sw $2, -12($fp) # Store returned value to tmp variable _tvar3.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -80($fp) # Store to tmp variable _tvar13.
	lw $8, -12($fp) # Load tmp variable _tvar3.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar3.
	sw $8, 0($sp) # Push the parameter value.
	lw $8, -80($fp) # Load tmp variable _tvar13.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar13.
	sw $8, 0($sp) # Push the parameter value.
	jal _add
	la $sp, 8($sp) # Pop parameters off the stack.
	sw $2, -8($fp) # Store returned value to tmp variable _tvar2.
	lw $8, -60($fp) # Load local int f.
	lw $9, -8($fp) # Load tmp variable _tvar2.
	mul $10, $8, $9
	sw $10, -80($fp) # Store to tmp variable _tvar13.
	lw $8, -80($fp) # Load tmp variable _tvar13.
	sw $8, -60($fp) # Store to local int f.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -80($fp) # Store to tmp variable _tvar13.
	lw $8, -64($fp) # Load local int i.
	lw $9, -80($fp) # Load tmp variable _tvar13.
	sub $10, $8, $9
	sw $10, -80($fp) # Store to tmp variable _tvar13.
	lw $8, -80($fp) # Load tmp variable _tvar13.
	sw $8, -64($fp) # Store to local int i.
	.text
_L1:	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar1.
	lw $8, -64($fp) # Load local int i.
	lw $9, -4($fp) # Load tmp variable _tvar1.
	bgt $8, $9, _L0
	j _L2
	.text
_L2:	lw $8, -60($fp) # Load local int f.
	la $sp, -4($sp) # Allocate stack space for parameter f.
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
