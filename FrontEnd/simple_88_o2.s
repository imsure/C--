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
	la $sp, -64($sp) # Allocate stack frame for locals/tmps
	li $8, 0 # Load int constant shorter than 16-bits
	move $12, $8 # Store local tmp _tvar0 to its pre-assigned register.
	move $11, $12 # Store local int j0 to its pre-assigned register.
	li $8, 0 # Load int constant shorter than 16-bits
	move $12, $8 # Store local tmp _tvar0 to its pre-assigned register.
	move $13, $12 # Store local int i to its pre-assigned register.
	j _L1
	.text
_L0:	li $8, 1 # Load int constant shorter than 16-bits
	move $12, $8 # Store local tmp _tvar1 to its pre-assigned register.
	add $10, $11, $12
	move $12, $10 # Store local tmp _tvar1 to its pre-assigned register.
	move $11, $12 # Store local int j1 to its pre-assigned register.
	li $8, 1 # Load int constant shorter than 16-bits
	move $12, $8 # Store local tmp _tvar1 to its pre-assigned register.
	sub $10, $11, $12
	move $12, $10 # Store local tmp _tvar1 to its pre-assigned register.
	move $11, $12 # Store local int j2 to its pre-assigned register.
	li $8, 2 # Load int constant shorter than 16-bits
	move $12, $8 # Store local tmp _tvar1 to its pre-assigned register.
	add $10, $11, $12
	move $12, $10 # Store local tmp _tvar1 to its pre-assigned register.
	move $11, $12 # Store local int j3 to its pre-assigned register.
	li $8, 2 # Load int constant shorter than 16-bits
	move $12, $8 # Store local tmp _tvar1 to its pre-assigned register.
	sub $10, $11, $12
	move $12, $10 # Store local tmp _tvar1 to its pre-assigned register.
	move $11, $12 # Store local int j4 to its pre-assigned register.
	li $8, 3 # Load int constant shorter than 16-bits
	move $12, $8 # Store local tmp _tvar1 to its pre-assigned register.
	add $10, $11, $12
	move $12, $10 # Store local tmp _tvar1 to its pre-assigned register.
	move $11, $12 # Store local int j5 to its pre-assigned register.
	li $8, 3 # Load int constant shorter than 16-bits
	move $12, $8 # Store local tmp _tvar1 to its pre-assigned register.
	sub $10, $11, $12
	move $12, $10 # Store local tmp _tvar1 to its pre-assigned register.
	move $11, $12 # Store local int j6 to its pre-assigned register.
	li $8, 4 # Load int constant shorter than 16-bits
	move $12, $8 # Store local tmp _tvar1 to its pre-assigned register.
	add $10, $11, $12
	move $12, $10 # Store local tmp _tvar1 to its pre-assigned register.
	move $11, $12 # Store local int j7 to its pre-assigned register.
	li $8, 4 # Load int constant shorter than 16-bits
	move $12, $8 # Store local tmp _tvar1 to its pre-assigned register.
	sub $10, $11, $12
	move $12, $10 # Store local tmp _tvar1 to its pre-assigned register.
	move $11, $12 # Store local int j8 to its pre-assigned register.
	li $8, 5 # Load int constant shorter than 16-bits
	move $12, $8 # Store local tmp _tvar1 to its pre-assigned register.
	add $10, $11, $12
	move $12, $10 # Store local tmp _tvar1 to its pre-assigned register.
	move $11, $12 # Store local int j9 to its pre-assigned register.
	li $8, 5 # Load int constant shorter than 16-bits
	move $12, $8 # Store local tmp _tvar1 to its pre-assigned register.
	sub $10, $11, $12
	move $12, $10 # Store local tmp _tvar1 to its pre-assigned register.
	move $11, $12 # Store local int j10 to its pre-assigned register.
	li $8, 6 # Load int constant shorter than 16-bits
	move $12, $8 # Store local tmp _tvar1 to its pre-assigned register.
	add $10, $11, $12
	move $12, $10 # Store local tmp _tvar1 to its pre-assigned register.
	move $11, $12 # Store local int j11 to its pre-assigned register.
	li $8, 5 # Load int constant shorter than 16-bits
	move $12, $8 # Store local tmp _tvar1 to its pre-assigned register.
	sub $10, $11, $12
	move $12, $10 # Store local tmp _tvar1 to its pre-assigned register.
	move $11, $12 # Store local int j12 to its pre-assigned register.
	li $8, 1 # Load int constant shorter than 16-bits
	move $12, $8 # Store local tmp _tvar1 to its pre-assigned register.
	add $10, $13, $12
	move $12, $10 # Store local tmp _tvar1 to its pre-assigned register.
	move $13, $12 # Store local int i to its pre-assigned register.
	.text
_L1:	li $8, 100 # Load int constant shorter than 16-bits
	move $12, $8 # Store local tmp _tvar0 to its pre-assigned register.
	blt $13, $12, _L0
	.text
_L2:	la $sp, -4($sp) # Allocate stack space for parameter j12.
	sw $11, 0($sp) # Push the parameter value.
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

