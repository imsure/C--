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

id:
	Enter id  0 
	Return x 

	.data
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
main:
	Enter main  148 
	_tvar0 = 0 
	i = _tvar0 
	goto _L1
_L0:
	_tvar1 = i * 4 
	_taddr0 = x + _tvar1
	*_taddr0(int) = i 
	_tvar1 = 1 
	_tvar1 = i + _tvar1
	i = _tvar1 
_L1:
	_tvar0 = 10 
	if ( i < _tvar0 ) goto _L0
	goto _L2
_L2:
	_tvar5 = 5 
	Param _tvar5 
	Call id  1 
	Retrieve _tvar4 
	_tvar5 = _tvar4 * 4 
	_taddr1 = x + _tvar5
	Param *_taddr1(int) 
	Call id  1 
	Retrieve _tvar3 
	_tvar4 = _tvar3 * 4 
	_taddr2 = x + _tvar4
	Param *_taddr2(int) 
	Call id  1 
	Retrieve _tvar2 
	_tvar3 = _tvar2 * 4 
	_taddr3 = x + _tvar3
	Param *_taddr3(int) 
	Call id  1 
	Retrieve _tvar1 
	_tvar2 = _tvar1 * 4 
	_taddr4 = x + _tvar2
	res = *_taddr4(int) 
	_tvar6 = 0 
	Param _tvar6 
	Call id  1 
	Retrieve _tvar5 
	_tvar7 = 1 
	_tvar6 = _tvar5 + _tvar7
	_tvar6 = _tvar6 * 4 
	_taddr5 = x + _tvar6
	_tvar6 = 1 
	_tvar6 = *_taddr5(int) + _tvar6
	Param _tvar6 
	Call id  1 
	Retrieve _tvar4 
	_tvar7 = 1 
	_tvar6 = _tvar4 + _tvar7
	_tvar6 = _tvar6 * 4 
	_taddr6 = x + _tvar6
	_tvar6 = 1 
	_tvar6 = *_taddr6(int) + _tvar6
	Param _tvar6 
	Call id  1 
	Retrieve _tvar3 
	_tvar7 = 1 
	_tvar6 = _tvar3 + _tvar7
	_tvar6 = _tvar6 * 4 
	_taddr7 = x + _tvar6
	_tvar6 = 1 
	_tvar6 = *_taddr7(int) + _tvar6
	Param _tvar6 
	Call id  1 
	Retrieve _tvar2 
	_tvar7 = 1 
	_tvar6 = _tvar2 + _tvar7
	_tvar6 = _tvar6 * 4 
	_taddr8 = x + _tvar6
	_tvar2 = 1 
	_tvar2 = res + _tvar2
	*_taddr8(int) = _tvar2 
	_tvar10 = 0 
	Param _tvar10 
	Call id  1 
	Retrieve _tvar9 
	_tvar11 = 1 
	_tvar10 = _tvar9 + _tvar11
	_tvar10 = _tvar10 * 4 
	_taddr9 = x + _tvar10
	_tvar10 = 1 
	_tvar10 = *_taddr9(int) + _tvar10
	Param _tvar10 
	Call id  1 
	Retrieve _tvar8 
	_tvar11 = 1 
	_tvar10 = _tvar8 + _tvar11
	_tvar10 = _tvar10 * 4 
	_taddr10 = x + _tvar10
	_tvar10 = 1 
	_tvar10 = *_taddr10(int) + _tvar10
	Param _tvar10 
	Call id  1 
	Retrieve _tvar7 
	_tvar11 = 1 
	_tvar10 = _tvar7 + _tvar11
	_tvar10 = _tvar10 * 4 
	_taddr11 = x + _tvar10
	_tvar10 = 1 
	_tvar10 = *_taddr11(int) + _tvar10
	Param _tvar10 
	Call id  1 
	Retrieve _tvar6 
	_tvar11 = 1 
	_tvar10 = _tvar6 + _tvar11
	_tvar10 = _tvar10 * 4 
	_taddr12 = x + _tvar10
	res = *_taddr12(int) 
	Param res 
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
	la $sp, -148($sp) # Allocate stack frame for locals/tmps
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar0.
	lw $8, -8($fp) # Load tmp variable _tvar0.
	sw $8, -48($fp) # Store to local int i.
	j _L1
	.text
