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
	Enter f  4 
	_tvar0 = 1 
	_tvar0 = x + _tvar0
	Return _tvar0 

	.data
	.text
_f:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -4($sp) # Allocate stack frame for locals/tmps
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, 8($fp) # Load int formal x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $2, -4($fp) # Load tmp variable _tvar0.
	sw $2, -4($fp)
	lb $2, -4($fp)
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.
main:
	Enter main  16 
	_tvar1 = 1 
	y = _tvar1 
	Param y 
	Call f  1 
	Retrieve _tvar1 
	x = _tvar1 
	Param x 
	Call f  1 
	Retrieve _tvar1 
	_tvar1 = x + _tvar1
	y = _tvar1 
	_tvar2 = 'Q' 
	Param _tvar2 
	Call f  1 
	Retrieve _tvar1 
	_tvar2 = y + _tvar1
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
	la $sp, -16($sp) # Allocate stack frame for locals/tmps
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar1.
	lw $8, -4($fp) # Load tmp variable _tvar1.
	sb $8, -16($fp) # Store to local char y.
	lb $8, -16($fp) # Load local char y.
	la $sp, -4($sp) # Allocate stack space for parameter y.
	sw $8, 0($sp) # Push the parameter value.
	jal _f
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -4($fp) # Store returned value to tmp variable _tvar1.
	lw $8, -4($fp) # Load tmp variable _tvar1.
	sw $8, -12($fp) # Store to local int x.
	lw $8, -12($fp) # Load local int x.
	la $sp, -4($sp) # Allocate stack space for parameter x.
	sw $8, 0($sp) # Push the parameter value.
	jal _f
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -4($fp) # Store returned value to tmp variable _tvar1.
	lw $8, -12($fp) # Load local int x.
	lw $9, -4($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar1.
	lw $8, -4($fp) # Load tmp variable _tvar1.
	sb $8, -16($fp) # Store to local char y.
	li $8, 81 # Load char constant.
	sw $8, -8($fp) # Store to tmp variable _tvar2.
	lw $8, -8($fp) # Load tmp variable _tvar2.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar2.
	sw $8, 0($sp) # Push the parameter value.
	jal _f
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -4($fp) # Store returned value to tmp variable _tvar1.
	lb $8, -16($fp) # Load local char y.
	lw $9, -4($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar2.
	lw $8, -8($fp) # Load tmp variable _tvar2.
	sw $8, -12($fp) # Store to local int x.
	lw $8, -12($fp) # Load local int x.
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
