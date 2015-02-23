	.text
print_int:
	li $v0, 1
	lw $a0, 0($sp)
	syscall
	jr $ra

	.text
main:
	la $sp, -8($sp)
	sw $fp, 4($sp)
	sw $ra, 0($sp)
	la $fp, 0($sp)
	la $sp, -40($sp)

	li $8, 0
	sw $8, -16($fp)

	lw $8, -16($fp)
	li $9, 4
	mul $10, $8, $9
	sw $10, -24($fp)

	la $8, -8($fp)
	lw $9, -24($fp)
	add $10, $8, $9
	sw $10, -20($fp)

	li $8, 8
	sw $8, -28($fp)

	lw $8, -28($fp)
	lw $9, -20($fp)
	sw $8, ($9)

	li $8, 0
	sw $8, -32($fp)

	lw $8, -32($fp)
	li $9, 4
	mul $10, $8, $9
	sw $10, -40($fp)

	la $8, -8($fp)
	lw $9, -40($fp)
	add $10, $8, $9
	sw $10, -36($fp)

	lw $8, -36($fp)
	lw $9, ($8)
	sw $9, -12($fp)

	lw $8, -12($fp)
	la $sp, -4($sp)
	sw $8, 0($sp)

	jal print_int
	la $sp, 4($sp)

	la $sp, 0($fp)
	lw $ra, 0($sp)
	lw $fp, 4($sp)
	la $sp, 8($sp)
	jr $ra