_L0:	lw $8, -48($fp) # Load local int i.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -12($fp) # Store to tmp variable _tvar1.
	la $8, -88($fp) # Load address of local int array x.
	lw $9, -12($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -100($fp) # Store address to tmp address _taddr0.
	lw $8, -48($fp) # Load local int i.
	lw $9, -100($fp) # Load tmp address _taddr0.
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
	la $8, -88($fp) # Load address of local int array x.
	lw $9, -28($fp) # Load tmp variable _tvar5.
	add $10, $8, $9
	sw $10, -104($fp) # Store address to tmp address _taddr1.
	lw $9, -104($fp) # Load tmp address _taddr1.
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
	la $8, -88($fp) # Load address of local int array x.
	lw $9, -24($fp) # Load tmp variable _tvar4.
	add $10, $8, $9
	sw $10, -108($fp) # Store address to tmp address _taddr2.
	lw $9, -108($fp) # Load tmp address _taddr2.
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
	la $8, -88($fp) # Load address of local int array x.
	lw $9, -20($fp) # Load tmp variable _tvar3.
	add $10, $8, $9
	sw $10, -112($fp) # Store address to tmp address _taddr3.
	lw $9, -112($fp) # Load tmp address _taddr3.
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
	la $8, -88($fp) # Load address of local int array x.
	lw $9, -16($fp) # Load tmp variable _tvar2.
	add $10, $8, $9
	sw $10, -116($fp) # Store address to tmp address _taddr4.
	lw $9, -116($fp) # Load tmp address _taddr4.
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
	la $8, -88($fp) # Load address of local int array x.
	lw $9, -32($fp) # Load tmp variable _tvar6.
	add $10, $8, $9
	sw $10, -120($fp) # Store address to tmp address _taddr5.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -32($fp) # Store to tmp variable _tvar6.
	lw $9, -120($fp) # Load tmp address _taddr5.
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
	la $8, -88($fp) # Load address of local int array x.
	lw $9, -32($fp) # Load tmp variable _tvar6.
	add $10, $8, $9
	sw $10, -124($fp) # Store address to tmp address _taddr6.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -32($fp) # Store to tmp variable _tvar6.
	lw $9, -124($fp) # Load tmp address _taddr6.
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
	la $8, -88($fp) # Load address of local int array x.
	lw $9, -32($fp) # Load tmp variable _tvar6.
	add $10, $8, $9
	sw $10, -128($fp) # Store address to tmp address _taddr7.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -32($fp) # Store to tmp variable _tvar6.
	lw $9, -128($fp) # Load tmp address _taddr7.
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
	la $8, -88($fp) # Load address of local int array x.
	lw $9, -32($fp) # Load tmp variable _tvar6.
	add $10, $8, $9
	sw $10, -132($fp) # Store address to tmp address _taddr8.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -16($fp) # Store to tmp variable _tvar2.
	lw $8, -4($fp) # Load local int res.
	lw $9, -16($fp) # Load tmp variable _tvar2.
	add $10, $8, $9
	sw $10, -16($fp) # Store to tmp variable _tvar2.
	lw $8, -16($fp) # Load tmp variable _tvar2.
	lw $9, -132($fp) # Load tmp address _taddr8.
	sw $8, ($9) # Store value pointed by _taddr8 to int array element.
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -92($fp) # Store to tmp variable _tvar10.
	lw $8, -92($fp) # Load tmp variable _tvar10.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar10.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -44($fp) # Store returned value to tmp variable _tvar9.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -96($fp) # Store to tmp variable _tvar11.
	lw $8, -44($fp) # Load tmp variable _tvar9.
	lw $9, -96($fp) # Load tmp variable _tvar11.
	add $10, $8, $9
	sw $10, -92($fp) # Store to tmp variable _tvar10.
	lw $8, -92($fp) # Load tmp variable _tvar10.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -92($fp) # Store to tmp variable _tvar10.
	la $8, -88($fp) # Load address of local int array x.
	lw $9, -92($fp) # Load tmp variable _tvar10.
	add $10, $8, $9
	sw $10, -136($fp) # Store address to tmp address _taddr9.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -92($fp) # Store to tmp variable _tvar10.
	lw $9, -136($fp) # Load tmp address _taddr9.
	lw $8, ($9) # Load value of the int array element pointed by _taddr9.
	lw $9, -92($fp) # Load tmp variable _tvar10.
	add $10, $8, $9
	sw $10, -92($fp) # Store to tmp variable _tvar10.
	lw $8, -92($fp) # Load tmp variable _tvar10.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar10.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -40($fp) # Store returned value to tmp variable _tvar8.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -96($fp) # Store to tmp variable _tvar11.
	lw $8, -40($fp) # Load tmp variable _tvar8.
	lw $9, -96($fp) # Load tmp variable _tvar11.
	add $10, $8, $9
	sw $10, -92($fp) # Store to tmp variable _tvar10.
	lw $8, -92($fp) # Load tmp variable _tvar10.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -92($fp) # Store to tmp variable _tvar10.
	la $8, -88($fp) # Load address of local int array x.
	lw $9, -92($fp) # Load tmp variable _tvar10.
	add $10, $8, $9
	sw $10, -140($fp) # Store address to tmp address _taddr10.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -92($fp) # Store to tmp variable _tvar10.
	lw $9, -140($fp) # Load tmp address _taddr10.
	lw $8, ($9) # Load value of the int array element pointed by _taddr10.
	lw $9, -92($fp) # Load tmp variable _tvar10.
	add $10, $8, $9
	sw $10, -92($fp) # Store to tmp variable _tvar10.
	lw $8, -92($fp) # Load tmp variable _tvar10.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar10.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -36($fp) # Store returned value to tmp variable _tvar7.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -96($fp) # Store to tmp variable _tvar11.
	lw $8, -36($fp) # Load tmp variable _tvar7.
	lw $9, -96($fp) # Load tmp variable _tvar11.
	add $10, $8, $9
	sw $10, -92($fp) # Store to tmp variable _tvar10.
	lw $8, -92($fp) # Load tmp variable _tvar10.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -92($fp) # Store to tmp variable _tvar10.
	la $8, -88($fp) # Load address of local int array x.
	lw $9, -92($fp) # Load tmp variable _tvar10.
	add $10, $8, $9
	sw $10, -144($fp) # Store address to tmp address _taddr11.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -92($fp) # Store to tmp variable _tvar10.
	lw $9, -144($fp) # Load tmp address _taddr11.
	lw $8, ($9) # Load value of the int array element pointed by _taddr11.
	lw $9, -92($fp) # Load tmp variable _tvar10.
	add $10, $8, $9
	sw $10, -92($fp) # Store to tmp variable _tvar10.
	lw $8, -92($fp) # Load tmp variable _tvar10.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar10.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -32($fp) # Store returned value to tmp variable _tvar6.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -96($fp) # Store to tmp variable _tvar11.
	lw $8, -32($fp) # Load tmp variable _tvar6.
	lw $9, -96($fp) # Load tmp variable _tvar11.
	add $10, $8, $9
	sw $10, -92($fp) # Store to tmp variable _tvar10.
	lw $8, -92($fp) # Load tmp variable _tvar10.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -92($fp) # Store to tmp variable _tvar10.
	la $8, -88($fp) # Load address of local int array x.
	lw $9, -92($fp) # Load tmp variable _tvar10.
	add $10, $8, $9
	sw $10, -148($fp) # Store address to tmp address _taddr12.
	lw $9, -148($fp) # Load tmp address _taddr12.
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
