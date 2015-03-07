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
	Enter main  28 
	_tvar0 = 1 
	n = _tvar0 
	goto _L1
_L0:
	_tvar1 = n * 1 
	_taddr0 = A + _tvar1
	*_taddr0(char) = n 
	_tvar1 = 1 
	_tvar1 = n + _tvar1
	n = _tvar1 
_L1:
	_tvar0 = 10 
	if ( n <= _tvar0 ) goto _L0
	goto _L2
_L2:
	_tvar1 = 1 
	n = _tvar1 
	Return 

	.data
	.text
main:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -28($sp) # Allocate stack frame for locals/tmps
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -16($fp) # Store to tmp variable _tvar0.
	lw $8, -16($fp) # Load tmp variable _tvar0.
	sw $8, -24($fp) # Store to local int n.
	j _L1
	.text
_L0:	lw $8, -24($fp) # Load local int n.
	li $9, 1 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -20($fp) # Store to tmp variable _tvar1.
	la $8, -12($fp) # Load address of local char array A.
	lw $9, -20($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -28($fp) # Store address to tmp address _taddr0.
	lw $8, -24($fp) # Load local int n.
	lw $9, -28($fp) # Load tmp address _taddr0.
	sb $8, ($9) # Store value pointed by _taddr0 to char array element.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -20($fp) # Store to tmp variable _tvar1.
	lw $8, -24($fp) # Load local int n.
	lw $9, -20($fp) # Load tmp variable _tvar1.
	add $10, $8, $9
	sw $10, -20($fp) # Store to tmp variable _tvar1.
	lw $8, -20($fp) # Load tmp variable _tvar1.
	sw $8, -24($fp) # Store to local int n.
	.text
_L1:	li $8, 10 # Load int constant shorter than 16-bits
	sw $8, -16($fp) # Store to tmp variable _tvar0.
	lw $8, -24($fp) # Load local int n.
	lw $9, -16($fp) # Load tmp variable _tvar0.
	ble $8, $9, _L0
	j _L2
	.text
_L2:	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -20($fp) # Store to tmp variable _tvar1.
	lw $8, -20($fp) # Load tmp variable _tvar1.
	sw $8, -24($fp) # Store to local int n.
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.
