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
__tstr20:	.asciiz "\n"
	.align 2
__tstr11:	.asciiz "\n"
	.align 2
__tstr21:	.asciiz "\n"
	.align 2
__tstr12:	.asciiz "\n"
	.align 2
__tstr22:	.asciiz "\n"
	.align 2
__tstr13:	.asciiz "\n"
	.align 2
__tstr23:	.asciiz "\n"
	.align 2
__tstr14:	.asciiz "\n"
	.align 2
__tstr24:	.asciiz "\n"
	.align 2
__tstr15:	.asciiz "\n"
	.align 2
__tstr25:	.asciiz "\n"
	.align 2
__tstr16:	.asciiz "\n"
	.align 2
__tstr26:	.asciiz "\n"
	.align 2
__tstr17:	.asciiz "\n"
	.align 2
__tstr27:	.asciiz "\n"
	.align 2
__tstr18:	.asciiz "\n"
	.align 2
__tstr28:	.asciiz "\n"
	.align 2
__tstr19:	.asciiz "\n"
	.align 2
__tstr29:	.asciiz "\n"
	.align 2

	.text
main:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -84($sp) # Allocate stack frame for locals/tmps
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, -8($fp) # Store to local int x1.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lw $9, -8($fp) # Load local int x1.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, -16($fp) # Store to local int x2.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lw $9, -16($fp) # Load local int x2.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, -24($fp) # Store to local int x3.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lw $9, -24($fp) # Load local int x3.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, -32($fp) # Store to local int x4.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lw $9, -32($fp) # Load local int x4.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, -40($fp) # Store to local int x5.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lw $9, -40($fp) # Load local int x5.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	move $25, $8 # Store local int x6 to its pre-assigned register.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	mul $10, $8, $25
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	move $24, $8 # Store local int x7 to its pre-assigned register.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	mul $10, $8, $24
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	move $23, $8 # Store local int x8 to its pre-assigned register.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	mul $10, $8, $23
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	move $22, $8 # Store local int x9 to its pre-assigned register.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	mul $10, $8, $22
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	move $21, $8 # Store local int x10 to its pre-assigned register.
	lw $8, -8($fp) # Load local int x1.
	lw $9, -16($fp) # Load local int x2.
	add $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	move $20, $8 # Store local int y1 to its pre-assigned register.
	lw $8, -16($fp) # Load local int x2.
	lw $9, -24($fp) # Load local int x3.
	add $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	move $19, $8 # Store local int y2 to its pre-assigned register.
	lw $8, -24($fp) # Load local int x3.
	lw $9, -32($fp) # Load local int x4.
	add $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	move $18, $8 # Store local int y3 to its pre-assigned register.
	lw $8, -32($fp) # Load local int x4.
	lw $9, -40($fp) # Load local int x5.
	add $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	move $17, $8 # Store local int y4 to its pre-assigned register.
	lw $8, -40($fp) # Load local int x5.
	add $10, $8, $25
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	move $16, $8 # Store local int y5 to its pre-assigned register.
	add $10, $25, $24
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	move $15, $8 # Store local int y6 to its pre-assigned register.
	add $10, $24, $23
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	move $14, $8 # Store local int y7 to its pre-assigned register.
	add $10, $23, $22
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	move $13, $8 # Store local int y8 to its pre-assigned register.
	add $10, $22, $21
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	move $12, $8 # Store local int y9 to its pre-assigned register.
	add $10, $20, $19
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $18
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $17
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $16
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $15
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $14
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $13
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $12
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	move $11, $8 # Store local int y10 to its pre-assigned register.
	lw $8, -8($fp) # Load local int x1.
	la $sp, -4($sp) # Allocate stack space for parameter x1.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr0 # Load string const address _tstr0.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr0.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter y1.
	sw $20, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr1 # Load string const address _tstr1.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr1.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -16($fp) # Load local int x2.
	la $sp, -4($sp) # Allocate stack space for parameter x2.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr2 # Load string const address _tstr2.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr2.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter y2.
	sw $19, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr3 # Load string const address _tstr3.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr3.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -24($fp) # Load local int x3.
	la $sp, -4($sp) # Allocate stack space for parameter x3.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr4 # Load string const address _tstr4.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr4.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter y3.
	sw $18, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr5 # Load string const address _tstr5.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr5.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -32($fp) # Load local int x4.
	la $sp, -4($sp) # Allocate stack space for parameter x4.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr6 # Load string const address _tstr6.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr6.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter y4.
	sw $17, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr7 # Load string const address _tstr7.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr7.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	lw $8, -40($fp) # Load local int x5.
	la $sp, -4($sp) # Allocate stack space for parameter x5.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr8 # Load string const address _tstr8.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr8.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter y5.
	sw $16, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr9 # Load string const address _tstr9.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr9.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter x6.
	sw $25, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr10 # Load string const address _tstr10.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr10.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter y6.
	sw $15, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr11 # Load string const address _tstr11.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr11.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter x7.
	sw $24, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr12 # Load string const address _tstr12.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr12.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter y7.
	sw $14, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr13 # Load string const address _tstr13.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr13.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter x8.
	sw $23, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr14 # Load string const address _tstr14.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr14.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter y8.
	sw $13, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr15 # Load string const address _tstr15.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr15.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter x9.
	sw $22, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr16 # Load string const address _tstr16.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr16.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter y9.
	sw $12, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr17 # Load string const address _tstr17.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr17.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter x10.
	sw $21, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr18 # Load string const address _tstr18.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr18.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter y10.
	sw $11, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr19 # Load string const address _tstr19.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr19.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter y1.
	sw $20, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr20 # Load string const address _tstr20.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr20.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter y2.
	sw $19, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr21 # Load string const address _tstr21.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr21.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter y3.
	sw $18, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr22 # Load string const address _tstr22.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr22.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter y4.
	sw $17, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr23 # Load string const address _tstr23.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr23.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter y5.
	sw $16, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr24 # Load string const address _tstr24.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr24.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter y6.
	sw $15, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr25 # Load string const address _tstr25.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr25.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter y7.
	sw $14, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr26 # Load string const address _tstr26.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr26.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter y8.
	sw $13, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr27 # Load string const address _tstr27.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr27.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter y9.
	sw $12, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr28 # Load string const address _tstr28.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr28.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, -4($sp) # Allocate stack space for parameter y10.
	sw $11, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, __tstr29 # Load string const address _tstr29.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr29.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.

