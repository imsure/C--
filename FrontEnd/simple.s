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

	.text
main:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -44($sp) # Allocate stack frame for locals/tmps
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -36($fp) # Store to local int i.
	li $8, 123 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to local int res.
	j _L1
	.text
_L0:	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -40($fp) # Store to local int j.
	j _L4
	.text
_L3:	lw $8, -36($fp) # Load local int i.
	lw $9, -40($fp) # Load local int j.
	add $10, $8, $9
	sw $10, -16($fp) # Store to tmp variable _tvar2.
	lw $8, -16($fp) # Load tmp variable _tvar2.
	li $9, 2 # Load int constant shorter than 16-bits
	div $10, $8, $9
	sw $10, -16($fp) # Store to tmp variable _tvar2.
	lw $8, -16($fp) # Load tmp variable _tvar2.
	sw $8, -44($fp) # Store to local int k.
	lw $8, -44($fp) # Load local int k.
	lw $9, -36($fp) # Load local int i.
	ble $8, $9, _L7
	.text
_L6:	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -28($fp) # Store to local int a.
	j _L9
	.text
_L8:	lw $8, -28($fp) # Load local int a.
	lw $9, -44($fp) # Load local int k.
	add $10, $8, $9
	sw $10, -20($fp) # Store to tmp variable _tvar3.
	lw $8, -20($fp) # Load tmp variable _tvar3.
	li $9, 2 # Load int constant shorter than 16-bits
	div $10, $8, $9
	sw $10, -20($fp) # Store to tmp variable _tvar3.
	lw $8, -20($fp) # Load tmp variable _tvar3.
	sw $8, -32($fp) # Store to local int b.
	lw $8, -32($fp) # Load local int b.
	lw $9, -40($fp) # Load local int j.
	ble $8, $9, _L12
	.text
_L11:	lw $8, -4($fp) # Load local int res.
	lw $9, -32($fp) # Load local int b.
	add $10, $8, $9
	sw $10, -20($fp) # Store to tmp variable _tvar3.
	lw $8, -20($fp) # Load tmp variable _tvar3.
	sw $8, -4($fp) # Store to local int res.
	j _L13
	.text
_L12:	lw $8, -4($fp) # Load local int res.
	lw $9, -44($fp) # Load local int k.
	add $10, $8, $9
	sw $10, -20($fp) # Store to tmp variable _tvar3.
	lw $8, -20($fp) # Load tmp variable _tvar3.
	sw $8, -4($fp) # Store to local int res.
	.text
_L13:	lw $8, -28($fp) # Load local int a.
	li $9, 1 # Load int constant shorter than 16-bits
	add $10, $8, $9
	sw $10, -20($fp) # Store to tmp variable _tvar3.
	lw $8, -20($fp) # Load tmp variable _tvar3.
	sw $8, -28($fp) # Store to local int a.
	.text
_L9:	lw $8, -28($fp) # Load local int a.
	li $9, 5 # Load int constant shorter than 16-bits
	blt $8, $9, _L8
	.text
_L7:	lw $8, -40($fp) # Load local int j.
	li $9, 1 # Load int constant shorter than 16-bits
	add $10, $8, $9
	sw $10, -20($fp) # Store to tmp variable _tvar3.
	lw $8, -20($fp) # Load tmp variable _tvar3.
	sw $8, -40($fp) # Store to local int j.
	.text
_L4:	lw $8, -40($fp) # Load local int j.
	li $9, 5 # Load int constant shorter than 16-bits
	blt $8, $9, _L3
	.text
_L5:	lw $8, -36($fp) # Load local int i.
	li $9, 1 # Load int constant shorter than 16-bits
	add $10, $8, $9
	sw $10, -20($fp) # Store to tmp variable _tvar3.
	lw $8, -20($fp) # Load tmp variable _tvar3.
	sw $8, -36($fp) # Store to local int i.
	.text
_L1:	lw $8, -36($fp) # Load local int i.
	li $9, 5 # Load int constant shorter than 16-bits
	blt $8, $9, _L0
	.text
_L2:	lw $8, -4($fp) # Load local int res.
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

