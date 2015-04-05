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
	la $sp, -44($sp) # Allocate stack frame for locals/tmps
	li $8, 0 # Load int constant shorter than 16-bits
	move $16, $8 # Store local int i to its pre-assigned register.
	li $8, 123 # Load int constant shorter than 16-bits
	move $15, $8 # Store local int res to its pre-assigned register.
	j _L1
	.text
_L0:	li $8, 0 # Load int constant shorter than 16-bits
	move $14, $8 # Store local int j to its pre-assigned register.
	j _L4
	.text
_L3:	add $10, $16, $14
	move $11, $10 # Store local tmp _tvar2 to its pre-assigned register.
	li $9, 2 # Load int constant shorter than 16-bits
	div $10, $11, $9
	move $11, $10 # Store local tmp _tvar2 to its pre-assigned register.
	move $13, $11 # Store local int k to its pre-assigned register.
	ble $13, $16, _L7
	.text
_L6:	li $8, 0 # Load int constant shorter than 16-bits
	move $12, $8 # Store local int a to its pre-assigned register.
	j _L9
	.text
_L8:	add $10, $12, $13
	move $11, $10 # Store local tmp _tvar3 to its pre-assigned register.
	li $9, 2 # Load int constant shorter than 16-bits
	div $10, $11, $9
	move $11, $10 # Store local tmp _tvar3 to its pre-assigned register.
	move $11, $11 # Store local int b to its pre-assigned register.
	ble $11, $14, _L12
	.text
_L11:	add $10, $15, $11
	move $11, $10 # Store local tmp _tvar3 to its pre-assigned register.
	move $15, $11 # Store local int res to its pre-assigned register.
	j _L13
	.text
_L12:	add $10, $15, $13
	move $11, $10 # Store local tmp _tvar3 to its pre-assigned register.
	move $15, $11 # Store local int res to its pre-assigned register.
	.text
_L13:	li $9, 1 # Load int constant shorter than 16-bits
	add $10, $12, $9
	move $11, $10 # Store local tmp _tvar3 to its pre-assigned register.
	move $12, $11 # Store local int a to its pre-assigned register.
	.text
_L9:	li $8, 5 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar2 to its pre-assigned register.
	blt $12, $11, _L8
	.text
_L7:	li $9, 1 # Load int constant shorter than 16-bits
	add $10, $14, $9
	move $11, $10 # Store local tmp _tvar3 to its pre-assigned register.
	move $14, $11 # Store local int j to its pre-assigned register.
	.text
_L4:	li $8, 5 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar1 to its pre-assigned register.
	blt $14, $11, _L3
	.text
_L5:	li $9, 1 # Load int constant shorter than 16-bits
	add $10, $16, $9
	move $11, $10 # Store local tmp _tvar3 to its pre-assigned register.
	move $16, $11 # Store local int i to its pre-assigned register.
	.text
_L1:	li $8, 5 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	blt $16, $11, _L0
	.text
_L2:	la $sp, -4($sp) # Allocate stack space for parameter res.
	sw $15, 0($sp) # Push the parameter value.
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

