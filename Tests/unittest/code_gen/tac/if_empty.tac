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
	Enter main  12 
	_tvar0 = 5 
	n = _tvar0 
	_tvar0 = 10 
	if ( n > _tvar0 ) goto _L1
	goto _L0
_L0:
	_tvar1 = 1 
	_tvar1 = _tvar1 + n
	n = _tvar1 
_L1:
	_tvar1 = n * n
	n = _tvar1 
	Return 

	.data
	.text
main:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -12($sp) # Allocate stack frame for locals/tmps
	li $8, 5 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, -12($fp) # Store to local int n.
	li $8, 10 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -12($fp) # Load local int n.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	bgt $8, $9, _L1
	j _L0
	.text
_L0:	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	lw $9, -12($fp) # Load local int n.
	add $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	sw $8, -12($fp) # Store to local int n.
	.text
_L1:	lw $8, -12($fp) # Load local int n.
	lw $9, -12($fp) # Load local int n.
	mul $10, $8, $9
	sw $10, -8($fp) # Store to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	sw $8, -12($fp) # Store to local int n.
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.
