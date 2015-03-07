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

	.text
_sum:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -24($sp) # Allocate stack frame for locals/tmps
	lw $8, 8($fp) # Load int formal i.
	li $9, 1 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, 12($fp) # Load address of formal char array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -20($fp) # Store address to tmp address _taddr0.
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $9, -20($fp) # Load tmp address _taddr0.
	lb $8, ($9) # Load value of the char array element pointed by _taddr0.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	bne $8, $9, _L1
	.text
_L0:	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $2, -8($fp) # Load tmp variable _tvar1.
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.
	j _L2
	.text
_L1:	lw $8, 8($fp) # Load int formal i.
	li $9, 1 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -12($fp) # Store to tmp variable _tvar2.
	lw $8, 12($fp) # Load address of formal char array x.
	lw $9, -12($fp) # Load tmp variable _tvar2.
	add $10, $8, $9
	sw $10, -24($fp) # Store address to tmp address _taddr1.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -16($fp) # Store to tmp variable _tvar3.
	lw $8, 8($fp) # Load int formal i.
	lw $9, -16($fp) # Load tmp variable _tvar3.
	add $10, $8, $9
	sw $10, -16($fp) # Store to tmp variable _tvar3.
	lw $8, 12($fp) # Load address of formal char array x.
	la $sp, -4($sp) # Allocate stack space for parameter x.
	sw $8, 0($sp) # Push the parameter value.
	lw $8, -16($fp) # Load tmp variable _tvar3.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar3.
	sw $8, 0($sp) # Push the parameter value.
	jal _sum
	la $sp, 8($sp) # Pop parameters off the stack.
	sw $2, -12($fp) # Store returned value to tmp variable _tvar2.
	lw $9, -24($fp) # Load tmp address _taddr1.
	lb $8, ($9) # Load value of the char array element pointed by _taddr1.
	lw $9, -12($fp) # Load tmp variable _tvar2.
	add $10, $8, $9
	sw $10, -16($fp) # Store to tmp variable _tvar3.
	lw $2, -16($fp) # Load tmp variable _tvar3.
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.
	.text
_L2:	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.

	.data
__tstr0:	.asciiz "hello world"
	.align 2
__tstr1:	.asciiz "\n"
	.align 2

	.text
main:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -12($sp) # Allocate stack frame for locals/tmps
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar5.
	la $8, __tstr0 # Load string const address _tstr0.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr0.
	sw $8, 0($sp) # Push the parameter value.
	lw $8, -8($fp) # Load tmp variable _tvar5.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar5.
	sw $8, 0($sp) # Push the parameter value.
	jal _sum
	la $sp, 8($sp) # Pop parameters off the stack.
	sw $2, -4($fp) # Store returned value to tmp variable _tvar4.
	lw $8, -4($fp) # Load tmp variable _tvar4.
	sw $8, -12($fp) # Store to local int x.
	lw $8, -12($fp) # Load local int x.
	la $sp, -4($sp) # Allocate stack space for parameter x.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr1 # Load string const address _tstr1.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr1.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.

