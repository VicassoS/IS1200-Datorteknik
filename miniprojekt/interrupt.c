// interrupt.c - egenskriven kod

#include "interrupt.h"
    
	
void init_time(){	
	// Buss hastigheten har frekvensen 40 Mhz (Sätts i display.h)
	
	// sätter på interrupt från timer2 - kod från lab 3 time4int
	
	T2CON = 0x0;	// slutar timer och rensar kontroll register - prescale sätts till 1:1, intern clock source
	TMR2 = 0x0; 	// rensar tids register

	PR2 = 31250; 	// sätter tids perioden till 31250 --> 31250 

	IPCSET(2) = 0xc;	// sätter prioritets nivå till 3
	IPCSET(2) = 0x1;	// sätter subprioritets nivå till 1

	IFSCLR(0) = 0x100; 	// rensar timer interupt flag status
	IECSET(0) = 0x100;	// sätter på timer interrupts
	enable_interrupt();	// sätter på interrupts globalt

	T2CONSET = 0x8070;	// startar timmer då bit 15 är 1, bitsen 6-4 är 111 --> prescale sätts till 1:256 --> N = 256
       				// PBCLK / N = 156250 --> perioden är 31250 --> 31250 / 156250 = 0.2 --> timeouts sker varje 200 ms --> 5 timeouts / s 
	
	// initaliserar 
	first_poll = true;
	interupted_btns = 0;
	
	//DEBUG med lysdioderna
	interrupt_count = 0;
	TRISECLR = 0xFF;
}

void user_isr(){
	
	//Hantera interrupts från timer2
	int time = IFS(0) & 0x100;	// får värde om det skett en interrupt av timer2 
	if (time != 0){				// testar om interrupt skett 
		
		//Kalla spel funktionerna
		update_game(getbtns());
		draw_snake_game();
			
		IFSCLR(0) = 0x100;		// rensar timeout flag status
	}
	
	// för cherry switcher (externa knappar)
	// Knapp 1 interrups
	if(IFS(0) & (1<<7)){
		interupted_btns |= 0b0001;
		interrupt_count++;
		IFSCLR(0) = (1<<7);
	}

	// Knapp 2 interrups
	if(IFS(0) & (1<<11)){
		interupted_btns |= 0b0010;
		interrupt_count++;
		IFSCLR(0) = (1<<11);
	}

	// Knapp 3 interrups
	if(IFS(0) & (1<<15)){
		interupted_btns |= 0b0100;
		interrupt_count++;
		IFSCLR(0) = (1<<15);
	}

	// Knapp 4 interrups
	if(IFS(0) & (1<<19)){
		interupted_btns |= 0b1000;
		interrupt_count++;
		IFSCLR(0) = (1<<19);
	}
	PORTECLR = 0xFF;
	PORTESET = interrupt_count & 0xFF;
}

// sätter alla btns till inputs 
void init_btns(){
    // Sätt interna knapparna till inputs
	TRISD |= 0xE0;  //eller 0b11100000 - sätter knapp 2-4 till inputs
    TRISF |= 0x1;   //eller 0b1 - sätter btn1 till att vara input

	// Sätt externa knapparna till inputs
	TRISDSET = 0xF00; // Sätt rd8-11 inputs INT1-INT4

	/*** Sätter på interrupts för externa knappar ***/

	// Disable INT1-INT4
	IECCLR(0) = 1 <<  7; //INT 1 	
	IECCLR(0) = 1 << 11; //INT 2	
	IECCLR(0) = 1 << 15; //INT 3	
	IECCLR(0) = 1 << 19; //INT 4
	
	INTCONCLR = 0xF << 1;   // Sätt INT1-INT4 att kallas på falling edge (Knapparna är pull-up)
	
	// cleara interrupt flag status
	IFSCLR(0) = 1 << 7;  //INT 1 	
	IFSCLR(0) = 1 << 11; //INT 2 	
	IFSCLR(0) = 1 << 15; //INT 3 	
	IFSCLR(0) = 1 << 19; //INT 4 	
	
	//Sätt prioritet (6, 3) - högre än timers prioritet, vill att knappen ska kännas av under uppdatering
	IPCSET(1) = 6 << 26;
	IPCSET(1) = 3 << 24;

	IPCSET(2) = 6 << 26;
	IPCSET(2) = 3 << 24;

	IPCSET(3) = 6 << 26;
	IPCSET(3) = 3 << 24;
	
	IPCSET(4) = 6 << 26;
	IPCSET(4) = 3 << 24;

	// enable interrupt INT1-INT4
	IECSET(0) = 1 <<  7; //INT 1 	
	IECSET(0) = 1 << 11; //INT 2	
	IECSET(0) = 1 << 15; //INT 3	
	IECSET(0) = 1 << 19; //INT 4	
}

// Får alla knappar som tryckts ned sedan förra gången funktionen kallades 
uint8_t getbtns (){
	uint8_t tmp = polled_buttons | interupted_btns; // Vi vill både använda pollade och interruptade knappar.
	polled_buttons = 0;
	unreleased_btns = 0;
	interupted_btns = 0;
	first_poll = true;
	return tmp;
}

// Polling för inbyggda knapparna
void poll_input(){
	poll_cnt++;
	uint8_t btns = 0;
	btns = (PORTD >> 5) & 0x7;				// tillger btns 2-4 från  bit 7 - 5 >> 5 --> (0b 0111) 
    btns = (btns << 1);                     // skapar en fri bit för btn 1 - varje bit representerar en btn

    btns = ((PORTF >> 1) & 0x1) | btns;     // lägger in värdet på btn 1 bit 1

	// Spara värdet på knapparna första gången den pollar
	if(first_poll){
		unreleased_btns = btns;
		first_poll = false;
	}

	// Unreleased_btns sparar vilka knappar som aldrig varit av.
	unreleased_btns &= btns;

	// Sätt en pollad knapp till på om den är på och tidigare har varit av. 
    polled_buttons |= (btns & ~(unreleased_btns)); // Sätt en knapp om den tidigare har varit av och nu är på
	
	int i;
	//Sakta ned polling hastigheten
	for(i = 0; i < 10000; i++) {}
}

// stänger av timer - används när snake har dött så att inte user_isr kallas på efter ett spel

void stop_timer(){
	IECCLR(0) = 0x100;		// sätter av timer interupts 
	disable_interrupt();	// stänger av interuppts globalt
	T2CON = 0x0;			// stoppar timer
	TMR2  = 0x0;			// rensar tids register 
	IFSCLR(0) = 0x100; 		// Rensa interrupt flag status
}