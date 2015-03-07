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
	y = _tvar0 
	Return 

	.data
_y:	.space 4
	.text
_add:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -4($sp) # Allocate stack frame for locals/tmps
	lw $8, 8($fp) # Load int formal x.
	lw $9, _y # Load global int y.
	add $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _y # Store to global int y.
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.
main:
	Enter main  36 
	_tvar0 = 1 
	f = _tvar0 
	_tvar0 = 7 
	i = _tvar0 
	goto _L1
_L0:
	y = i 
	_tvar1 = 0 
	Param _tvar1 
	Call add  1 
	_tvar2 = 1 
	Param _tvar2 
	Call add  1 
	_tvar3 = 2 
	Param _tvar3 
	Call add  1 
	_tvar4 = 5 
	_tvar5 = -_tvar4 
	Param _tvar5 
	Call add  1 
	_tvar5 = 2 
	Param _tvar5 
	Call add  1 
	_tvar6 = f * y
	f = _tvar6 
	_tvar6 = 1 
	_tvar6 = i - _tvar6
	i = _tvar6 
_L1:
	_tvar0 = 0 
	if ( i > _tvar0 ) goto _L0
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
	la $sp, -36($sp) # Allocate stack frame for locals/tmps
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, -32($fp) # Store to local int f.
	li $8, 7 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, -36($fp) # Store to local int i.
	j _L1
	.text
_L0:	lw $8, -36($fp) # Load local int i.
	sw $8, _y # Store to global int y.
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar1.
	sw $8, 0($sp) # Push the parameter value.
	jal _add
	la $sp, 4($sp) # Pop parameters off the stack.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -12($fp) # Store to tmp variable _tvar2.
	lw $8, -12($fp) # Load tmp variable _tvar2.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar2.
	sw $8, 0($sp) # Push the parameter value.
	jal _add
	la $sp, 4($sp) # Pop parameters off the stack.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -16($fp) # Store to tmp variable _tvar3.
	lw $8, -16($fp) # Load tmp variable _tvar3.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar3.
	sw $8, 0($sp) # Push the parameter value.
	jal _add
	la $sp, 4($sp) # Pop parameters off the stack.
	li $8, 5 # Load int constant shorter than 16-bits
	sw $8, -20($fp) # Store to tmp variable _tvar4.
	lw $8, -20($fp) # Load tmp variable _tvar4.
	neg $10, $8
	sw $10, -24($fp) # Store to tmp variable _tvar5.
	lw $8, -24($fp) # Load tmp variable _tvar5.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar5.
	sw $8, 0($sp) # Push the parameter value.
	jal _add
	la $sp, 4($sp) # Pop parameters off the stack.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -24($fp) # Store to tmp variable _tvar5.
	lw $8, -24($fp) # Load tmp variable _tvar5.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar5.
	sw $8, 0($sp) # Push the parameter value.
	jal _add
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -32($fp) # Load local int f.
	lw $9, _y # Load global int y.
	mul $10, $8, $9
	sw $10, -28($fp) # Store to tmp variable _tvar6.
	lw $8, -28($fp) # Load tmp variable _tvar6.
	sw $8, -32($fp) # Store to local int f.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -28($fp) # Store to tmp variable _tvar6.
	lw $8, -36($fp) # Load local int i.
	lw $9, -28($fp) # Load tmp variable _tvar6.
	sub $10, $8, $9
	sw $10, -28($fp) # Store to tmp variable _tvar6.
	lw $8, -28($fp) # Load tmp variable _tvar6.
	sw $8, -36($fp) # Store to local int i.
	.text
_L1:	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -36($fp) # Load local int i.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	bgt $8, $9, _L0
	j _L2
	.text
_L2:	lw $8, -32($fp) # Load local int f.
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
