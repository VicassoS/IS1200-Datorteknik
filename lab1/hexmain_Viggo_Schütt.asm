  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.
  # Changed for lab 1 assignment 2 by Viggo Schütt

	.text
main:
	li	$a0,0
	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
  # All numbers from 0-9 will be printed and 10-15 will print A-F
  
hexasc:
	andi	$a0, $a0, 0xf  	# ingores all bits except the 4 LSB, 0 - 15 (0xf) 
				# resets after 15 - e.g 16 --> 0, 17 --> 1 etc 
	addi 	$v0, $a0, 0x30  # adds the ASCII value (0 = 0x30)
	
				# can also give $t0 the value 9
	ble 	$a0, 9, hexasc2 # jumps to new branch when value is less than 9 	
	nop
	addi 	$v0, $v0, 7	# adds 7 to ASCII code to achive 10-15 display A-F
	  
  # taken branch for when a0 is between 0-9  
  
hexasc2: 
	jr 	$ra		# return 
	nop
