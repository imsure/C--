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
res:	.space 4
_tstr0:	.asciiz "\n"
	.align 2
a:	.space 4
_b:	.space 4
c:	.space 4
d:	.space 4
e:	.space 4
f:	.space 4
g:	.space 4
h:	.space 4
i:	.space 4
_j:	.space 4
	.text
main:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -4($sp) # Allocate stack frame for locals/tmps
	li $8, 1 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, a # Store to global int a.
	li $8, 2 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _b # Store to global int b.
	li $8, 3 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, c # Store to global int c.
	li $8, 4 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, d # Store to global int d.
	li $8, 5 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, e # Store to global int e.
	li $8, 6 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, f # Store to global int f.
	li $8, 7 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, g # Store to global int g.
	li $8, 8 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, h # Store to global int h.
	li $8, 9 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, i # Store to global int i.
	li $8, 10 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, _j # Store to global int j.
	lw $8, a # Load global int a.
	lw $9, _b # Load global int b.
	ble $8, $9, _L6
	j _L1
	.text
_L6:	lw $8, _b # Load global int b.
	lw $9, c # Load global int c.
	ble $8, $9, _L5
	j _L1
	.text
_L5:	lw $8, c # Load global int c.
	lw $9, d # Load global int d.
	ble $8, $9, _L4
	j _L1
	.text
_L4:	lw $8, d # Load global int d.
	lw $9, e # Load global int e.
	ble $8, $9, _L3
	j _L1
	.text
_L3:	lw $8, e # Load global int e.
	lw $9, f # Load global int f.
	bgt $8, $9, _L1
	j _L10
	.text
_L10:	lw $8, f # Load global int f.
	lw $9, g # Load global int g.
	bgt $8, $9, _L1
	j _L9
	.text
_L9:	lw $8, g # Load global int g.
	lw $9, h # Load global int h.
	bgt $8, $9, _L1
	j _L8
	.text
_L8:	lw $8, h # Load global int h.
	lw $9, i # Load global int i.
	bgt $8, $9, _L1
	j _L7
	.text
_L7:	lw $8, i # Load global int i.
	lw $9, _j # Load global int j.
	bgt $8, $9, _L1
	j _L0
	.text
_L0:	li $8, 1111 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, res # Store to global int res.
	j _L2
	.text
_L1:	li $8, 2222 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	sw $8, res # Store to global int res.
	.text
_L2:	lw $8, res # Load global int res.
	la $sp, -4($sp) # Allocate stack space for parameter res.
	sw $8, 0($sp) # Push the parameter value.
	jal print_int
	la $sp, 4($sp) # Pop parameters off the stack.
	la $8, _tstr0 # Load string const address _tstr0.
	la $sp, -4($sp) # Allocate stack space for parameter _tstr0.
	sw $8, 0($sp) # Push the parameter value.
	jal print_string
	la $sp, 4($sp) # Pop parameters off the stack.
	la $sp, 0($fp) # Move stack pointer back to $fp.
	lw $ra, 0($sp) # Restore return address.
	lw $fp, 4($sp) # Restore frame pointer.
	la $sp, 8($sp) # Restore stack pointer.
	jr $ra # jump back to the return address.