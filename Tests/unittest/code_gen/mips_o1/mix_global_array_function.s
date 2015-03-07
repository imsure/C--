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
_x:	.space 40

	.text
_id:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -0($sp) # Allocate stack frame for locals/tmps
	lw $2, 8($fp) # Load int formal x.
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
	la $sp, -108($sp) # Allocate stack frame for locals/tmps
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -48($fp) # Store to local int i.
	j _L1
	.text
_L0:	lw $8, -48($fp) # Load local int i.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -12($fp) # Store to tmp variable _tvar1.
	la $8, _x # Load address of global int array x.
	lw $9, -12($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -60($fp) # Store address to tmp address _taddr0.
	lw $8, -48($fp) # Load local int i.
	lw $9, -60($fp) # Load tmp address _taddr0.
	sw $8, ($9) # Store value pointed by _taddr0 to int array element.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -12($fp) # Store to tmp variable _tvar1.
	lw $8, -48($fp) # Load local int i.
	lw $9, -12($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -12($fp) # Store to tmp variable _tvar1.
	lw $8, -12($fp) # Load tmp variable _tvar1.
	sw $8, -48($fp) # Store to local int i.
	.text
_L1:	li $8, 10 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar0.
	lw $8, -48($fp) # Load local int i.
	lw $9, -8($fp) # Load tmp variable _tvar0.
	blt $8, $9, _L0
	j _L2
	.text
_L2:	li $8, 5 # Load int constant shorter than 16-bits
	sw $8, -28($fp) # Store to tmp variable _tvar5.
	lw $8, -28($fp) # Load tmp variable _tvar5.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar5.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -24($fp) # Store returned value to tmp variable _tvar4.
	lw $8, -24($fp) # Load tmp variable _tvar4.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -28($fp) # Store to tmp variable _tvar5.
	la $8, _x # Load address of global int array x.
	lw $9, -28($fp) # Load tmp variable _tvar5.
	add $10, $8, $9
	sw $10, -64($fp) # Store address to tmp address _taddr1.
	lw $9, -64($fp) # Load tmp address _taddr1.
	lw $8, ($9) # Load value of the int array element pointed by _taddr1.
	la $sp, -4($sp) # Allocate stack space for parameter _taddr1.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -20($fp) # Store returned value to tmp variable _tvar3.
	lw $8, -20($fp) # Load tmp variable _tvar3.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -24($fp) # Store to tmp variable _tvar4.
	la $8, _x # Load address of global int array x.
	lw $9, -24($fp) # Load tmp variable _tvar4.
	add $10, $8, $9
	sw $10, -68($fp) # Store address to tmp address _taddr2.
	lw $9, -68($fp) # Load tmp address _taddr2.
	lw $8, ($9) # Load value of the int array element pointed by _taddr2.
	la $sp, -4($sp) # Allocate stack space for parameter _taddr2.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -16($fp) # Store returned value to tmp variable _tvar2.
	lw $8, -16($fp) # Load tmp variable _tvar2.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -20($fp) # Store to tmp variable _tvar3.
	la $8, _x # Load address of global int array x.
	lw $9, -20($fp) # Load tmp variable _tvar3.
	add $10, $8, $9
	sw $10, -72($fp) # Store address to tmp address _taddr3.
	lw $9, -72($fp) # Load tmp address _taddr3.
	lw $8, ($9) # Load value of the int array element pointed by _taddr3.
	la $sp, -4($sp) # Allocate stack space for parameter _taddr3.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -12($fp) # Store returned value to tmp variable _tvar1.
	lw $8, -12($fp) # Load tmp variable _tvar1.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -16($fp) # Store to tmp variable _tvar2.
	la $8, _x # Load address of global int array x.
	lw $9, -16($fp) # Load tmp variable _tvar2.
	add $10, $8, $9
	sw $10, -76($fp) # Store address to tmp address _taddr4.
	lw $9, -76($fp) # Load tmp address _taddr4.
	lw $8, ($9) # Load value of the int array element pointed by _taddr4.
	sw $8, -4($fp) # Store to local int res.
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -32($fp) # Store to tmp variable _tvar6.
	lw $8, -32($fp) # Load tmp variable _tvar6.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar6.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -28($fp) # Store returned value to tmp variable _tvar5.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -36($fp) # Store to tmp variable _tvar7.
	lw $8, -28($fp) # Load tmp variable _tvar5.
	lw $9, -36($fp) # Load tmp variable _tvar7.
	add $10, $8, $9
	sw $10, -32($fp) # Store to tmp variable _tvar6.
	lw $8, -32($fp) # Load tmp variable _tvar6.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -32($fp) # Store to tmp variable _tvar6.
	la $8, _x # Load address of global int array x.
	lw $9, -32($fp) # Load tmp variable _tvar6.
	add $10, $8, $9
	sw $10, -80($fp) # Store address to tmp address _taddr5.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -32($fp) # Store to tmp variable _tvar6.
	lw $9, -80($fp) # Load tmp address _taddr5.
	lw $8, ($9) # Load value of the int array element pointed by _taddr5.
	lw $9, -32($fp) # Load tmp variable _tvar6.
	add $10, $8, $9
	sw $10, -32($fp) # Store to tmp variable _tvar6.
	lw $8, -32($fp) # Load tmp variable _tvar6.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar6.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -24($fp) # Store returned value to tmp variable _tvar4.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -36($fp) # Store to tmp variable _tvar7.
	lw $8, -24($fp) # Load tmp variable _tvar4.
	lw $9, -36($fp) # Load tmp variable _tvar7.
	add $10, $8, $9
	sw $10, -32($fp) # Store to tmp variable _tvar6.
	lw $8, -32($fp) # Load tmp variable _tvar6.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -32($fp) # Store to tmp variable _tvar6.
	la $8, _x # Load address of global int array x.
	lw $9, -32($fp) # Load tmp variable _tvar6.
	add $10, $8, $9
	sw $10, -84($fp) # Store address to tmp address _taddr6.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -32($fp) # Store to tmp variable _tvar6.
	lw $9, -84($fp) # Load tmp address _taddr6.
	lw $8, ($9) # Load value of the int array element pointed by _taddr6.
	lw $9, -32($fp) # Load tmp variable _tvar6.
	add $10, $8, $9
	sw $10, -32($fp) # Store to tmp variable _tvar6.
	lw $8, -32($fp) # Load tmp variable _tvar6.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar6.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -20($fp) # Store returned value to tmp variable _tvar3.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -36($fp) # Store to tmp variable _tvar7.
	lw $8, -20($fp) # Load tmp variable _tvar3.
	lw $9, -36($fp) # Load tmp variable _tvar7.
	add $10, $8, $9
	sw $10, -32($fp) # Store to tmp variable _tvar6.
	lw $8, -32($fp) # Load tmp variable _tvar6.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -32($fp) # Store to tmp variable _tvar6.
	la $8, _x # Load address of global int array x.
	lw $9, -32($fp) # Load tmp variable _tvar6.
	add $10, $8, $9
	sw $10, -88($fp) # Store address to tmp address _taddr7.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -32($fp) # Store to tmp variable _tvar6.
	lw $9, -88($fp) # Load tmp address _taddr7.
	lw $8, ($9) # Load value of the int array element pointed by _taddr7.
	lw $9, -32($fp) # Load tmp variable _tvar6.
	add $10, $8, $9
	sw $10, -32($fp) # Store to tmp variable _tvar6.
	lw $8, -32($fp) # Load tmp variable _tvar6.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar6.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -16($fp) # Store returned value to tmp variable _tvar2.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -36($fp) # Store to tmp variable _tvar7.
	lw $8, -16($fp) # Load tmp variable _tvar2.
	lw $9, -36($fp) # Load tmp variable _tvar7.
	add $10, $8, $9
	sw $10, -32($fp) # Store to tmp variable _tvar6.
	lw $8, -32($fp) # Load tmp variable _tvar6.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -32($fp) # Store to tmp variable _tvar6.
	la $8, _x # Load address of global int array x.
	lw $9, -32($fp) # Load tmp variable _tvar6.
	add $10, $8, $9
	sw $10, -92($fp) # Store address to tmp address _taddr8.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -16($fp) # Store to tmp variable _tvar2.
	lw $8, -4($fp) # Load local int res.
	lw $9, -16($fp) # Load tmp variable _tvar2.
	add $10, $8, $9
	sw $10, -16($fp) # Store to tmp variable _tvar2.
	lw $8, -16($fp) # Load tmp variable _tvar2.
	lw $9, -92($fp) # Load tmp address _taddr8.
	sw $8, ($9) # Store value pointed by _taddr8 to int array element.
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -52($fp) # Store to tmp variable _tvar10.
	lw $8, -52($fp) # Load tmp variable _tvar10.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar10.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -44($fp) # Store returned value to tmp variable _tvar9.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -56($fp) # Store to tmp variable _tvar11.
	lw $8, -44($fp) # Load tmp variable _tvar9.
	lw $9, -56($fp) # Load tmp variable _tvar11.
	add $10, $8, $9
	sw $10, -52($fp) # Store to tmp variable _tvar10.
	lw $8, -52($fp) # Load tmp variable _tvar10.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -52($fp) # Store to tmp variable _tvar10.
	la $8, _x # Load address of global int array x.
	lw $9, -52($fp) # Load tmp variable _tvar10.
	add $10, $8, $9
	sw $10, -96($fp) # Store address to tmp address _taddr9.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -52($fp) # Store to tmp variable _tvar10.
	lw $9, -96($fp) # Load tmp address _taddr9.
	lw $8, ($9) # Load value of the int array element pointed by _taddr9.
	lw $9, -52($fp) # Load tmp variable _tvar10.
	add $10, $8, $9
	sw $10, -52($fp) # Store to tmp variable _tvar10.
	lw $8, -52($fp) # Load tmp variable _tvar10.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar10.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -40($fp) # Store returned value to tmp variable _tvar8.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -56($fp) # Store to tmp variable _tvar11.
	lw $8, -40($fp) # Load tmp variable _tvar8.
	lw $9, -56($fp) # Load tmp variable _tvar11.
	add $10, $8, $9
	sw $10, -52($fp) # Store to tmp variable _tvar10.
	lw $8, -52($fp) # Load tmp variable _tvar10.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -52($fp) # Store to tmp variable _tvar10.
	la $8, _x # Load address of global int array x.
	lw $9, -52($fp) # Load tmp variable _tvar10.
	add $10, $8, $9
	sw $10, -100($fp) # Store address to tmp address _taddr10.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -52($fp) # Store to tmp variable _tvar10.
	lw $9, -100($fp) # Load tmp address _taddr10.
	lw $8, ($9) # Load value of the int array element pointed by _taddr10.
	lw $9, -52($fp) # Load tmp variable _tvar10.
	add $10, $8, $9
	sw $10, -52($fp) # Store to tmp variable _tvar10.
	lw $8, -52($fp) # Load tmp variable _tvar10.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar10.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -36($fp) # Store returned value to tmp variable _tvar7.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -56($fp) # Store to tmp variable _tvar11.
	lw $8, -36($fp) # Load tmp variable _tvar7.
	lw $9, -56($fp) # Load tmp variable _tvar11.
	add $10, $8, $9
	sw $10, -52($fp) # Store to tmp variable _tvar10.
	lw $8, -52($fp) # Load tmp variable _tvar10.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -52($fp) # Store to tmp variable _tvar10.
	la $8, _x # Load address of global int array x.
	lw $9, -52($fp) # Load tmp variable _tvar10.
	add $10, $8, $9
	sw $10, -104($fp) # Store address to tmp address _taddr11.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -52($fp) # Store to tmp variable _tvar10.
	lw $9, -104($fp) # Load tmp address _taddr11.
	lw $8, ($9) # Load value of the int array element pointed by _taddr11.
	lw $9, -52($fp) # Load tmp variable _tvar10.
	add $10, $8, $9
	sw $10, -52($fp) # Store to tmp variable _tvar10.
	lw $8, -52($fp) # Load tmp variable _tvar10.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar10.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -32($fp) # Store returned value to tmp variable _tvar6.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -56($fp) # Store to tmp variable _tvar11.
	lw $8, -32($fp) # Load tmp variable _tvar6.
	lw $9, -56($fp) # Load tmp variable _tvar11.
	add $10, $8, $9
	sw $10, -52($fp) # Store to tmp variable _tvar10.
	lw $8, -52($fp) # Load tmp variable _tvar10.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -52($fp) # Store to tmp variable _tvar10.
	la $8, _x # Load address of global int array x.
	lw $9, -52($fp) # Load tmp variable _tvar10.
	add $10, $8, $9
	sw $10, -108($fp) # Store address to tmp address _taddr12.
	lw $9, -108($fp) # Load tmp address _taddr12.
	lw $8, ($9) # Load value of the int array element pointed by _taddr12.
	sw $8, -4($fp) # Store to local int res.
	lw $8, -4($fp) # Load local int res.
	la $sp, -4($sp) # Allocate stack space for parameter res.
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

