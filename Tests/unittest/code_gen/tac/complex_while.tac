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
	Enter main  52 
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
	_tvar0 = 5 
	if ( i < _tvar0 ) goto _L0
	goto _L2
_L2:
	_tvar1 = 123 
	res = _tvar1 
	goto _L4
_L3:
	_tvar1 = res * i
	res = _tvar1 
	_tvar1 = 1 
	_tvar1 = i - _tvar1
	i = _tvar1 
_L4:
	_tvar1 = 5 
	_tvar1 = i / _tvar1
	_tvar1 = _tvar1 * 4 
	_taddr1 = x + _tvar1
	_tvar1 = 4 
	_tvar1 = i / _tvar1
	_tvar1 = _tvar1 * 4 
	_taddr2 = x + _tvar1
	if ( *_taddr1(int) <= *_taddr1(int)  ) goto _L7
	goto _L3
_L7:
	_tvar1 = 4 
	_tvar1 = i / _tvar1
	_tvar1 = _tvar1 * 4 
	_taddr3 = x + _tvar1
	_tvar1 = 3 
	_tvar1 = i / _tvar1
	_tvar1 = _tvar1 * 4 
	_taddr4 = x + _tvar1
	if ( *_taddr3(int) <= *_taddr3(int)  ) goto _L6
	goto _L3
_L6:
	_tvar1 = 2 
	_tvar1 = i / _tvar1
	_tvar1 = _tvar1 * 4 
	_taddr5 = x + _tvar1
	_tvar1 = 3 
	_tvar1 = i / _tvar1
	_tvar1 = _tvar1 * 4 
	_taddr6 = x + _tvar1
	if ( *_taddr5(int) > *_taddr5(int)  ) goto _L3
	goto _L9
_L9:
	_tvar1 = 3 
	_tvar1 = i / _tvar1
	_tvar1 = _tvar1 * 4 
	_taddr7 = x + _tvar1
	_tvar1 = 4 
	_tvar1 = i / _tvar1
	_tvar1 = _tvar1 * 4 
	_taddr8 = x + _tvar1
	if ( *_taddr7(int) > *_taddr7(int)  ) goto _L3
	goto _L8
_L8:
	_tvar1 = 4 
	_tvar1 = i / _tvar1
	_tvar1 = _tvar1 * 4 
	_taddr9 = x + _tvar1
	_tvar1 = 5 
	_tvar1 = i / _tvar1
	_tvar1 = _tvar1 * 4 
	_taddr10 = x + _tvar1
	if ( *_taddr9(int) > *_taddr9(int)  ) goto _L3
	goto _L5
_L5:
	Param res 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

	.data
_res:	.space 4
__tstr0:	.asciiz "\n"
	.align 2
_i:	.space 4
_x:	.space 20
	.text
main:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -52($sp) # Allocate stack frame for locals/tmps
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _i # Store to global int i.
	j _L1
	.text
_L0:	lw $8, _i # Load global int i.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	la $8, _x # Load address of global int array x.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -12($fp) # Store address to tmp address _taddr0.
	lw $8, _i # Load global int i.
	lw $9, -12($fp) # Load tmp address _taddr0.
	sw $8, ($9) # Store value pointed by _taddr0 to int array element.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, _i # Load global int i.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	sw $8, _i # Store to global int i.
	.text
_L1:	li $8, 5 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, _i # Load global int i.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	blt $8, $9, _L0
	j _L2
	.text
_L2:	li $8, 123 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	sw $8, _res # Store to global int res.
	j _L4
	.text
_L3:	lw $8, _res # Load global int res.
	lw $9, _i # Load global int i.
	mul $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	sw $8, _res # Store to global int res.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, _i # Load global int i.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	sub $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	sw $8, _i # Store to global int i.
	.text
_L4:	li $8, 5 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, _i # Load global int i.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	div $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	la $8, _x # Load address of global int array x.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -16($fp) # Store address to tmp address _taddr1.
	li $8, 4 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, _i # Load global int i.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	div $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	la $8, _x # Load address of global int array x.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -20($fp) # Store address to tmp address _taddr2.
	lw $9, -16($fp) # Load tmp address _taddr1.
	lw $8, ($9) # Load value of the int array element pointed by _taddr1.
	lw $10, -20($fp) # Load tmp address _taddr2.
	lw $9, ($10) # Load value of the int array element pointed by _taddr2.
	ble $8, $9, _L7
	j _L3
	.text
_L7:	li $8, 4 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, _i # Load global int i.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	div $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	la $8, _x # Load address of global int array x.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -24($fp) # Store address to tmp address _taddr3.
	li $8, 3 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, _i # Load global int i.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	div $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	la $8, _x # Load address of global int array x.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -28($fp) # Store address to tmp address _taddr4.
	lw $9, -24($fp) # Load tmp address _taddr3.
	lw $8, ($9) # Load value of the int array element pointed by _taddr3.
	lw $10, -28($fp) # Load tmp address _taddr4.
	lw $9, ($10) # Load value of the int array element pointed by _taddr4.
	ble $8, $9, _L6
	j _L3
	.text
_L6:	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, _i # Load global int i.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	div $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	la $8, _x # Load address of global int array x.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -32($fp) # Store address to tmp address _taddr5.
	li $8, 3 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, _i # Load global int i.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	div $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	la $8, _x # Load address of global int array x.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -36($fp) # Store address to tmp address _taddr6.
	lw $9, -32($fp) # Load tmp address _taddr5.
	lw $8, ($9) # Load value of the int array element pointed by _taddr5.
	lw $10, -36($fp) # Load tmp address _taddr6.
	lw $9, ($10) # Load value of the int array element pointed by _taddr6.
	bgt $8, $9, _L3
	j _L9
	.text
_L9:	li $8, 3 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, _i # Load global int i.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	div $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	la $8, _x # Load address of global int array x.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -40($fp) # Store address to tmp address _taddr7.
	li $8, 4 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, _i # Load global int i.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	div $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	la $8, _x # Load address of global int array x.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -44($fp) # Store address to tmp address _taddr8.
	lw $9, -40($fp) # Load tmp address _taddr7.
	lw $8, ($9) # Load value of the int array element pointed by _taddr7.
	lw $10, -44($fp) # Load tmp address _taddr8.
	lw $9, ($10) # Load value of the int array element pointed by _taddr8.
	bgt $8, $9, _L3
	j _L8
	.text
_L8:	li $8, 4 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, _i # Load global int i.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	div $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	la $8, _x # Load address of global int array x.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -48($fp) # Store address to tmp address _taddr9.
	li $8, 5 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, _i # Load global int i.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	div $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	la $8, _x # Load address of global int array x.
	lw $9, -8($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -52($fp) # Store address to tmp address _taddr10.
	lw $9, -48($fp) # Load tmp address _taddr9.
	lw $8, ($9) # Load value of the int array element pointed by _taddr9.
	lw $10, -52($fp) # Load tmp address _taddr10.
	lw $9, ($10) # Load value of the int array element pointed by _taddr10.
	bgt $8, $9, _L3
	j _L5
	.text
_L5:	lw $8, _res # Load global int res.
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
