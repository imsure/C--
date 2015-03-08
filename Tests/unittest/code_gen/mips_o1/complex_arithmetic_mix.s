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
_y:	.space 5
	.align 2

	.text
main:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -100($sp) # Allocate stack frame for locals/tmps
	la $8, -32($fp) # Load address of local int array x.
	li $9, 0 # Load size of array element for calculating its offset.
	add $10, $8, $9
	sw $10, -36($fp) # Store address to tmp address _taddr0.
	li $8, 0 # Load int constant shorter than 16-bits
	lw $9, -36($fp) # Load tmp address _taddr0.
	sw $8, ($9) # Store value pointed by _taddr0 to int array element.
	la $8, _y # Load address of global char array y.
	li $9, 0 # Load size of array element for calculating its offset.
	add $10, $8, $9
	sw $10, -40($fp) # Store address to tmp address _taddr1.
	li $8, 1 # Load int constant shorter than 16-bits
	lw $9, -40($fp) # Load tmp address _taddr1.
	sb $8, ($9) # Store value pointed by _taddr1 to char array element.
	la $8, -32($fp) # Load address of local int array x.
	li $9, 4 # Load size of array element for calculating its offset.
	add $10, $8, $9
	sw $10, -44($fp) # Store address to tmp address _taddr2.
	li $8, 1 # Load int constant shorter than 16-bits
	lw $9, -44($fp) # Load tmp address _taddr2.
	sw $8, ($9) # Store value pointed by _taddr2 to int array element.
	la $8, _y # Load address of global char array y.
	li $9, 1 # Load size of array element for calculating its offset.
	add $10, $8, $9
	sw $10, -48($fp) # Store address to tmp address _taddr3.
	li $8, 2 # Load int constant shorter than 16-bits
	lw $9, -48($fp) # Load tmp address _taddr3.
	sb $8, ($9) # Store value pointed by _taddr3 to char array element.
	la $8, -32($fp) # Load address of local int array x.
	li $9, 8 # Load size of array element for calculating its offset.
	add $10, $8, $9
	sw $10, -52($fp) # Store address to tmp address _taddr4.
	li $8, 2 # Load int constant shorter than 16-bits
	lw $9, -52($fp) # Load tmp address _taddr4.
	sw $8, ($9) # Store value pointed by _taddr4 to int array element.
	la $8, _y # Load address of global char array y.
	li $9, 2 # Load size of array element for calculating its offset.
	add $10, $8, $9
	sw $10, -56($fp) # Store address to tmp address _taddr5.
	li $8, 3 # Load int constant shorter than 16-bits
	lw $9, -56($fp) # Load tmp address _taddr5.
	sb $8, ($9) # Store value pointed by _taddr5 to char array element.
	la $8, -32($fp) # Load address of local int array x.
	li $9, 12 # Load size of array element for calculating its offset.
	add $10, $8, $9
	sw $10, -60($fp) # Store address to tmp address _taddr6.
	li $8, 3 # Load int constant shorter than 16-bits
	lw $9, -60($fp) # Load tmp address _taddr6.
	sw $8, ($9) # Store value pointed by _taddr6 to int array element.
	la $8, _y # Load address of global char array y.
	li $9, 3 # Load size of array element for calculating its offset.
	add $10, $8, $9
	sw $10, -64($fp) # Store address to tmp address _taddr7.
	li $8, 4 # Load int constant shorter than 16-bits
	lw $9, -64($fp) # Load tmp address _taddr7.
	sb $8, ($9) # Store value pointed by _taddr7 to char array element.
	la $8, -32($fp) # Load address of local int array x.
	li $9, 16 # Load size of array element for calculating its offset.
	add $10, $8, $9
	sw $10, -68($fp) # Store address to tmp address _taddr8.
	li $8, 4 # Load int constant shorter than 16-bits
	lw $9, -68($fp) # Load tmp address _taddr8.
	sw $8, ($9) # Store value pointed by _taddr8 to int array element.
	la $8, _y # Load address of global char array y.
	li $9, 4 # Load size of array element for calculating its offset.
	add $10, $8, $9
	sw $10, -72($fp) # Store address to tmp address _taddr9.
	li $8, 55 # Load int constant shorter than 16-bits
	lw $9, -72($fp) # Load tmp address _taddr9.
	sb $8, ($9) # Store value pointed by _taddr9 to char array element.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	la $8, -32($fp) # Load address of local int array x.
	li $9, 4 # Load size of array element for calculating its offset.
	add $10, $8, $9
	sw $10, -76($fp) # Store address to tmp address _taddr10.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lw $10, -76($fp) # Load tmp address _taddr10.
	lw $9, ($10) # Load value of the int array element pointed by _taddr10.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	sub $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, -32($fp) # Load address of local int array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -80($fp) # Store address to tmp address _taddr11.
	la $8, _y # Load address of global char array y.
	li $9, 4 # Load size of array element for calculating its offset.
	add $10, $8, $9
	sw $10, -84($fp) # Store address to tmp address _taddr12.
	la $8, -32($fp) # Load address of local int array x.
	li $9, 8 # Load size of array element for calculating its offset.
	add $10, $8, $9
	sw $10, -88($fp) # Store address to tmp address _taddr13.
	la $8, _y # Load address of global char array y.
	li $9, 0 # Load size of array element for calculating its offset.
	add $10, $8, $9
	sw $10, -92($fp) # Store address to tmp address _taddr14.
	lw $9, -88($fp) # Load tmp address _taddr13.
	lw $8, ($9) # Load value of the int array element pointed by _taddr13.
	lw $10, -92($fp) # Load tmp address _taddr14.
	lb $9, ($10) # Load value of the char array element pointed by _taddr14.
	add $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	li $9, 1 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, _y # Load address of global char array y.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -96($fp) # Store address to tmp address _taddr15.
	la $8, -32($fp) # Load address of local int array x.
	li $9, 4 # Load size of array element for calculating its offset.
	add $10, $8, $9
	sw $10, -100($fp) # Store address to tmp address _taddr16.
	lw $9, -96($fp) # Load tmp address _taddr15.
	lb $8, ($9) # Load value of the char array element pointed by _taddr15.
	lw $10, -100($fp) # Load tmp address _taddr16.
	lw $9, ($10) # Load value of the int array element pointed by _taddr16.
	add $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $9, -84($fp) # Load tmp address _taddr12.
	lb $8, ($9) # Load value of the char array element pointed by _taddr12.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	div $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $9, -80($fp) # Load tmp address _taddr11.
	lw $8, ($9) # Load value of the int array element pointed by _taddr11.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, -12($fp) # Store to local int u.
	lw $8, -12($fp) # Load local int u.
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

