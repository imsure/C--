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
	li $8, 0 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	li $9, 4 # Load int constant shorter than 16-bits
	mul $10, $11, $9
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	la $8, -32($fp) # Load address of local int array x.
	add $10, $8, $11
	sw $10, -36($fp) # Store address to tmp address _taddr0.
	li $8, 0 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	lw $12, -36($fp) # Load tmp address _taddr0.
	sw $11, ($12) # Store value pointed by _taddr0 to int array element.
	li $8, 0 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	li $9, 1 # Load int constant shorter than 16-bits
	mul $10, $11, $9
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	la $8, _y # Load address of global char array y.
	add $10, $8, $11
	sw $10, -40($fp) # Store address to tmp address _taddr1.
	li $8, 1 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	lw $12, -40($fp) # Load tmp address _taddr1.
	sb $11, ($12) # Store value pointed by _taddr1 to char array element.
	li $8, 1 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	li $9, 4 # Load int constant shorter than 16-bits
	mul $10, $11, $9
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	la $8, -32($fp) # Load address of local int array x.
	add $10, $8, $11
	sw $10, -44($fp) # Store address to tmp address _taddr2.
	li $8, 1 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	lw $12, -44($fp) # Load tmp address _taddr2.
	sw $11, ($12) # Store value pointed by _taddr2 to int array element.
	li $8, 1 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	li $9, 1 # Load int constant shorter than 16-bits
	mul $10, $11, $9
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	la $8, _y # Load address of global char array y.
	add $10, $8, $11
	sw $10, -48($fp) # Store address to tmp address _taddr3.
	li $8, 2 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	lw $12, -48($fp) # Load tmp address _taddr3.
	sb $11, ($12) # Store value pointed by _taddr3 to char array element.
	li $8, 2 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	li $9, 4 # Load int constant shorter than 16-bits
	mul $10, $11, $9
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	la $8, -32($fp) # Load address of local int array x.
	add $10, $8, $11
	sw $10, -52($fp) # Store address to tmp address _taddr4.
	li $8, 2 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	lw $12, -52($fp) # Load tmp address _taddr4.
	sw $11, ($12) # Store value pointed by _taddr4 to int array element.
	li $8, 2 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	li $9, 1 # Load int constant shorter than 16-bits
	mul $10, $11, $9
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	la $8, _y # Load address of global char array y.
	add $10, $8, $11
	sw $10, -56($fp) # Store address to tmp address _taddr5.
	li $8, 3 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	lw $12, -56($fp) # Load tmp address _taddr5.
	sb $11, ($12) # Store value pointed by _taddr5 to char array element.
	li $8, 3 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	li $9, 4 # Load int constant shorter than 16-bits
	mul $10, $11, $9
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	la $8, -32($fp) # Load address of local int array x.
	add $10, $8, $11
	sw $10, -60($fp) # Store address to tmp address _taddr6.
	li $8, 3 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	lw $12, -60($fp) # Load tmp address _taddr6.
	sw $11, ($12) # Store value pointed by _taddr6 to int array element.
	li $8, 3 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	li $9, 1 # Load int constant shorter than 16-bits
	mul $10, $11, $9
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	la $8, _y # Load address of global char array y.
	add $10, $8, $11
	sw $10, -64($fp) # Store address to tmp address _taddr7.
	li $8, 4 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	lw $12, -64($fp) # Load tmp address _taddr7.
	sb $11, ($12) # Store value pointed by _taddr7 to char array element.
	li $8, 4 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	li $9, 4 # Load int constant shorter than 16-bits
	mul $10, $11, $9
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	la $8, -32($fp) # Load address of local int array x.
	add $10, $8, $11
	sw $10, -68($fp) # Store address to tmp address _taddr8.
	li $8, 4 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	lw $12, -68($fp) # Load tmp address _taddr8.
	sw $11, ($12) # Store value pointed by _taddr8 to int array element.
	li $8, 4 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	li $9, 1 # Load int constant shorter than 16-bits
	mul $10, $11, $9
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	la $8, _y # Load address of global char array y.
	add $10, $8, $11
	sw $10, -72($fp) # Store address to tmp address _taddr9.
	li $8, 55 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	lw $12, -72($fp) # Load tmp address _taddr9.
	sb $11, ($12) # Store value pointed by _taddr9 to char array element.
	li $8, 2 # Load int constant shorter than 16-bits
	
	## value of $11 = 2
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	li $8, 1 # Load int constant shorter than 16-bits
	
	## value of $11 = 1, _tvar0 got overwritten, this causes 2*x[1] become: 1*x[1]
	## so _tvar0 and _tvar1 should not colored by the same register!!!!!
	move $11, $8 # Store local tmp _tvar1 to its pre-assigned register.
	
	li $9, 4 # Load int constant shorter than 16-bits
	mul $10, $11, $9
	move $11, $10 # Store local tmp _tvar1 to its pre-assigned register.
	la $8, -32($fp) # Load address of local int array x.
	add $10, $8, $11
	sw $10, -76($fp) # Store address to tmp address _taddr10.
	lw $10, -76($fp) # Load tmp address _taddr10.
	lw $9, ($10) # Load value of the int array element pointed by _taddr10.
	mul $10, $11, $9
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	li $8, 1 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar1 to its pre-assigned register.
	sub $10, $11, $11
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	li $9, 4 # Load int constant shorter than 16-bits
	mul $10, $11, $9
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	la $8, -32($fp) # Load address of local int array x.
	add $10, $8, $11
	sw $10, -80($fp) # Store address to tmp address _taddr11.
	li $8, 4 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	li $9, 1 # Load int constant shorter than 16-bits
	mul $10, $11, $9
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	la $8, _y # Load address of global char array y.
	add $10, $8, $11
	sw $10, -84($fp) # Store address to tmp address _taddr12.
	li $8, 2 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	li $9, 4 # Load int constant shorter than 16-bits
	mul $10, $11, $9
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	la $8, -32($fp) # Load address of local int array x.
	add $10, $8, $11
	sw $10, -88($fp) # Store address to tmp address _taddr13.
	li $8, 0 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	li $9, 1 # Load int constant shorter than 16-bits
	mul $10, $11, $9
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	la $8, _y # Load address of global char array y.
	add $10, $8, $11
	sw $10, -92($fp) # Store address to tmp address _taddr14.
	lw $9, -88($fp) # Load tmp address _taddr13.
	lw $8, ($9) # Load value of the int array element pointed by _taddr13.
	lw $10, -92($fp) # Load tmp address _taddr14.
	lb $9, ($10) # Load value of the char array element pointed by _taddr14.
	add $10, $8, $9
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	li $9, 1 # Load int constant shorter than 16-bits
	mul $10, $11, $9
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	la $8, _y # Load address of global char array y.
	add $10, $8, $11
	sw $10, -96($fp) # Store address to tmp address _taddr15.
	li $8, 1 # Load int constant shorter than 16-bits
	move $11, $8 # Store local tmp _tvar0 to its pre-assigned register.
	li $9, 4 # Load int constant shorter than 16-bits
	mul $10, $11, $9
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	la $8, -32($fp) # Load address of local int array x.
	add $10, $8, $11
	sw $10, -100($fp) # Store address to tmp address _taddr16.
	lw $9, -96($fp) # Load tmp address _taddr15.
	lb $8, ($9) # Load value of the char array element pointed by _taddr15.
	lw $10, -100($fp) # Load tmp address _taddr16.
	lw $9, ($10) # Load value of the int array element pointed by _taddr16.
	add $10, $8, $9
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	lw $9, -84($fp) # Load tmp address _taddr12.
	lb $8, ($9) # Load value of the char array element pointed by _taddr12.
	div $10, $8, $11
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	lw $9, -80($fp) # Load tmp address _taddr11.
	lw $8, ($9) # Load value of the int array element pointed by _taddr11.
	add $10, $8, $11
	move $11, $10 # Store local tmp _tvar0 to its pre-assigned register.
	move $11, $11 # Store local int u to its pre-assigned register.
	la $sp, -4($sp) # Allocate stack space for parameter u.
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

