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

main:
	Enter main  128 
	_tvar0 = 0 
	_tvar0 = _tvar0 * 4 
	_taddr0 = x + _tvar0
	_tvar0 = 1 
	*_taddr0(int) = _tvar0 
	_tvar0 = 1 
	_tvar0 = _tvar0 * 4 
	_taddr1 = x + _tvar0
	_tvar0 = 2 
	*_taddr1(int) = _tvar0 
	_tvar0 = 2 
	_tvar0 = _tvar0 * 4 
	_taddr2 = x + _tvar0
	_tvar0 = 3 
	*_taddr2(int) = _tvar0 
	_tvar0 = 3 
	_tvar0 = _tvar0 * 4 
	_taddr3 = x + _tvar0
	_tvar0 = 4 
	*_taddr3(int) = _tvar0 
	_tvar0 = 4 
	_tvar0 = _tvar0 * 4 
	_taddr4 = x + _tvar0
	_tvar0 = 5 
	*_taddr4(int) = _tvar0 
	_tvar0 = 5 
	_tvar0 = _tvar0 * 4 
	_taddr5 = x + _tvar0
	_tvar0 = 6 
	*_taddr5(int) = _tvar0 
	_tvar0 = 6 
	_tvar0 = _tvar0 * 4 
	_taddr6 = x + _tvar0
	_tvar0 = 7 
	*_taddr6(int) = _tvar0 
	_tvar0 = 7 
	_tvar0 = _tvar0 * 4 
	_taddr7 = x + _tvar0
	_tvar0 = 8 
	*_taddr7(int) = _tvar0 
	_tvar0 = 8 
	_tvar0 = _tvar0 * 4 
	_taddr8 = x + _tvar0
	_tvar0 = 9 
	*_taddr8(int) = _tvar0 
	_tvar0 = 9 
	_tvar0 = _tvar0 * 4 
	_taddr9 = x + _tvar0
	_tvar0 = 10 
	*_taddr9(int) = _tvar0 
	_tvar0 = 0 
	_tvar0 = _tvar0 * 4 
	_taddr10 = x + _tvar0
	_tvar0 = *_taddr10(int) * 4 
	_taddr11 = x + _tvar0
	_tvar0 = *_taddr11(int) * 4 
	_taddr12 = x + _tvar0
	_tvar0 = *_taddr12(int) * 4 
	_taddr13 = x + _tvar0
	_tvar0 = *_taddr13(int) * 4 
	_taddr14 = x + _tvar0
	_tvar0 = *_taddr14(int) * 4 
	_taddr15 = x + _tvar0
	_tvar0 = *_taddr15(int) * 4 
	_taddr16 = x + _tvar0
	_tvar0 = *_taddr16(int) * 4 
	_taddr17 = x + _tvar0
	_tvar0 = *_taddr17(int) * 4 
	_taddr18 = x + _tvar0
	_tvar0 = *_taddr18(int) * 4 
	_taddr19 = x + _tvar0
	u = *_taddr19(int) 
	Param u 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

	.data
__tstr0:	.asciiz "\n"
	.align 2
	.text
main:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -128($sp) # Allocate stack frame for locals/tmps
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, -48($fp) # Load address of local int array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -52($fp) # Store address to tmp address _taddr0.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lw $9, -52($fp) # Load tmp address _taddr0.
	sw $8, ($9) # Store value pointed by _taddr0 to int array element.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, -48($fp) # Load address of local int array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -56($fp) # Store address to tmp address _taddr1.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lw $9, -56($fp) # Load tmp address _taddr1.
	sw $8, ($9) # Store value pointed by _taddr1 to int array element.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, -48($fp) # Load address of local int array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -60($fp) # Store address to tmp address _taddr2.
	li $8, 3 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lw $9, -60($fp) # Load tmp address _taddr2.
	sw $8, ($9) # Store value pointed by _taddr2 to int array element.
	li $8, 3 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, -48($fp) # Load address of local int array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -64($fp) # Store address to tmp address _taddr3.
	li $8, 4 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lw $9, -64($fp) # Load tmp address _taddr3.
	sw $8, ($9) # Store value pointed by _taddr3 to int array element.
	li $8, 4 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, -48($fp) # Load address of local int array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -68($fp) # Store address to tmp address _taddr4.
	li $8, 5 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lw $9, -68($fp) # Load tmp address _taddr4.
	sw $8, ($9) # Store value pointed by _taddr4 to int array element.
	li $8, 5 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, -48($fp) # Load address of local int array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -72($fp) # Store address to tmp address _taddr5.
	li $8, 6 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lw $9, -72($fp) # Load tmp address _taddr5.
	sw $8, ($9) # Store value pointed by _taddr5 to int array element.
	li $8, 6 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, -48($fp) # Load address of local int array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -76($fp) # Store address to tmp address _taddr6.
	li $8, 7 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lw $9, -76($fp) # Load tmp address _taddr6.
	sw $8, ($9) # Store value pointed by _taddr6 to int array element.
	li $8, 7 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, -48($fp) # Load address of local int array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -80($fp) # Store address to tmp address _taddr7.
	li $8, 8 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lw $9, -80($fp) # Load tmp address _taddr7.
	sw $8, ($9) # Store value pointed by _taddr7 to int array element.
	li $8, 8 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, -48($fp) # Load address of local int array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -84($fp) # Store address to tmp address _taddr8.
	li $8, 9 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lw $9, -84($fp) # Load tmp address _taddr8.
	sw $8, ($9) # Store value pointed by _taddr8 to int array element.
	li $8, 9 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, -48($fp) # Load address of local int array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -88($fp) # Store address to tmp address _taddr9.
	li $8, 10 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lw $9, -88($fp) # Load tmp address _taddr9.
	sw $8, ($9) # Store value pointed by _taddr9 to int array element.
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, -48($fp) # Load address of local int array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -92($fp) # Store address to tmp address _taddr10.
	lw $9, -92($fp) # Load tmp address _taddr10.
	lw $8, ($9) # Load value of the int array element pointed by _taddr10.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, -48($fp) # Load address of local int array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -96($fp) # Store address to tmp address _taddr11.
	lw $9, -96($fp) # Load tmp address _taddr11.
	lw $8, ($9) # Load value of the int array element pointed by _taddr11.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, -48($fp) # Load address of local int array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -100($fp) # Store address to tmp address _taddr12.
	lw $9, -100($fp) # Load tmp address _taddr12.
	lw $8, ($9) # Load value of the int array element pointed by _taddr12.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, -48($fp) # Load address of local int array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -104($fp) # Store address to tmp address _taddr13.
	lw $9, -104($fp) # Load tmp address _taddr13.
	lw $8, ($9) # Load value of the int array element pointed by _taddr13.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, -48($fp) # Load address of local int array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -108($fp) # Store address to tmp address _taddr14.
	lw $9, -108($fp) # Load tmp address _taddr14.
	lw $8, ($9) # Load value of the int array element pointed by _taddr14.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, -48($fp) # Load address of local int array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -112($fp) # Store address to tmp address _taddr15.
	lw $9, -112($fp) # Load tmp address _taddr15.
	lw $8, ($9) # Load value of the int array element pointed by _taddr15.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, -48($fp) # Load address of local int array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -116($fp) # Store address to tmp address _taddr16.
	lw $9, -116($fp) # Load tmp address _taddr16.
	lw $8, ($9) # Load value of the int array element pointed by _taddr16.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, -48($fp) # Load address of local int array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -120($fp) # Store address to tmp address _taddr17.
	lw $9, -120($fp) # Load tmp address _taddr17.
	lw $8, ($9) # Load value of the int array element pointed by _taddr17.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, -48($fp) # Load address of local int array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -124($fp) # Store address to tmp address _taddr18.
	lw $9, -124($fp) # Load tmp address _taddr18.
	lw $8, ($9) # Load value of the int array element pointed by _taddr18.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, -48($fp) # Load address of local int array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -128($fp) # Store address to tmp address _taddr19.
	lw $9, -128($fp) # Load tmp address _taddr19.
	lw $8, ($9) # Load value of the int array element pointed by _taddr19.
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
