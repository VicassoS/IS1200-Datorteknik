  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.
  # changes made by Viggo Schütt for lab 1 

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957	
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,1000	# 1000 ms - om <= 0 ingen delay
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  # copy of the function hexasc from hexmain
  
hexasc:
	andi	$a0, $a0, 0xf  	# ingores all bits except the 4 LSB, 0 - 15 (0xf)
	addi 	$v0, $a0, 0x30  # adds the ASCII value (0 = 0x30)
	
	ble 	$a0, 9, hexasc2 # jumps to new branch when value is less than 9 	
	nop
	
	addi 	$v0, $v0, 7	# adds 7 to ASCII code to achive 10-15 display A-F
  
  # taken branch for when a0 is between 0-9  
  
hexasc2: 
	jr 	$ra		# return
	nop

  # simple delay function 
delay: 
				
	while:
		# antalet ms finns i det givna $a0
		ble	$a0, $0, stop	# If a0 <= 0 stop program (ms > 0)
		nop
	
		addi	$a0, $a0, -1		# a0 - 1 : (ms - 1)
		addi	$t0, $0, 0		# (i = 0) "li also works" : -1
		addi 	$t1, $0, 10		# (t1 = 4771) for i < 4771  
	
	for:
		addi	$t0, $t0, 1	# (i + 1)   
		blt	$t0, $t1, for	# (i < 4771) --> if ble (i <= 4770) repeat loop 
		nop			# Same as i = 1 & i <= 4771 
	
		j	while
		nop
	 
stop:
	jr	$ra
	nop 
	
  # convert time-info into a string
  # 1. 1 Nibble motsvarar ett tal i a1 och skall omvandlas till ASCII kod
  # 1.a) andi med t3 för där t3 antar 4 sista LSB  
  # 2. ASCII kod skall sparas på den plats som a0 pekar på 
  # 3. a1 sll höger 4 steg för nästa nibble 
  
time2string:
	
	PUSH $ra		# saves value during branch - know where to return 
	PUSH $s0
	move 	$s0, $a0
	
	#andi	$t4, $a1, 0xff	# t4 får fyra sista värde
	#beq	$t4, $0, ding	# om 8 sista är 0 hoppa till Ding						
	#nop
																																					# endast LSB nibble sista används i hexasc   
	srl	$t1, $a1, 4	# nästa nibble för sekunder  	
	srl 	$t2, $a1, 8	# nästa nibble för minut - 1
	srl 	$t3, $a1, 12	# nästa nibble för minut - 2
	
	PUSH $a1
	PUSH $t1		# får inte anta att de ändras i hexasc
	PUSH $t2
				# minutvärdena fösrt
	move 	$a0, $t3	# överför för argurment till funktion
	jal 	hexasc 		# hoppar till ASCII kod som fås med 1 byte
	nop
	sb 	$v0, 0($s0) 	# retur värde sätts in på minnet
	
	POP $t2
	
	move 	$a0, $t2 	# överför till argument för funktion
	jal 	hexasc
	nop
	sb	$v0, 1($s0)
	
	li 	$t3, 0x3A	# ger värdet av kolon till t3
	sb	$t3, 2($s0)
	
	POP $t1
				# ger värde för sekuner - hanterar 5an i 16:53
	move 	$a0, $t1 	# överför till argument för funktion
	jal 	hexasc
	nop
	sb	$v0, 3($s0)
	
	POP $a1
	
	move 	$a0, $a1 	# överför till argument för funktion
	jal 	hexasc
	nop
	sb	$v0, 4($s0)
		
	sb 	$0, 5($s0)	# null byte 
	
	#j	ding_end
	#nop

	# suprise assignment
	
#ding:		
	#li	$t4, 0x474e4944 # ger värde för DING i motsatsrikning
	#sw	$t4, 0($s0)	# sparar "DING" 
	      
	#sb 	$0, 4($s0)	# null byte - visa slut 
	

#ding_end: 			
	POP $s0
	POP $ra
	jr 	$ra 		# tillbaka till rätt funktion
	nop	
	
  	  
	
