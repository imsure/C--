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
_f:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -24($sp) # Allocate stack frame for locals/tmps
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, 8($fp) # Load int formal n.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	bgt $8, $9, _L1
	.text
_L0:	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar1.
	lw $2, -8($fp) # Load tmp variable _tvar1.
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.
	j _L2
	.text
_L1:	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -16($fp) # Store to tmp variable _tvar3.
	lw $8, 8($fp) # Load int formal n.
	lw $9, -16($fp) # Load tmp variable _tvar3.
	sub $10, $8, $9
	sw $10, -16($fp) # Store to tmp variable _tvar3.
	lw $8, -16($fp) # Load tmp variable _tvar3.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar3.
	sw $8, 0($sp) # Push the parameter value.
	jal _g
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -12($fp) # Store returned value to tmp variable _tvar2.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -24($fp) # Store to tmp variable _tvar5.
	lw $8, 8($fp) # Load int formal n.
	lw $9, -24($fp) # Load tmp variable _tvar5.
	sub $10, $8, $9
	sw $10, -24($fp) # Store to tmp variable _tvar5.
	lw $8, -24($fp) # Load tmp variable _tvar5.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar5.
	sw $8, 0($sp) # Push the parameter value.
	jal _f
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -20($fp) # Store returned value to tmp variable _tvar4.
	lw $8, -12($fp) # Load tmp variable _tvar2.
	lw $9, -20($fp) # Load tmp variable _tvar4.
	add $10, $8, $9
	sw $10, -20($fp) # Store to tmp variable _tvar4.
	lw $2, -20($fp) # Load tmp variable _tvar4.
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

	.text
_g:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -24($sp) # Allocate stack frame for locals/tmps
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar5.
	lw $8, 8($fp) # Load int formal n.
	lw $9, -4($fp) # Load tmp variable _tvar5.
	bgt $8, $9, _L4
	.text
_L3:	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -8($fp) # Store to tmp variable _tvar6.
	lw $2, -8($fp) # Load tmp variable _tvar6.
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.
	j _L5
	.text
_L4:	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -16($fp) # Store to tmp variable _tvar8.
	lw $8, 8($fp) # Load int formal n.
	lw $9, -16($fp) # Load tmp variable _tvar8.
	sub $10, $8, $9
	sw $10, -16($fp) # Store to tmp variable _tvar8.
	lw $8, -16($fp) # Load tmp variable _tvar8.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar8.
	sw $8, 0($sp) # Push the parameter value.
	jal _f
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -12($fp) # Store returned value to tmp variable _tvar7.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -24($fp) # Store to tmp variable _tvar10.
	lw $8, 8($fp) # Load int formal n.
	lw $9, -24($fp) # Load tmp variable _tvar10.
	sub $10, $8, $9
	sw $10, -24($fp) # Store to tmp variable _tvar10.
	lw $8, -24($fp) # Load tmp variable _tvar10.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar10.
	sw $8, 0($sp) # Push the parameter value.
	jal _g
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -20($fp) # Store returned value to tmp variable _tvar9.
	lw $8, -12($fp) # Load tmp variable _tvar7.
	lw $9, -20($fp) # Load tmp variable _tvar9.
	add $10, $8, $9
	sw $10, -20($fp) # Store to tmp variable _tvar9.
	lw $2, -20($fp) # Load tmp variable _tvar9.
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.
	.text
_L5:	la $sp, 0($fp) # Move stack pointer back to $fp.
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
	la $sp, -12($sp) # Allocate stack frame for locals/tmps
	li $8, 5 # Load int constant shorter than 16-bits
	sw $8, -12($fp) # Store to tmp variable _tvar11.
	lw $8, -12($fp) # Load tmp variable _tvar11.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar11.
	sw $8, 0($sp) # Push the parameter value.
	jal _f
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -8($fp) # Store returned value to tmp variable _tvar10.
	lw $8, -8($fp) # Load tmp variable _tvar10.
	sw $8, -4($fp) # Store to local int x.
	lw $8, -4($fp) # Load local int x.
	la $sp, -4($sp) # Allocate stack space for parameter x.
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

