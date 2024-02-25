
.text
	
	addi 	$a0, $0, 3	# värdet på n

main:
	beq	$a0, $0, zero	# kör fuktion zero om n = 0
	add	$v0, $0, $a0	# ger v0 värde för n
	addi	$a1, $a0, -1	# a1 = n - 1
	
fakultet:
	beq	$a1, $0, end	# slut på program, a1 = 0
	mul	$v0, $v0, $a1 	# n * (n - 1) "= X"
	addi 	$a1, $a1, -1	# a1-- (minskar) --> X * (n - 2) osv
	beq 	$0, $0, fakultet	# kör om program
	
zero:
	addi	$v0, $0, 1	# 0! = 1 
	beq	$0, $0, end	# hoppar till slut
	add	$0, $0, $0	# nop

end: 
	beq	$0, $0, end	# kör end oändligt många gånger
	add 	$0, $0, $0	# nop 