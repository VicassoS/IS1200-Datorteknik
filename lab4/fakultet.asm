
.text

	addi 	$a0, $0, 3	# talet för n! ; initialiserar n

main:
	beq	$a0, $0, zero	# om n = 0, 0! gå till funktion zero 
	add 	$0, $0, $0	# nop
	add	$v0, $a0, $0	# ger v0 värde för a0 ; initialiserar resultat = n
	addi	$a1, $a0, -1	# ger värde i = n - 1
	add	$a2, $0, $0	# ger start värde 0, ändras genom programmet - adderas till v0
	
	# loop för fakultet - 5! = 5 * 4 * 3  * 2 * 1	
	# --> (5+5+5+5) * 3 * 2 * 1 = (20 + 20 + 20) * 2 * 1 = 60 + 60 = 120
	
fakultet:			# for (i = n - 1; i > 0; i--) 
	beq	$0, $a1, end	# a1 = 0 --> beräkningen är klar	
	add	$0, $0, $0	# nop
	
	# additionsloop som motsvarar multiplikation
multi:				# for (a1 != 0; a1--)
	beq	$a1, $0, fakultet_end	# om a1 = 0 gå till fakultet end
	add	$0, $0, $0 		# nop	
	add 	$a2, $a2, $v0		# adderar a2 får värde av antalet additioner från v0
	addi	$a1, $a1, -1		# a1-- ändrar värde på a1 för fakultet vilket betyder att a1 måste får värde av a0
	beq	$0, $0, multi		# villkorlöst hopp
	add	$0, $0, $0		# nop 

fakultet_end:
	add	$v0, $a2, $0	# uppdaterar v0 värde 
	add	$a2, $0, $0	# nollställer a2 (adderar till v0) för att lägga till nytt v0 värde
	addi	$a0, $a0, -1	# minskar n med 1 (n - 1)
	addi	$a1, $a0, -1	# överskriver a1 med ny n - 1
	beq  	$0, $0, fakultet	# kör fakultet loop
	add	$0, $0, $0	# nop
	

	# fakultet 0
zero:
	addi	$v0, $0, 1	# 0! = 1 
	beq	$0, $0, end	# hoppar till slut
	add	$0, $0, $0	# samma som nop

	# slut av program
 end:
 	beq	$0, $0, end	# j end (sitter kvar på slut)
 	add 	$0, $0, $0	# nop 
