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
_x:	.space 4
_y:	.space 4
_z:	.space 4
	.text
main:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -16($sp) # Allocate stack frame for locals/tmps
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _x # Store to global int x.
	li $8, 3 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _y # Store to global int y.
	li $8, 4 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _z # Store to global int z.
	li $8, 97 # Load char constant.
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lw $9, _x # Load global int x.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sb $8, -8($fp) # Store to local char a.
	lw $8, _x # Load global int x.
	lw $9, _y # Load global int y.
	add $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lb $8, -8($fp) # Load local char a.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	div $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lw $9, _z # Load global int z.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sb $8, -12($fp) # Store to local char b.
	lw $8, _x # Load global int x.
	lw $9, _y # Load global int y.
	add $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lb $8, -8($fp) # Load local char a.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	div $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lw $9, _z # Load global int z.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lb $9, -8($fp) # Load local char a.
	sub $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lb $9, -12($fp) # Load local char b.
	add $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sb $8, -16($fp) # Store to local char c.
	lb $8, -16($fp) # Load local char c.
	la $sp, -4($sp) # Allocate stack space for parameter c.
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
