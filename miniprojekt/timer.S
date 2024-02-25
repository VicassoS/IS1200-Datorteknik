# timer.S -

# egen skriven kod kombinerat - grund från lab 3 time4int @Viggo Schütt

.data
.global enable_interrupt    // andra funktioner ska få tillgång till funktionen
.global disable_interrupt   // andra funktioner ska få tillgång till funktionen
.text

// sätter på interuppt bit vilket aktiverar interrupts 

enable_interrupt:
    ei              // sätter på interrupts
    jr $ra         
    nop

// stänger av interrupt bit vilket inaktiverar interrupts

disable_interrupt:
    di              // stänger av interuppts
    jr $ra
    nop
