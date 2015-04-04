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
__tstr1:	.asciiz "\n"
	.align 2
_x:	.space 15
	.align 2

	.text
_copy:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -28($sp) # Allocate stack frame for locals/tmps
	li $8, 0 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	move $12, $11 # Store local int i to its pre-assigned register.
	li $8, 0 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	move $12, $11 # Store local int i to its pre-assigned register.
	j _L1
	.text
_L0:	la $sp, -4($sp) # Allocate stack space for parameter i.
	sw $12, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr0 # Load string const address _tstr0.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr0.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	li $9, 1 # Load int constant shorter than 16-bits
	mul $10, $12, $9
	move $11, $10 # Store local tmp _tvar1 to its pre-assigned register.
	lw $8, 8($fp) # Load address of formal char array b.
	add $10, $8, $11
	sw $10, -24($fp) # Store address to tmp address _taddr2.
	li $9, 1 # Load int constant shorter than 16-bits
	mul $10, $12, $9
	move $11, $10 # Store local tmp _tvar1 to its pre-assigned register.
	lw $8, 12($fp) # Load address of formal char array a.
	add $10, $8, $11
	sw $10, -20($fp) # Store address to tmp address _taddr1.
	lw $9, -20($fp) # Load tmp address _taddr1.
	lb $8, ($9) # Load value of the char array element pointed by _taddr1.
	lw $9, -24($fp) # Load tmp address _taddr2.
	sb $8, ($9) # Store value pointed by _taddr2 to char array element.
	li $8, 1 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar1 to its pre-assigned register.
	add $10, $12, $11
	move $11, $10 # Store local tmp _tvar1 to its pre-assigned register.
	move $12, $11 # Store local int i to its pre-assigned register.
	.text
_L1:	li $9, 1 # Load int constant shorter than 16-bits
	mul $10, $12, $9
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	lw $8, 12($fp) # Load address of formal char array a.
	add $10, $8, $11
	sw $10, -16($fp) # Store address to tmp address _taddr0.
	li $8, 0 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	lw $9, -16($fp) # Load tmp address _taddr0.
	lb $8, ($9) # Load value of the char array element pointed by _taddr0.
	bgt $8, $11, _L0
	.text
_L2:	li $9, 1 # Load int constant shorter than 16-bits
	mul $10, $12, $9
	move $11, $10 # Store local tmp _tvar1 to its pre-assigned register.
	lw $8, 8($fp) # Load address of formal char array b.
	add $10, $8, $11
	sw $10, -28($fp) # Store address to tmp address _taddr3.
	li $8, 0 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar1 to its pre-assigned register.

	# This overwrites the value of 'i' because $12 is allocated to i.
	# This is caused by a bug in MIPS advanced generator.
	lw $12, -28($fp) # Load tmp address _taddr3.
	
	sb $11, ($12) # Store value pointed by _taddr3 to char array element.
	la $sp, -4($sp) # Allocate stack space for parameter i.
	sw $12, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr1 # Load string const address _tstr1.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr1.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	move $2, $12 # return int i
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.

	.data

	.text
_sum:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -24($sp) # Allocate stack frame for locals/tmps
	li $8, 0 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar1 to its pre-assigned register.
	move $13, $11 # Store local int i to its pre-assigned register.
	li $8, 0 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar1 to its pre-assigned register.
	move $12, $11 # Store local int sum to its pre-assigned register.
	j _L4
	.text
_L3:	li $9, 1 # Load int constant shorter than 16-bits
	mul $10, $13, $9
	move $11, $10 # Store local tmp _tvar2 to its pre-assigned register.
	lw $8, 8($fp) # Load address of formal char array b.
	add $10, $8, $11
	sw $10, -24($fp) # Store address to tmp address _taddr5.
	lw $10, -24($fp) # Load tmp address _taddr5.
	lb $9, ($10) # Load value of the char array element pointed by _taddr5.
	add $10, $12, $9
	move $11, $10 # Store local tmp _tvar2 to its pre-assigned register.
	move $12, $11 # Store local int sum to its pre-assigned register.
	li $8, 1 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar2 to its pre-assigned register.
	add $10, $13, $11
	move $11, $10 # Store local tmp _tvar2 to its pre-assigned register.
	move $13, $11 # Store local int i to its pre-assigned register.
	.text
_L4:	li $9, 1 # Load int constant shorter than 16-bits
	mul $10, $13, $9
	move $11, $10 # Store local tmp _tvar1 to its pre-assigned register.
	lw $8, 8($fp) # Load address of formal char array b.
	add $10, $8, $11
	sw $10, -20($fp) # Store address to tmp address _taddr4.
	li $8, 0 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar1 to its pre-assigned register.
	lw $9, -20($fp) # Load tmp address _taddr4.
	lb $8, ($9) # Load value of the char array element pointed by _taddr4.
	bgt $8, $11, _L3
	.text
_L5:	move $2, $12 # return int sum
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.

	.data
__tstr2:	.asciiz "hello world"
	.align 2
__tstr3:	.asciiz "\n"
	.align 2
__tstr4:	.asciiz "\n"
	.align 2

	.text
main:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -8($sp) # Allocate stack frame for locals/tmps
	la $8, __tstr2 # Load string const address _tstr2.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr2.
	sw $8, 0($sp) # Push the parameter value.
	la $8, _x # Load address of global char array x.
	la $sp, -4($sp) # Allocate stack space for parameter x.
	sw $8, 0($sp) # Push the parameter value.
	sw $12, -4($fp) # Store local int/tmp _tvar2 from its pre-assigned register to memory location.
	sw $11, -8($fp) # Store local int/tmp y from its pre-assigned register to memory location.
	jal _copy
	la $sp, 8($sp) # Pop parameters off the stack.
	lw $12, -4($fp) # Reload local int/tmp _tvar2 into its pre-assigned register.
	lw $11, -8($fp) # Reload local int/tmp y into its pre-assigned register.
	move $12, $2 # retrieve return value into _tvar2
	move $11, $12 # Store local int y to its pre-assigned register.
	la $sp, -4($sp) # Allocate stack space for parameter y.
	sw $11, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr3 # Load string const address _tstr3.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr3.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, _x # Load address of global char array x.
	la $sp, -4($sp) # Allocate stack space for parameter x.
	sw $8, 0($sp) # Push the parameter value.
	sw $12, -4($fp) # Store local int/tmp _tvar2 from its pre-assigned register to memory location.
	sw $11, -8($fp) # Store local int/tmp y from its pre-assigned register to memory location.
	jal _sum
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $12, -4($fp) # Reload local int/tmp _tvar2 into its pre-assigned register.
	lw $11, -8($fp) # Reload local int/tmp y into its pre-assigned register.
	move $12, $2 # retrieve return value into _tvar2
	add $10, $11, $12
	move $12, $10 # Store local tmp _tvar2 to its pre-assigned register.
	move $11, $12 # Store local int y to its pre-assigned register.
	la $sp, -4($sp) # Allocate stack space for parameter y.
	sw $11, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr4 # Load string const address _tstr4.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr4.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.

