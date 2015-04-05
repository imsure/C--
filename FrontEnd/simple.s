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
__tstr1:	.asciiz "\n"
	.align 2
__tstr2:	.asciiz "\n"
	.align 2
__tstr3:	.asciiz "\n"
	.align 2
__tstr4:	.asciiz "\n"
	.align 2
__tstr5:	.asciiz "\n"
	.align 2
__tstr6:	.asciiz "\n"
	.align 2
__tstr7:	.asciiz "\n"
	.align 2
__tstr8:	.asciiz "\n"
	.align 2
__tstr9:	.asciiz "\n"
	.align 2
__tstr10:	.asciiz "\n"
	.align 2
__tstr11:	.asciiz "\n"
	.align 2
__tstr12:	.asciiz "\n"
	.align 2
__tstr13:	.asciiz "\n"
	.align 2
__tstr14:	.asciiz "\n"
	.align 2
__tstr15:	.asciiz "\n"
	.align 2
__tstr16:	.asciiz "\n"
	.align 2
__tstr17:	.asciiz "\n"
	.align 2
__tstr18:	.asciiz "\n"
	.align 2
__tstr19:	.asciiz "\n"
	.align 2

	.text
main:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -92($sp) # Allocate stack frame for locals/tmps
	li $8, 97 # Load char constant.
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, -8($fp) # Store to local int a.
	li $8, 98 # Load char constant.
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, -12($fp) # Store to local int b.
	lw $8, -8($fp) # Load local int a.
	sw $8, -16($fp) # Store to local int x1.
	lw $8, -8($fp) # Load local int a.
	sw $8, -24($fp) # Store to local int x2.
	lw $8, -8($fp) # Load local int a.
	sw $8, -32($fp) # Store to local int x3.
	lw $8, -8($fp) # Load local int a.
	sw $8, -40($fp) # Store to local int x4.
	lw $8, -8($fp) # Load local int a.
	sw $8, -48($fp) # Store to local int x5.
	lw $8, -8($fp) # Load local int a.
	sw $8, -56($fp) # Store to local int x6.
	lw $8, -8($fp) # Load local int a.
	sw $8, -64($fp) # Store to local int x7.
	lw $8, -8($fp) # Load local int a.
	sw $8, -72($fp) # Store to local int x8.
	lw $8, -8($fp) # Load local int a.
	sw $8, -80($fp) # Store to local int x9.
	lw $8, -8($fp) # Load local int a.
	sw $8, -88($fp) # Store to local int x10.
	lw $8, -12($fp) # Load local int b.
	sw $8, -20($fp) # Store to local int y1.
	lw $8, -12($fp) # Load local int b.
	sw $8, -28($fp) # Store to local int y2.
	lw $8, -12($fp) # Load local int b.
	sw $8, -36($fp) # Store to local int y3.
	lw $8, -12($fp) # Load local int b.
	sw $8, -44($fp) # Store to local int y4.
	lw $8, -12($fp) # Load local int b.
	sw $8, -52($fp) # Store to local int y5.
	lw $8, -12($fp) # Load local int b.
	sw $8, -60($fp) # Store to local int y6.
	lw $8, -12($fp) # Load local int b.
	sw $8, -68($fp) # Store to local int y7.
	lw $8, -12($fp) # Load local int b.
	sw $8, -76($fp) # Store to local int y8.
	lw $8, -12($fp) # Load local int b.
	sw $8, -84($fp) # Store to local int y9.
	lw $8, -12($fp) # Load local int b.
	sw $8, -92($fp) # Store to local int y10.
	lw $8, -16($fp) # Load local int x1.
	la $sp, -4($sp) # Allocate stack space for parameter x1.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr0 # Load string const address _tstr0.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr0.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -24($fp) # Load local int x2.
	la $sp, -4($sp) # Allocate stack space for parameter x2.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr1 # Load string const address _tstr1.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr1.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -32($fp) # Load local int x3.
	la $sp, -4($sp) # Allocate stack space for parameter x3.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr2 # Load string const address _tstr2.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr2.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -40($fp) # Load local int x4.
	la $sp, -4($sp) # Allocate stack space for parameter x4.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr3 # Load string const address _tstr3.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr3.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -48($fp) # Load local int x5.
	la $sp, -4($sp) # Allocate stack space for parameter x5.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr4 # Load string const address _tstr4.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr4.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -56($fp) # Load local int x6.
	la $sp, -4($sp) # Allocate stack space for parameter x6.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr5 # Load string const address _tstr5.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr5.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -64($fp) # Load local int x7.
	la $sp, -4($sp) # Allocate stack space for parameter x7.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr6 # Load string const address _tstr6.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr6.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -72($fp) # Load local int x8.
	la $sp, -4($sp) # Allocate stack space for parameter x8.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr7 # Load string const address _tstr7.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr7.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -80($fp) # Load local int x9.
	la $sp, -4($sp) # Allocate stack space for parameter x9.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr8 # Load string const address _tstr8.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr8.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -88($fp) # Load local int x10.
	la $sp, -4($sp) # Allocate stack space for parameter x10.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr9 # Load string const address _tstr9.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr9.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -20($fp) # Load local int y1.
	la $sp, -4($sp) # Allocate stack space for parameter y1.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr10 # Load string const address _tstr10.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr10.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -28($fp) # Load local int y2.
	la $sp, -4($sp) # Allocate stack space for parameter y2.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr11 # Load string const address _tstr11.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr11.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -36($fp) # Load local int y3.
	la $sp, -4($sp) # Allocate stack space for parameter y3.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr12 # Load string const address _tstr12.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr12.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -44($fp) # Load local int y4.
	la $sp, -4($sp) # Allocate stack space for parameter y4.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr13 # Load string const address _tstr13.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr13.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -52($fp) # Load local int y5.
	la $sp, -4($sp) # Allocate stack space for parameter y5.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr14 # Load string const address _tstr14.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr14.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -60($fp) # Load local int y6.
	la $sp, -4($sp) # Allocate stack space for parameter y6.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr15 # Load string const address _tstr15.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr15.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -68($fp) # Load local int y7.
	la $sp, -4($sp) # Allocate stack space for parameter y7.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr16 # Load string const address _tstr16.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr16.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -76($fp) # Load local int y8.
	la $sp, -4($sp) # Allocate stack space for parameter y8.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr17 # Load string const address _tstr17.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr17.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -84($fp) # Load local int y9.
	la $sp, -4($sp) # Allocate stack space for parameter y9.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr18 # Load string const address _tstr18.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr18.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -92($fp) # Load local int y10.
	la $sp, -4($sp) # Allocate stack space for parameter y10.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr19 # Load string const address _tstr19.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr19.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.

