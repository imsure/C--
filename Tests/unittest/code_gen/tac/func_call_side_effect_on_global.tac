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

f:
	Enter f  12 
	_tvar0 = 1 
	y = _tvar0 
	goto _L1
_L0:
	_tvar1 = x * i
	x = _tvar1 
	_tvar1 = 2 
	_tvar1 = _tvar1 * y
	y = _tvar1 
	_tvar1 = 1 
	_tvar1 = i - _tvar1
	i = _tvar1 
_L1:
	_tvar0 = 0 
	if ( i > _tvar0 ) goto _L0
	goto _L2
_L2:
	Return y 

	.data
_x:	.space 4
	.text
_f:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -12($sp) # Allocate stack frame for locals/tmps
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, -12($fp) # Store to local int y.
	j _L1
	.text
_L0:	lw $8, _x # Load global int x.
	lw $9, 8($fp) # Load int formal i.
	mul $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	sw $8, _x # Store to global int x.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	lw $9, -12($fp) # Load local int y.
	mul $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	sw $8, -12($fp) # Store to local int y.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, 8($fp) # Load int formal i.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	sub $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	sw $8, 8($fp) # Store to int formal i.
	.text
_L1:	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, 8($fp) # Load int formal i.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	bgt $8, $9, _L0
	j _L2
	.text
_L2:	lw $2, -12($fp) # Load local int y.
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.
main:
	Enter main  12 
	_tvar1 = 1 
	x = _tvar1 
	_tvar2 = 6 
	Param _tvar2 
	Call f  1 
	Retrieve _tvar1 
	a = _tvar1 
	_tvar2 = a + x
	x = _tvar2 
	Param x 
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
	la $sp, -12($sp) # Allocate stack frame for locals/tmps
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar1.
	lw $8, -4($fp) # Load tmp variable _tvar1.
	sw $8, _x # Store to global int x.
	li $8, 6 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar2.
	lw $8, -8($fp) # Load tmp variable _tvar2.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar2.
	sw $8, 0($sp) # Push the parameter value.
	jal _f
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -4($fp) # Store returned value to tmp variable _tvar1.
	lw $8, -4($fp) # Load tmp variable _tvar1.
	sw $8, -12($fp) # Store to local int a.
	lw $8, -12($fp) # Load local int a.
	lw $9, _x # Load global int x.
	add $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar2.
	lw $8, -8($fp) # Load tmp variable _tvar2.
	sw $8, _x # Store to global int x.
	lw $8, _x # Load global int x.
	la $sp, -4($sp) # Allocate stack space for parameter x.
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
