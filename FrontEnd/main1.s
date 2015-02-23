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
	la $sp, -16($sp)

	li $8, 10
	sw $8, -12($fp)

	lw $8, -12($fp)
	sw $8, -4($fp)

	lw $8, -4($fp)
	la $sp, -4($sp)
	sw $8, 0($sp)

	jal print_int
	la $sp, 4($sp)

	li $8, 50
	sw $8, -16($fp)

	lw $8, -16($fp)
	sw $8, -8($fp)

	lw $8, -8($fp)
	la $sp, -4($sp)
	sw $8, 0($sp)

	jal print_int
	la $sp, 4($sp)

	la $sp, 0($fp)
	lw $ra, 0($sp)
	lw $fp, 4($sp)
	la $sp, 8($sp)
	jr $ra

