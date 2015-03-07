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
	la $sp, -76($sp) # Allocate stack frame for locals/tmps
	li $8, 123 # Load int constant shorter than 16-bits
	sw $8, -48($fp) # Store to local int x.
	li $8, 3 # Load int constant shorter than 16-bits
	sw $8, -12($fp) # Store to tmp variable _tvar2.
	lw $8, -12($fp) # Load tmp variable _tvar2.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar2.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -8($fp) # Store returned value to tmp variable _tvar1.
	lw $8, -8($fp) # Load tmp variable _tvar1.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar1.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -4($fp) # Store returned value to tmp variable _tvar0.
	li $8, 4 # Load int constant shorter than 16-bits
	sw $8, -28($fp) # Store to tmp variable _tvar6.
	lw $8, -28($fp) # Load tmp variable _tvar6.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar6.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -24($fp) # Store returned value to tmp variable _tvar5.
	lw $8, -24($fp) # Load tmp variable _tvar5.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar5.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -20($fp) # Store returned value to tmp variable _tvar4.
	lw $8, -20($fp) # Load tmp variable _tvar4.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar4.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -16($fp) # Store returned value to tmp variable _tvar3.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lw $9, -16($fp) # Load tmp variable _tvar3.
	ble $8, $9, _L1
	.text
_L0:	li $8, 321 # Load int constant shorter than 16-bits
	sw $8, -48($fp) # Store to local int x.
	.text
_L1:	li $8, 12 # Load int constant shorter than 16-bits
	sw $8, -44($fp) # Store to local int i.
	j _L3
	.text
_L2:	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -56($fp) # Store to tmp variable _tvar11.
	lw $8, -48($fp) # Load local int x.
	lw $9, -56($fp) # Load tmp variable _tvar11.
	sub $10, $8, $9
	sw $10, -56($fp) # Store to tmp variable _tvar11.
	lw $8, -56($fp) # Load tmp variable _tvar11.
	sw $8, -48($fp) # Store to local int x.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -56($fp) # Store to tmp variable _tvar11.
	lw $8, -44($fp) # Load local int i.
	lw $9, -56($fp) # Load tmp variable _tvar11.
	sub $10, $8, $9
	sw $10, -56($fp) # Store to tmp variable _tvar11.
	lw $8, -56($fp) # Load tmp variable _tvar11.
	sw $8, -44($fp) # Store to local int i.
	.text
_L3:	lw $8, -44($fp) # Load local int i.
	la $sp, -4($sp) # Allocate stack space for parameter i.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -40($fp) # Store returned value to tmp variable _tvar9.
	lw $8, -40($fp) # Load tmp variable _tvar9.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar9.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -36($fp) # Store returned value to tmp variable _tvar8.
	lw $8, -36($fp) # Load tmp variable _tvar8.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar8.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -32($fp) # Store returned value to tmp variable _tvar7.
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -52($fp) # Store to tmp variable _tvar10.
	lw $8, -32($fp) # Load tmp variable _tvar7.
	lw $9, -52($fp) # Load tmp variable _tvar10.
	bgt $8, $9, _L2
	j _L4
	.text
_L4:	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -60($fp) # Store to tmp variable _tvar12.
	lw $8, -60($fp) # Load tmp variable _tvar12.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar12.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -56($fp) # Store returned value to tmp variable _tvar11.
	lw $8, -56($fp) # Load tmp variable _tvar11.
	sw $8, -44($fp) # Store to local int i.
	j _L6
	.text
_L5:	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -72($fp) # Store to tmp variable _tvar15.
	lw $8, -48($fp) # Load local int x.
	lw $9, -72($fp) # Load tmp variable _tvar15.
	add $10, $8, $9
	sw $10, -72($fp) # Store to tmp variable _tvar15.
	lw $8, -72($fp) # Load tmp variable _tvar15.
	sw $8, -48($fp) # Store to local int x.
	lw $8, -44($fp) # Load local int i.
	la $sp, -4($sp) # Allocate stack space for parameter i.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -72($fp) # Store returned value to tmp variable _tvar15.
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -76($fp) # Store to tmp variable _tvar16.
	lw $8, -72($fp) # Load tmp variable _tvar15.
	lw $9, -76($fp) # Load tmp variable _tvar16.
	add $10, $8, $9
	sw $10, -72($fp) # Store to tmp variable _tvar15.
	lw $8, -72($fp) # Load tmp variable _tvar15.
	sw $8, -44($fp) # Store to local int i.
	.text
_L6:	lw $8, -44($fp) # Load local int i.
	la $sp, -4($sp) # Allocate stack space for parameter i.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -64($fp) # Store returned value to tmp variable _tvar13.
	lw $8, -64($fp) # Load tmp variable _tvar13.
	la $sp, -4($sp) # Allocate stack space for parameter _tvar13.
	sw $8, 0($sp) # Push the parameter value.
	jal _id
	la $sp, 4($sp) # Pop parameters off the stack.
	sw $2, -60($fp) # Store returned value to tmp variable _tvar12.
	li $8, 6 # Load int constant shorter than 16-bits
	sw $8, -68($fp) # Store to tmp variable _tvar14.
	lw $8, -60($fp) # Load tmp variable _tvar12.
	lw $9, -68($fp) # Load tmp variable _tvar14.
	blt $8, $9, _L5
	j _L7
	.text
_L7:	lw $8, -48($fp) # Load local int x.
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

