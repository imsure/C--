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
	Enter main  8 
	_tvar0 = 5 
	n = _tvar0 
	_tvar0 = n * n
	n = _tvar0 
	Return 

