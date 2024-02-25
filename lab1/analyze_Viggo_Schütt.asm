  # analyze.asm
  # This file written 2015 by F Lundevall
  # Copyright abandoned - this file is in the public domain.
  # Changes made for lab assignment 1 by V Schütt

	.text
main:
	li	$s0,0x30
loop:
	move	$a0,$s0		# copy from s0 to a0
	
	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window

	addi	$s0,$s0,3	# what happens if the constant is changed?
				# 1 --> 3 changes amount of jumps in characters to 3 
	
	li	$t0,0x5d	# Z have ASCII value 0x5a 
				# Changed b --> d for account for the 3 jumps in character
	bne	$s0,$t0,loop	# test if s0 and t0 are equal - branches if not equal 
	nop			# delay slot filler (just in case)

stop:	j	stop		# loop forever here
	nop			# delay slot filler (just in case)

