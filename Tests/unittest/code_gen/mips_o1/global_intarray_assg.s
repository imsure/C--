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
_x:	.space 40
_y:	.space 40

	.text
main:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -24($sp) # Allocate stack frame for locals/tmps
	la $8, _y # Load address of global int array y.
	li $9, 28 # Load size of array element for calculating its offset.
	add $10, $8, $9
	sw $10, -12($fp) # Store address to tmp address _taddr0.
	li $8, 1234 # Load int constant shorter than 16-bits
	lw $9, -12($fp) # Load tmp address _taddr0.
	sw $8, ($9) # Store value pointed by _taddr0 to int array element.
	la $8, _x # Load address of global int array x.
	li $9, 0 # Load size of array element for calculating its offset.
	add $10, $8, $9
	sw $10, -20($fp) # Store address to tmp address _taddr2.
	la $8, _y # Load address of global int array y.
	li $9, 28 # Load size of array element for calculating its offset.
	add $10, $8, $9
	sw $10, -16($fp) # Store address to tmp address _taddr1.
	lw $9, -16($fp) # Load tmp address _taddr1.
	lw $8, ($9) # Load value of the int array element pointed by _taddr1.
	lw $9, -20($fp) # Load tmp address _taddr2.
	sw $8, ($9) # Store value pointed by _taddr2 to int array element.
	la $8, _x # Load address of global int array x.
	li $9, 0 # Load size of array element for calculating its offset.
	add $10, $8, $9
	sw $10, -24($fp) # Store address to tmp address _taddr3.
	lw $9, -24($fp) # Load tmp address _taddr3.
	lw $8, ($9) # Load value of the int array element pointed by _taddr3.
	sw $8, -8($fp) # Store to local int u.
	lw $8, -8($fp) # Load local int u.
	la $sp, -4($sp) # Allocate stack space for parameter u.
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

