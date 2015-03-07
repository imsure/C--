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
	_tvar0 = d * e
	_tvar0 = c + _tvar0
	_tvar0 = b * _tvar0
	_tvar0 = a + _tvar0
	Return _tvar0 

	.data
	.text
_f:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -4($sp) # Allocate stack frame for locals/tmps
	lb $8, 12($fp) # Load char formal d.
	lw $9, 8($fp) # Load int formal e.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, 16($fp) # Load int formal c.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lb $8, 20($fp) # Load char formal b.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, 24($fp) # Load int formal a.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $2, -4($fp) # Load tmp variable _tvar0.
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.
main:
	Enter main  36 
	_tvar1 = 'a' 
	y = _tvar1 
	_tvar1 = 'b' 
	z = _tvar1 
	_tvar2 = 1 
	_tvar3 = 2 
	_tvar4 = 3 
	_tvar5 = 4 
	_tvar6 = 5 
	Param _tvar2 
	Param _tvar3 
	Param _tvar4 
	Param _tvar5 
	Param _tvar6 
	Call f  5 
	Retrieve _tvar1 
	x = _tvar1 
	Param x 
	Param y 
	Param x 
	Param z 
	Param x 
	Call f  5 
	Retrieve _tvar6 
	x = _tvar6 
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
	la $sp, -36($sp) # Allocate stack frame for locals/tmps
	li $8, 97 # Load char constant.
	sw $8, -4($fp) # Store to tmp variable _tvar1.
	lw $8, -4($fp) # Load tmp variable _tvar1.
	sb $8, -32($fp) # Store to local char y.
	li $8, 98 # Load char constant.
	sw $8, -4($fp) # Store to tmp variable _tvar1.
	lw $8, -4($fp) # Load tmp variable _tvar1.
	sb $8, -36($fp) # Store to local char z.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar2.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -12($fp) # Store to tmp variable _tvar3.
	li $8, 3 # Load int constant shorter than 16-bits
	sw $8, -16($fp) # Store to tmp variable _tvar4.
	li $8, 4 # Load int constant shorter than 16-bits
	sw $8, -20($fp) # Store to tmp variable _tvar5.
	li $8, 5 # Load int constant shorter than 16-bits
	sw $8, -24($fp) # Store to tmp variable _tvar6.
	lw $8, -8($fp) # Load tmp variable _tvar2.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar2.
	sw $8, 0($sp) # Push the parameter value.
	lw $8, -12($fp) # Load tmp variable _tvar3.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar3.
	sw $8, 0($sp) # Push the parameter value.
	lw $8, -16($fp) # Load tmp variable _tvar4.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar4.
	sw $8, 0($sp) # Push the parameter value.
	lw $8, -20($fp) # Load tmp variable _tvar5.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar5.
	sw $8, 0($sp) # Push the parameter value.
	lw $8, -24($fp) # Load tmp variable _tvar6.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar6.
	sw $8, 0($sp) # Push the parameter value.
	jal _f
	la $sp, 20($sp) # Pop parameters off the stack.
	sw $2, -4($fp) # Store returned value to tmp variable _tvar1.
	lw $8, -4($fp) # Load tmp variable _tvar1.
	sw $8, -28($fp) # Store to local int x.
	lw $8, -28($fp) # Load local int x.
	la $sp, -4($sp) # Allocate stack space for parameter x.
	sw $8, 0($sp) # Push the parameter value.
	lb $8, -32($fp) # Load local char y.
	la $sp, -4($sp) # Allocate stack space for parameter y.
	sw $8, 0($sp) # Push the parameter value.
	lw $8, -28($fp) # Load local int x.
	la $sp, -4($sp) # Allocate stack space for parameter x.
	sw $8, 0($sp) # Push the parameter value.
	lb $8, -36($fp) # Load local char z.
	la $sp, -4($sp) # Allocate stack space for parameter z.
	sw $8, 0($sp) # Push the parameter value.
	lw $8, -28($fp) # Load local int x.
	la $sp, -4($sp) # Allocate stack space for parameter x.
	sw $8, 0($sp) # Push the parameter value.
	jal _f
	la $sp, 20($sp) # Pop parameters off the stack.
	sw $2, -24($fp) # Store returned value to tmp variable _tvar6.
	lw $8, -24($fp) # Load tmp variable _tvar6.
	sw $8, -28($fp) # Store to local int x.
	lw $8, -28($fp) # Load local int x.
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
