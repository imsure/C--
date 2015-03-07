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
	Enter main  64 
	_tvar0 = 7 
	_tvar0 = _tvar0 * 4 
	_taddr0 = y + _tvar0
	_tvar0 = 1234 
	*_taddr0(int) = _tvar0 
	_tvar0 = 0 
	_tvar0 = _tvar0 * 4 
	_taddr2 = x + _tvar0
	_tvar0 = 7 
	_tvar0 = _tvar0 * 4 
	_taddr1 = y + _tvar0
	*_taddr2(int) = *_taddr1(int) 
	_tvar0 = 0 
	_tvar0 = _tvar0 * 4 
	_taddr3 = x + _tvar0
	u = *_taddr3(int) 
	Param u 
	Call print_int  1 
	_tstr0 = "\n"
	Param _tstr0 
	Call print_string  1 
	Return 

	.data
__tstr0:	.asciiz "\n"
	.align 2
_y:	.space 40
	.text
main:	la $sp, -8($sp) # Allocate space for old $fp and $ra
	sw $fp, 4($sp) # Save old $fp on stack
	sw $ra, 0($sp) # Save old $ra on stack
	la $fp, 0($sp) # Set up frame pointer
	la $sp, -64($sp) # Allocate stack frame for locals/tmps
	li $8, 7 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, _y # Load address of global int array y.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -52($fp) # Store address to tmp address _taddr0.
	li $8, 1234 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	lw $9, -52($fp) # Load tmp address _taddr0.
	sw $8, ($9) # Store value pointed by _taddr0 to int array element.
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, -48($fp) # Load address of local int array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -60($fp) # Store address to tmp address _taddr2.
	li $8, 7 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, _y # Load address of global int array y.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -56($fp) # Store address to tmp address _taddr1.
	lw $9, -56($fp) # Load tmp address _taddr1.
	lw $8, ($9) # Load value of the int array element pointed by _taddr1.
	lw $9, -60($fp) # Load tmp address _taddr2.
	sw $8, ($9) # Store value pointed by _taddr2 to int array element.
	li $8, 0 # Load int constant shorter than 16-bits
	sw $8, -4($fp) # Store to tmp variable _tvar0.
	lw $8, -4($fp) # Load tmp variable _tvar0.
	li $9, 4 # Load size of array element for calculating its offset.
	mul $10, $8, $9
	sw $10, -4($fp) # Store to tmp variable _tvar0.
	la $8, -48($fp) # Load address of local int array x.
	lw $9, -4($fp) # Load tmp variable _tvar0.
	add $10, $8, $9
	sw $10, -64($fp) # Store address to tmp address _taddr3.
	lw $9, -64($fp) # Load tmp address _taddr3.
	lw $8, ($9) # Load value of the int array element pointed by _taddr3.
	sw $8, -8($fp) # Store to local int u.
	lw $8, -8($fp) # Load local int u.
	la $sp, -4($sp) # Allocate stack space for parameter u.
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
