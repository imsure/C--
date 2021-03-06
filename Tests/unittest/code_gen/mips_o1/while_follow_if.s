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

	.data
__tstr0:	.asciiz "\n"
	.align 2

	.text
main:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -20($sp) # Allocate stack frame for locals/tmps
	li $8, 123 # Load int constant shorter than 16-bits
	sw $8, -20($fp) # Store to local int x.
	li $8, 123 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -20($fp) # Load local int x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	bne $8, $9, _L1
	.text
_L0:	li $8, 321 # Load int constant shorter than 16-bits
	sw $8, -20($fp) # Store to local int x.
	.text
_L1:	j _L3
	.text
_L2:	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -12($fp) # Store to tmp variable _tvar2.
	lw $8, -20($fp) # Load local int x.
	lw $9, -12($fp) # Load tmp variable _tvar2.
	sub $10, $8, $9
	sw $10, -12($fp) # Store to tmp variable _tvar2.
	lw $8, -12($fp) # Load tmp variable _tvar2.
	sw $8, -20($fp) # Store to local int x.
	.text
_L3:	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -20($fp) # Load local int x.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	bgt $8, $9, _L2
	j _L4
	.text
_L4:	lw $8, -20($fp) # Load local int x.
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

