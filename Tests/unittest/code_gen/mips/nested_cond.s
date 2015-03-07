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
_res:	.space 4
__tstr0:	.asciiz "\n"
	.align 2
_a:	.space 4
_b:	.space 4
_c:	.space 4
_d:	.space 4
_e:	.space 4
_f:	.space 4
_g:	.space 4
	.text
main:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -4($sp) # Allocate stack frame for locals/tmps
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _a # Store to global int a.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _b # Store to global int b.
	li $8, 3 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _c # Store to global int c.
	li $8, 4 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _d # Store to global int d.
	li $8, 5 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _e # Store to global int e.
	li $8, 6 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _f # Store to global int f.
	lw $8, _a # Load global int a.
	lw $9, _b # Load global int b.
	blt $8, $9, _L0
	j _L1
	.text
_L0:	lw $8, _b # Load global int b.
	lw $9, _c # Load global int c.
	bge $8, $9, _L3
	j _L4
	.text
_L3:	lw $8, _c # Load global int c.
	lw $9, _d # Load global int d.
	blt $8, $9, _L6
	j _L7
	.text
_L6:	lw $8, _d # Load global int d.
	lw $9, _e # Load global int e.
	beq $8, $9, _L10
	j _L9
	.text
_L9:	lw $8, _e # Load global int e.
	lw $9, _f # Load global int f.
	blt $8, $9, _L12
	j _L13
	.text
_L12:	lw $8, _g # Load global int g.
	lw $9, _f # Load global int f.
	blt $8, $9, _L15
	j _L16
	.text
_L15:	lw $8, _g # Load global int g.
	lw $9, _a # Load global int a.
	blt $8, $9, _L18
	j _L19
	.text
_L18:	li $8, 1111 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _res # Store to global int res.
	j _L20
	.text
_L19:	li $8, 2222 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _res # Store to global int res.
	.text
_L20:	j _L17
	.text
_L16:	li $8, 3333 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _res # Store to global int res.
	.text
_L17:	j _L14
	.text
_L13:	li $8, 4444 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _res # Store to global int res.
	.text
_L14:	j _L11
	.text
_L10:	li $8, 5555 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _res # Store to global int res.
	.text
_L11:	j _L8
	.text
_L7:	li $8, 6666 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _res # Store to global int res.
	.text
_L8:	j _L5
	.text
_L4:	li $8, 7777 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _res # Store to global int res.
	.text
_L5:	j _L2
	.text
_L1:	li $8, 8888 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _res # Store to global int res.
	.text
_L2:	lw $8, _res # Load global int res.
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
