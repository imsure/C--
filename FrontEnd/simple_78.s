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
_a:	.space 40

	.text
_f:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -44($sp) # Allocate stack frame for locals/tmps
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, -16($fp) # Store to local int i.
	j _L1
	.text
_L0:	lw $8, -16($fp) # Load local int i.
	li $9, 4 # Load int constant shorter than 16-bits
	mul $10, $8, $9
	sw $10, -44($fp) # Store to tmp variable _tvar4.
	lw $8, -44($fp) # Load tmp variable _tvar4.
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	la $8, _a # Load address of global int array a.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -24($fp) # Store address to tmp address _taddr0.
	lw $8, -16($fp) # Load local int i.
	lw $9, -24($fp) # Load tmp address _taddr0.
	sw $8, ($9) # Store value pointed by _taddr0 to int array element.
	lw $8, -44($fp) # Load tmp variable _tvar4.
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, 8($fp) # Load address of formal int array x.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -28($fp) # Store address to tmp address _taddr1.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -16($fp) # Load local int i.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	lw $9, -28($fp) # Load tmp address _taddr1.
	sw $8, ($9) # Store value pointed by _taddr1 to int array element.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -16($fp) # Load local int i.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	li $9, 4 # Load int constant shorter than 16-bits
	mul $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	la $8, _a # Load address of global int array a.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -32($fp) # Store address to tmp address _taddr2.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -16($fp) # Load local int i.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	lw $9, -32($fp) # Load tmp address _taddr2.
	sw $8, ($9) # Store value pointed by _taddr2 to int array element.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -16($fp) # Load local int i.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	li $9, 4 # Load int constant shorter than 16-bits
	mul $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, 8($fp) # Load address of formal int array x.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -36($fp) # Store address to tmp address _taddr3.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -16($fp) # Load local int i.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	lw $9, -36($fp) # Load tmp address _taddr3.
	sw $8, ($9) # Store value pointed by _taddr3 to int array element.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -16($fp) # Load local int i.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	sw $8, -16($fp) # Store to local int i.
	.text
_L1:	li $8, 10 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -16($fp) # Load local int i.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	blt $8, $9, _L0
	.text
_L2:	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	sw $8, -20($fp) # Store to local int j.
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	sw $8, -16($fp) # Store to local int i.
	j _L4
	.text
_L3:	lw $8, -16($fp) # Load local int i.
	li $9, 4 # Load int constant shorter than 16-bits
	mul $10, $8, $9
	sw $10, -12($fp) # Store to tmp variable _tvar2.
	la $8, _a # Load address of global int array a.
	lw $9, -12($fp) # Load tmp variable _tvar2.
	add $10, $8, $9
	sw $10, -40($fp) # Store address to tmp address _taddr4.
	lw $8, -20($fp) # Load local int j.
	lw $10, -40($fp) # Load tmp address _taddr4.
	lw $9, ($10) # Load value of the int array element pointed by _taddr4.
	add $10, $8, $9
	sw $10, -12($fp) # Store to tmp variable _tvar2.
	lw $8, -12($fp) # Load tmp variable _tvar2.
	sw $8, -20($fp) # Store to local int j.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -12($fp) # Store to tmp variable _tvar2.
	lw $8, -16($fp) # Load local int i.
	lw $9, -12($fp) # Load tmp variable _tvar2.
	add $10, $8, $9
	sw $10, -12($fp) # Store to tmp variable _tvar2.
	lw $8, -12($fp) # Load tmp variable _tvar2.
	sw $8, -16($fp) # Store to local int i.
	.text
_L4:	li $8, 10 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -16($fp) # Load local int i.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	blt $8, $9, _L3
	.text
_L5:	lw $2, -20($fp) # Load local int j.
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
	la $sp, -8($sp) # Allocate stack frame for locals/tmps
	la $8, _a # Load address of global int array a.
	la $sp, -4($sp) # Allocate stack space for parameter a.
	sw $8, 0($sp) # Push the parameter value.
	jal _f
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -8($fp) # Store returned value to tmp variable _tvar19.
	lw $8, -8($fp) # Load tmp variable _tvar19.
	sw $8, -4($fp) # Store to local int x.
	lw $8, -4($fp) # Load local int x.
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

