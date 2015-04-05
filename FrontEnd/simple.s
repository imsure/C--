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

	.text
_add:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -4($sp) # Allocate stack frame for locals/tmps
	lw $8, 12($fp) # Load int formal x.
	lw $9, 8($fp) # Load int formal y.
	add $10, $8, $9
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	move $2, $11 # return int _tvar0
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.

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
	move $11, $8 # Store local tmp _tvar1 to its pre-assigned register.
	move $16, $11 # Store local int f to its pre-assigned register.
	li $8, 7 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar1 to its pre-assigned register.
	move $15, $11 # Store local int i to its pre-assigned register.
	j _L1
	.text
_L0:	li $8, 1 # Load int constant shorter than 16-bits
	move $14, $8 # Store local tmp _tvar4 to its pre-assigned register.
	li $8, 2 # Load int constant shorter than 16-bits
	move $13, $8 # Store local tmp _tvar7 to its pre-assigned register.
	li $8, 0 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar10 to its pre-assigned register.
	la $sp, -4($sp) # Allocate stack space for parameter i.
	sw $15, 0($sp) # Push the parameter value.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar10.
	sw $11, 0($sp) # Push the parameter value.
	sw $11, -4($fp) # Store local int/tmp _tvar1 from its pre-assigned register to memory location.
	sw $16, -60($fp) # Store local int/tmp f from its pre-assigned register to memory location.
	sw $15, -64($fp) # Store local int/tmp i from its pre-assigned register to memory location.
	sw $14, -16($fp) # Store local int/tmp _tvar4 from its pre-assigned register to memory location.
	sw $13, -28($fp) # Store local int/tmp _tvar7 from its pre-assigned register to memory location.
	sw $11, -68($fp) # Store local int/tmp _tvar10 from its pre-assigned register to memory location.
	jal _add
	la $sp, 8($sp) # Pop parameters off the stack.
	lw $11, -4($fp) # Reload local int/tmp _tvar1 into its pre-assigned register.
	lw $16, -60($fp) # Reload local int/tmp f into its pre-assigned register.
	lw $15, -64($fp) # Reload local int/tmp i into its pre-assigned register.
	lw $14, -16($fp) # Reload local int/tmp _tvar4 into its pre-assigned register.
	lw $13, -28($fp) # Reload local int/tmp _tvar7 into its pre-assigned register.
	lw $11, -68($fp) # Reload local int/tmp _tvar10 into its pre-assigned register.
	move $12, $2 # retrieve return value into _tvar9
	li $8, 1 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar11 to its pre-assigned register.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar9.
	sw $12, 0($sp) # Push the parameter value.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar11.
	sw $11, 0($sp) # Push the parameter value.
	sw $11, -4($fp) # Store local int/tmp _tvar1 from its pre-assigned register to memory location.
	sw $16, -60($fp) # Store local int/tmp f from its pre-assigned register to memory location.
	sw $15, -64($fp) # Store local int/tmp i from its pre-assigned register to memory location.
	sw $14, -16($fp) # Store local int/tmp _tvar4 from its pre-assigned register to memory location.
	sw $13, -28($fp) # Store local int/tmp _tvar7 from its pre-assigned register to memory location.
	sw $11, -68($fp) # Store local int/tmp _tvar10 from its pre-assigned register to memory location.
	sw $12, -36($fp) # Store local int/tmp _tvar9 from its pre-assigned register to memory location.
	sw $11, -72($fp) # Store local int/tmp _tvar11 from its pre-assigned register to memory location.
	jal _add
	la $sp, 8($sp) # Pop parameters off the stack.
	lw $11, -4($fp) # Reload local int/tmp _tvar1 into its pre-assigned register.
	lw $16, -60($fp) # Reload local int/tmp f into its pre-assigned register.
	lw $15, -64($fp) # Reload local int/tmp i into its pre-assigned register.
	lw $14, -16($fp) # Reload local int/tmp _tvar4 into its pre-assigned register.
	lw $13, -28($fp) # Reload local int/tmp _tvar7 into its pre-assigned register.
	lw $11, -68($fp) # Reload local int/tmp _tvar10 into its pre-assigned register.
	lw $12, -36($fp) # Reload local int/tmp _tvar9 into its pre-assigned register.
	lw $11, -72($fp) # Reload local int/tmp _tvar11 into its pre-assigned register.
	move $11, $2 # retrieve return value into _tvar8
	la $sp, -4($sp) # Allocate stack space for parameter _tvar7.
	sw $13, 0($sp) # Push the parameter value.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar8.
	sw $11, 0($sp) # Push the parameter value.
	sw $11, -4($fp) # Store local int/tmp _tvar1 from its pre-assigned register to memory location.
	sw $16, -60($fp) # Store local int/tmp f from its pre-assigned register to memory location.
	sw $15, -64($fp) # Store local int/tmp i from its pre-assigned register to memory location.
	sw $14, -16($fp) # Store local int/tmp _tvar4 from its pre-assigned register to memory location.
	sw $13, -28($fp) # Store local int/tmp _tvar7 from its pre-assigned register to memory location.
	sw $11, -68($fp) # Store local int/tmp _tvar10 from its pre-assigned register to memory location.
	sw $12, -36($fp) # Store local int/tmp _tvar9 from its pre-assigned register to memory location.
	sw $11, -72($fp) # Store local int/tmp _tvar11 from its pre-assigned register to memory location.
	sw $11, -32($fp) # Store local int/tmp _tvar8 from its pre-assigned register to memory location.
	jal _add
	la $sp, 8($sp) # Pop parameters off the stack.
	lw $11, -4($fp) # Reload local int/tmp _tvar1 into its pre-assigned register.
	lw $16, -60($fp) # Reload local int/tmp f into its pre-assigned register.
	lw $15, -64($fp) # Reload local int/tmp i into its pre-assigned register.
	lw $14, -16($fp) # Reload local int/tmp _tvar4 into its pre-assigned register.
	lw $13, -28($fp) # Reload local int/tmp _tvar7 into its pre-assigned register.
	lw $11, -68($fp) # Reload local int/tmp _tvar10 into its pre-assigned register.
	lw $12, -36($fp) # Reload local int/tmp _tvar9 into its pre-assigned register.
	lw $11, -72($fp) # Reload local int/tmp _tvar11 into its pre-assigned register.
	lw $11, -32($fp) # Reload local int/tmp _tvar8 into its pre-assigned register.
	move $13, $2 # retrieve return value into _tvar6
	li $8, 5 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar12 to its pre-assigned register.
	neg $10, $11
	move $12, $10 # Store local tmp _tvar13 to its pre-assigned register.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar6.
	sw $13, 0($sp) # Push the parameter value.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar13.
	sw $12, 0($sp) # Push the parameter value.
	sw $11, -4($fp) # Store local int/tmp _tvar1 from its pre-assigned register to memory location.
	sw $16, -60($fp) # Store local int/tmp f from its pre-assigned register to memory location.
	sw $15, -64($fp) # Store local int/tmp i from its pre-assigned register to memory location.
	sw $14, -16($fp) # Store local int/tmp _tvar4 from its pre-assigned register to memory location.
	sw $13, -28($fp) # Store local int/tmp _tvar7 from its pre-assigned register to memory location.
	sw $11, -68($fp) # Store local int/tmp _tvar10 from its pre-assigned register to memory location.
	sw $12, -36($fp) # Store local int/tmp _tvar9 from its pre-assigned register to memory location.
	sw $11, -72($fp) # Store local int/tmp _tvar11 from its pre-assigned register to memory location.
	sw $11, -32($fp) # Store local int/tmp _tvar8 from its pre-assigned register to memory location.
	sw $13, -24($fp) # Store local int/tmp _tvar6 from its pre-assigned register to memory location.
	sw $11, -76($fp) # Store local int/tmp _tvar12 from its pre-assigned register to memory location.
	sw $12, -80($fp) # Store local int/tmp _tvar13 from its pre-assigned register to memory location.
	jal _add
	la $sp, 8($sp) # Pop parameters off the stack.
	lw $11, -4($fp) # Reload local int/tmp _tvar1 into its pre-assigned register.
	lw $16, -60($fp) # Reload local int/tmp f into its pre-assigned register.
	lw $15, -64($fp) # Reload local int/tmp i into its pre-assigned register.
	lw $14, -16($fp) # Reload local int/tmp _tvar4 into its pre-assigned register.
	lw $13, -28($fp) # Reload local int/tmp _tvar7 into its pre-assigned register.
	lw $11, -68($fp) # Reload local int/tmp _tvar10 into its pre-assigned register.
	lw $12, -36($fp) # Reload local int/tmp _tvar9 into its pre-assigned register.
	lw $11, -72($fp) # Reload local int/tmp _tvar11 into its pre-assigned register.
	lw $11, -32($fp) # Reload local int/tmp _tvar8 into its pre-assigned register.
	lw $13, -24($fp) # Reload local int/tmp _tvar6 into its pre-assigned register.
	lw $11, -76($fp) # Reload local int/tmp _tvar12 into its pre-assigned register.
	lw $12, -80($fp) # Reload local int/tmp _tvar13 into its pre-assigned register.
	move $11, $2 # retrieve return value into _tvar5
	la $sp, -4($sp) # Allocate stack space for parameter _tvar4.
	sw $14, 0($sp) # Push the parameter value.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar5.
	sw $11, 0($sp) # Push the parameter value.
	sw $11, -4($fp) # Store local int/tmp _tvar1 from its pre-assigned register to memory location.
	sw $16, -60($fp) # Store local int/tmp f from its pre-assigned register to memory location.
	sw $15, -64($fp) # Store local int/tmp i from its pre-assigned register to memory location.
	sw $14, -16($fp) # Store local int/tmp _tvar4 from its pre-assigned register to memory location.
	sw $13, -28($fp) # Store local int/tmp _tvar7 from its pre-assigned register to memory location.
	sw $11, -68($fp) # Store local int/tmp _tvar10 from its pre-assigned register to memory location.
	sw $12, -36($fp) # Store local int/tmp _tvar9 from its pre-assigned register to memory location.
	sw $11, -72($fp) # Store local int/tmp _tvar11 from its pre-assigned register to memory location.
	sw $11, -32($fp) # Store local int/tmp _tvar8 from its pre-assigned register to memory location.
	sw $13, -24($fp) # Store local int/tmp _tvar6 from its pre-assigned register to memory location.
	sw $11, -76($fp) # Store local int/tmp _tvar12 from its pre-assigned register to memory location.
	sw $12, -80($fp) # Store local int/tmp _tvar13 from its pre-assigned register to memory location.
	sw $11, -20($fp) # Store local int/tmp _tvar5 from its pre-assigned register to memory location.
	jal _add
	la $sp, 8($sp) # Pop parameters off the stack.
	lw $11, -4($fp) # Reload local int/tmp _tvar1 into its pre-assigned register.
	lw $16, -60($fp) # Reload local int/tmp f into its pre-assigned register.
	lw $15, -64($fp) # Reload local int/tmp i into its pre-assigned register.
	lw $14, -16($fp) # Reload local int/tmp _tvar4 into its pre-assigned register.
	lw $13, -28($fp) # Reload local int/tmp _tvar7 into its pre-assigned register.
	lw $11, -68($fp) # Reload local int/tmp _tvar10 into its pre-assigned register.
	lw $12, -36($fp) # Reload local int/tmp _tvar9 into its pre-assigned register.
	lw $11, -72($fp) # Reload local int/tmp _tvar11 into its pre-assigned register.
	lw $11, -32($fp) # Reload local int/tmp _tvar8 into its pre-assigned register.
	lw $13, -24($fp) # Reload local int/tmp _tvar6 into its pre-assigned register.
	lw $11, -76($fp) # Reload local int/tmp _tvar12 into its pre-assigned register.
	lw $12, -80($fp) # Reload local int/tmp _tvar13 into its pre-assigned register.
	lw $11, -20($fp) # Reload local int/tmp _tvar5 into its pre-assigned register.
	move $11, $2 # retrieve return value into _tvar3
	li $8, 1 # Load int constant shorter than 16-bits
	move $12, $8 # Store local tmp _tvar13 to its pre-assigned register.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar3.
	sw $11, 0($sp) # Push the parameter value.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar13.
	sw $12, 0($sp) # Push the parameter value.
	sw $11, -4($fp) # Store local int/tmp _tvar1 from its pre-assigned register to memory location.
	sw $16, -60($fp) # Store local int/tmp f from its pre-assigned register to memory location.
	sw $15, -64($fp) # Store local int/tmp i from its pre-assigned register to memory location.
	sw $14, -16($fp) # Store local int/tmp _tvar4 from its pre-assigned register to memory location.
	sw $13, -28($fp) # Store local int/tmp _tvar7 from its pre-assigned register to memory location.
	sw $11, -68($fp) # Store local int/tmp _tvar10 from its pre-assigned register to memory location.
	sw $12, -36($fp) # Store local int/tmp _tvar9 from its pre-assigned register to memory location.
	sw $11, -72($fp) # Store local int/tmp _tvar11 from its pre-assigned register to memory location.
	sw $11, -32($fp) # Store local int/tmp _tvar8 from its pre-assigned register to memory location.
	sw $13, -24($fp) # Store local int/tmp _tvar6 from its pre-assigned register to memory location.
	sw $11, -76($fp) # Store local int/tmp _tvar12 from its pre-assigned register to memory location.
	sw $12, -80($fp) # Store local int/tmp _tvar13 from its pre-assigned register to memory location.
	sw $11, -20($fp) # Store local int/tmp _tvar5 from its pre-assigned register to memory location.
	sw $11, -12($fp) # Store local int/tmp _tvar3 from its pre-assigned register to memory location.
	jal _add
	la $sp, 8($sp) # Pop parameters off the stack.
	lw $11, -4($fp) # Reload local int/tmp _tvar1 into its pre-assigned register.
	lw $16, -60($fp) # Reload local int/tmp f into its pre-assigned register.
	lw $15, -64($fp) # Reload local int/tmp i into its pre-assigned register.
	lw $14, -16($fp) # Reload local int/tmp _tvar4 into its pre-assigned register.
	lw $13, -28($fp) # Reload local int/tmp _tvar7 into its pre-assigned register.
	lw $11, -68($fp) # Reload local int/tmp _tvar10 into its pre-assigned register.
	lw $12, -36($fp) # Reload local int/tmp _tvar9 into its pre-assigned register.
	lw $11, -72($fp) # Reload local int/tmp _tvar11 into its pre-assigned register.
	lw $11, -32($fp) # Reload local int/tmp _tvar8 into its pre-assigned register.
	lw $13, -24($fp) # Reload local int/tmp _tvar6 into its pre-assigned register.
	lw $11, -76($fp) # Reload local int/tmp _tvar12 into its pre-assigned register.
	lw $12, -80($fp) # Reload local int/tmp _tvar13 into its pre-assigned register.
	lw $11, -20($fp) # Reload local int/tmp _tvar5 into its pre-assigned register.
	lw $11, -12($fp) # Reload local int/tmp _tvar3 into its pre-assigned register.
	move $11, $2 # retrieve return value into _tvar2
	mul $10, $16, $11
	move $12, $10 # Store local tmp _tvar13 to its pre-assigned register.
	move $16, $12 # Store local int f to its pre-assigned register.
	li $8, 1 # Load int constant shorter than 16-bits
	move $12, $8 # Store local tmp _tvar13 to its pre-assigned register.
	sub $10, $15, $12
	move $12, $10 # Store local tmp _tvar13 to its pre-assigned register.
	move $15, $12 # Store local int i to its pre-assigned register.
	.text
_L1:	li $8, 0 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar1 to its pre-assigned register.
	bgt $15, $11, _L0
	.text
_L2:	la $sp, -4($sp) # Allocate stack space for parameter f.
	sw $16, 0($sp) # Push the parameter value.
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

