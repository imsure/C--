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
_x:	.space 15
	.align 2
	.text
_copy:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -28($sp) # Allocate stack frame for locals/tmps
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, -12($fp) # Store to local int i.
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, -12($fp) # Store to local int i.
	j _L1
	.text
_L0:	lw $8, -12($fp) # Load local int i.
	li $9, 1 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, 8($fp) # Load address of formal char array b.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -24($fp) # Store address to tmp address _taddr2.
	lw $8, -12($fp) # Load local int i.
	li $9, 1 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, 12($fp) # Load address of formal char array a.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -20($fp) # Store address to tmp address _taddr1.
	lw $9, -20($fp) # Load tmp address _taddr1.
	lb $8, ($9) # Load value of the char array element pointed by _taddr1.
	lw $9, -24($fp) # Load tmp address _taddr2.
	sb $8, ($9) # Store value pointed by _taddr2 to char array element.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -12($fp) # Load local int i.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	sw $8, -12($fp) # Store to local int i.
	.text
_L1:	lw $8, -12($fp) # Load local int i.
	li $9, 1 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, 12($fp) # Load address of formal char array a.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -16($fp) # Store address to tmp address _taddr0.
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $9, -16($fp) # Load tmp address _taddr0.
	lb $8, ($9) # Load value of the char array element pointed by _taddr0.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	bgt $8, $9, _L0
	j _L2
	.text
_L2:	lw $8, -12($fp) # Load local int i.
	li $9, 1 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, 8($fp) # Load address of formal char array b.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -28($fp) # Store address to tmp address _taddr3.
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	lw $9, -28($fp) # Load tmp address _taddr3.
	sb $8, ($9) # Store value pointed by _taddr3 to char array element.
	lw $2, -12($fp) # Load local int i.
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
	sw $8, -4($fp) # Store to tmp variable _tvar1.
	lw $8, -4($fp) # Load tmp variable _tvar1.
	sw $8, -16($fp) # Store to local int i.
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar1.
	lw $8, -4($fp) # Load tmp variable _tvar1.
	sw $8, -12($fp) # Store to local int sum.
	j _L4
	.text
_L3:	lw $8, -16($fp) # Load local int i.
	li $9, 1 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar2.
	lw $8, 8($fp) # Load address of formal char array b.
	lw $9, -8($fp) # Load tmp variable _tvar2.
	add $10, $8, $9
	sw $10, -24($fp) # Store address to tmp address _taddr5.
	lw $8, -12($fp) # Load local int sum.
	lw $10, -24($fp) # Load tmp address _taddr5.
	lb $9, ($10) # Load value of the char array element pointed by _taddr5.
	add $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar2.
	lw $8, -8($fp) # Load tmp variable _tvar2.
	sw $8, -12($fp) # Store to local int sum.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar2.
	lw $8, -16($fp) # Load local int i.
	lw $9, -8($fp) # Load tmp variable _tvar2.
	add $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar2.
	lw $8, -8($fp) # Load tmp variable _tvar2.
	sw $8, -16($fp) # Store to local int i.
	.text
_L4:	lw $8, -16($fp) # Load local int i.
	li $9, 1 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar1.
	lw $8, 8($fp) # Load address of formal char array b.
	lw $9, -4($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -20($fp) # Store address to tmp address _taddr4.
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar1.
	lw $9, -20($fp) # Load tmp address _taddr4.
	lb $8, ($9) # Load value of the char array element pointed by _taddr4.
	lw $9, -4($fp) # Load tmp variable _tvar1.
	bgt $8, $9, _L3
	j _L5
	.text
_L5:	lw $2, -12($fp) # Load local int sum.
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.
	.data
__tstr0:	.asciiz "hello world"
	.align 2
__tstr1:	.asciiz "\n"
	.align 2
	.text
main:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -8($sp) # Allocate stack frame for locals/tmps
	la $8, __tstr0 # Load string const address _tstr0.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr0.
	sw $8, 0($sp) # Push the parameter value.
	la $8, _x # Load address of global char array x.
	la $sp, -4($sp) # Allocate stack space for parameter x.
	sw $8, 0($sp) # Push the parameter value.
	jal _copy
	la $sp, 8($sp) # Pop parameters off the stack.
	sw $2, -4($fp) # Store returned value to tmp variable _tvar2.
	lw $8, -4($fp) # Load tmp variable _tvar2.
	sw $8, -8($fp) # Store to local int y.
	la $8, _x # Load address of global char array x.
	la $sp, -4($sp) # Allocate stack space for parameter x.
	sw $8, 0($sp) # Push the parameter value.
	jal _sum
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -4($fp) # Store returned value to tmp variable _tvar2.
	lw $8, -8($fp) # Load local int y.
	lw $9, -4($fp) # Load tmp variable _tvar2.
	add $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar2.
	lw $8, -4($fp) # Load tmp variable _tvar2.
	sw $8, -8($fp) # Store to local int y.
	lw $8, -8($fp) # Load local int y.
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
