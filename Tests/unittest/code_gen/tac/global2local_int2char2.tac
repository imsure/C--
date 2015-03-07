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
	Enter main  8 
	_tvar0 = 123456 
	x = _tvar0 
	y = x 
	Param x 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Param y 
	Call print_int  1 
	_tstr1 = "\n"
	Param _tstr1 
	Call print_string  1 
	Return 

	.data
__tstr0:	.asciiz "\n"
	.align 2
__tstr1:	.asciiz "\n"
	.align 2
_x:	.space 4
	.text
main:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -8($sp) # Allocate stack frame for locals/tmps
	lui $8, 1 # Load higher 16-bits
	ori $8, 57920 # Load lower 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _x # Store to global int x.
	lw $8, _x # Load global int x.
	sb $8, -8($fp) # Store to local char y.
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
	lb $8, -8($fp) # Load local char y.
	la $sp, -4($sp) # Allocate stack space for parameter y.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr1 # Load string const address _tstr1.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr1.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.
