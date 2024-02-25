// display.c - halvt egenskriven kod

#include "display.h"

//DEFINITIONS
#define SPI_MAIN_REGISTER   PORTF
#define RESET_PORT          PORTG
#define VDD_CTRL     (1<<6)
#define VBAT_CTRL    (1<<5)
#define DATA_COMMAND (1<<4)
#define OLED_RESET   (1<<9)


char textbuffer[4][16];

// textfont - inte egenskiven
static const uint8_t const font[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 94, 0, 0, 0, 0,
	0, 0, 4, 3, 4, 3, 0, 0,
	0, 36, 126, 36, 36, 126, 36, 0,
	0, 36, 74, 255, 82, 36, 0, 0,
	0, 70, 38, 16, 8, 100, 98, 0,
	0, 52, 74, 74, 52, 32, 80, 0,
	0, 0, 0, 4, 3, 0, 0, 0,
	0, 0, 0, 126, 129, 0, 0, 0,
	0, 0, 0, 129, 126, 0, 0, 0,
	0, 42, 28, 62, 28, 42, 0, 0,
	0, 8, 8, 62, 8, 8, 0, 0,
	0, 0, 0, 128, 96, 0, 0, 0,
	0, 8, 8, 8, 8, 8, 0, 0,
	0, 0, 0, 0, 96, 0, 0, 0,
	0, 64, 32, 16, 8, 4, 2, 0,
	0, 62, 65, 73, 65, 62, 0, 0,
	0, 0, 66, 127, 64, 0, 0, 0,
	0, 0, 98, 81, 73, 70, 0, 0,
	0, 0, 34, 73, 73, 54, 0, 0,
	0, 0, 14, 8, 127, 8, 0, 0,
	0, 0, 35, 69, 69, 57, 0, 0,
	0, 0, 62, 73, 73, 50, 0, 0,
	0, 0, 1, 97, 25, 7, 0, 0,
	0, 0, 54, 73, 73, 54, 0, 0,
	0, 0, 6, 9, 9, 126, 0, 0,
	0, 0, 0, 102, 0, 0, 0, 0,
	0, 0, 128, 102, 0, 0, 0, 0,
	0, 0, 8, 20, 34, 65, 0, 0,
	0, 0, 20, 20, 20, 20, 0, 0,
	0, 0, 65, 34, 20, 8, 0, 0,
	0, 2, 1, 81, 9, 6, 0, 0,
	0, 28, 34, 89, 89, 82, 12, 0,
	0, 0, 126, 9, 9, 126, 0, 0,
	0, 0, 127, 73, 73, 54, 0, 0,
	0, 0, 62, 65, 65, 34, 0, 0,
	0, 0, 127, 65, 65, 62, 0, 0,
	0, 0, 127, 73, 73, 65, 0, 0,
	0, 0, 127, 9, 9, 1, 0, 0,
	0, 0, 62, 65, 81, 50, 0, 0,
	0, 0, 127, 8, 8, 127, 0, 0,
	0, 0, 65, 127, 65, 0, 0, 0,
	0, 0, 32, 64, 64, 63, 0, 0,
	0, 0, 127, 8, 20, 99, 0, 0,
	0, 0, 127, 64, 64, 64, 0, 0,
	0, 127, 2, 4, 2, 127, 0, 0,
	0, 127, 6, 8, 48, 127, 0, 0,
	0, 0, 62, 65, 65, 62, 0, 0,
	0, 0, 127, 9, 9, 6, 0, 0,
	0, 0, 62, 65, 97, 126, 64, 0,
	0, 0, 127, 9, 9, 118, 0, 0,
	0, 0, 38, 73, 73, 50, 0, 0,
	0, 1, 1, 127, 1, 1, 0, 0,
	0, 0, 63, 64, 64, 63, 0, 0,
	0, 31, 32, 64, 32, 31, 0, 0,
	0, 63, 64, 48, 64, 63, 0, 0,
	0, 0, 119, 8, 8, 119, 0, 0,
	0, 3, 4, 120, 4, 3, 0, 0,
	0, 0, 113, 73, 73, 71, 0, 0,
	0, 0, 127, 65, 65, 0, 0, 0,
	0, 2, 4, 8, 16, 32, 64, 0,
	0, 0, 0, 65, 65, 127, 0, 0,
	0, 4, 2, 1, 2, 4, 0, 0,
	0, 64, 64, 64, 64, 64, 64, 0,
	0, 0, 1, 2, 4, 0, 0, 0,
	0, 0, 48, 72, 40, 120, 0, 0,
	0, 0, 127, 72, 72, 48, 0, 0,
	0, 0, 48, 72, 72, 0, 0, 0,
	0, 0, 48, 72, 72, 127, 0, 0,
	0, 0, 48, 88, 88, 16, 0, 0,
	0, 0, 126, 9, 1, 2, 0, 0,
	0, 0, 80, 152, 152, 112, 0, 0,
	0, 0, 127, 8, 8, 112, 0, 0,
	0, 0, 0, 122, 0, 0, 0, 0,
	0, 0, 64, 128, 128, 122, 0, 0,
	0, 0, 127, 16, 40, 72, 0, 0,
	0, 0, 0, 127, 0, 0, 0, 0,
	0, 120, 8, 16, 8, 112, 0, 0,
	0, 0, 120, 8, 8, 112, 0, 0,
	0, 0, 48, 72, 72, 48, 0, 0,
	0, 0, 248, 40, 40, 16, 0, 0,
	0, 0, 16, 40, 40, 248, 0, 0,
	0, 0, 112, 8, 8, 16, 0, 0,
	0, 0, 72, 84, 84, 36, 0, 0,
	0, 0, 8, 60, 72, 32, 0, 0,
	0, 0, 56, 64, 32, 120, 0, 0,
	0, 0, 56, 64, 56, 0, 0, 0,
	0, 56, 64, 32, 64, 56, 0, 0,
	0, 0, 72, 48, 48, 72, 0, 0,
	0, 0, 24, 160, 160, 120, 0, 0,
	0, 0, 100, 84, 84, 76, 0, 0,
	0, 0, 8, 28, 34, 65, 0, 0,
	0, 0, 0, 126, 0, 0, 0, 0,
	0, 0, 65, 34, 28, 8, 0, 0,
	0, 0, 4, 2, 4, 2, 0, 0,
	0, 120, 68, 66, 68, 120, 0, 0,
};

//Följande funktion har tagit från labbarna
void display_string(int line, char *s) {
	int i;
	if(line < 0 || line >= 4)
		return;
	if(!s)
		return;
	
	for(i = 0; i < 16; i++)
		if(*s) {
			textbuffer[line][i] = *s;
			s++;
		} else
			textbuffer[line][i] = ' ';
}

//Följande funktion har tagits från labbarna
void delay(int cyc) {
	int i;
	for(i = cyc; i > 0; i--){}
}

//Egenskriven funktion baserad på display update
void draw_snake(uint8_t* grid){
    int page, col, i;
	for(i = 0; i < 4; i++){
	    for(page = 0; page < 4; page++) {
			
			// Nolla DATA_COMMAND för att skicka kommandon till displayen.
	    	SPI_MAIN_REGISTER &= ~DATA_COMMAND; 

            // Sätt nuvarande page
	    	send_oled_data(0x22);   // Sätter även page adress till page start adress 
	    	send_oled_data(page);   // Page start adress
	    	send_oled_data(7);		// Sätt till sista pagen

            // Set higher column page adress to 0.
			uint8_t col_offset = i*32;
            send_oled_data(0x10 | (col_offset>>4)); //32
            send_oled_data(0x00 | (col_offset&0xF));

			// Sätt DATA_COMMAND för att skicka skärmdata till displayen
	    	SPI_MAIN_REGISTER |= DATA_COMMAND;
			uint8_t snake_col=0, snake_row=0;
	    	for(col = 0; col < 32; col++){
				snake_col = ((col_offset + col)>>1); 
				snake_row = (page*4);
	    		uint8_t data;
				data = 0;
				uint8_t r;
				int pos;
				// Läs från rätt postitioner i grid och hitta
				for(r = 0; r<4; r++){
					pos = (r+snake_row)*64 + snake_col; 
					data |= (grid[pos] & 0b11)<<(r*2); 
				}
				send_oled_data(data); // Send display data
			}
	    }
    }
}

//Funktion för att cleara skärmen.
void clear_screen(){
	int col, i, page;
	
	for(page = 0; page < 4; page++) {
		
		//Cleara DATA_COMMAND för att skicka kommandon till skärmen
	    SPI_MAIN_REGISTER &= ~DATA_COMMAND; 
        
		//Set page start and end address (NOT PAGE MODE?)
	    send_oled_data(0x22);   // Sätter även page adress till page start adress 
	    send_oled_data(page);      // Page start adress
	    send_oled_data(7);      // Page end adress = 0==> gå aldrig tillbaks
        //Set higher column page adress to 0. Börjar ju skriva från kolumn noll.
		uint8_t col_offset = 0;
        send_oled_data(0x10 | (col_offset>>4)); //32
        send_oled_data(0x00 | (col_offset&0xF));
	    
		//Sätt DATA_COMMAND för att skicka skärm-data (pixlar) till skärmen
		SPI_MAIN_REGISTER |= DATA_COMMAND;
		delay(1000);
	    for(col = 0; col < 128; col++){
	    	send_oled_data(0);    // Skriv nollor till skärmen
		}
	    
    }
}


//Följande funktion är tagen från en av labbarna, men modifierats något
void display_update() {
	int i, j, k;
	int c;
	for(i = 0; i < 4; i++) {
		SPI_MAIN_REGISTER &= ~DATA_COMMAND;

        //Set page adress:
		send_oled_data(0x22); // Sätter även page adress till page start adress
		send_oled_data(i);
		send_oled_data(0x0);

        //Set higher column page adress to 0.
		send_oled_data(0x10);
		
		SPI_MAIN_REGISTER |= DATA_COMMAND;
		
		for(j = 0; j < 16; j++) {
			c = textbuffer[i][j];
			if(c & 0x80)
				continue;
			
			for(k = 0; k < 8; k++)
				send_oled_data(font[c*8 + k]);
		}
	}

	// egenskriven kod
	// rensar textbuffern
	for(i=0;i<4;i++)
		for(j=0;j<16;j++)
			textbuffer[i][j] = ' ';
}



/*
OLED regler från PDF:en
    Start oled:
        1. Apply power to vdd
        2. Send display off command
        3. Initialize display to operating mode
        4. Clear the screen
        5. Apply power to vbat
        6. Delay 100ms
        7. Send Display on command

    Power off (Används inte):
        1. Send Display off command.
        2. Power off VBAT
        3. Delay 100ms
        4. Power off VDD
*/

//Följande funktion har tagits från labbarna
uint8_t send_oled_data(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 0x01));
	return SPI2BUF;
}

//Följande funktion har tagits från labbrana
void init_display(){
    
    //Set pheriferal buss clock
    OSCCON &= ~0x180000;
	OSCCON |= 0x080000;

    //Init SPI for oled communication ( SPI2 )
    SPI2CON = 0;
    SPI2BRG = 15;
    
    //Make RF4, RF5, RF6 be outputs
    ODCF = 0x0; // Open drain configuration
	ODCG = 0x0; // Open drain configuration
    PORTF = 0xFFFF;
	PORTG = (1 << 9);
    TRISFCLR = (0x111 << 4); // Sets RF4, RF5, RF6 to be outputs
    TRISGCLR = (0x1   << 9); // Sets RG9 to output (RESET SIGNAL)

	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
	
	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	
	/* Clear SPIROV */
	SPI2STATCLR = (1<<6);   // SPIROV = 0
    SPI2CONSET = (0b11<<5); // CKP = 1, MSTEN = 1
    
	/* Turn on SPI */
	SPI2CONSET = (1<<15);   // ON = 1

    /*** Start oled  ***/
    SPI_MAIN_REGISTER &= ~DATA_COMMAND; // Turns off data command bit
    delay(10); // Small delay
    SPI_MAIN_REGISTER &= ~VDD_CTRL;     // Turn on VDD (STEP 1)
    delay(1000000);          // Wait for it to turn on?
    
    // DISPLAY OFF COMMAND (STEP 2)
    send_oled_data(0xAE);    
    RESET_PORT &= ~OLED_RESET;  // TURN OFF RESET BIT
    delay(10);
    RESET_PORT |= OLED_RESET;   // TURN ON  RESET BIT
    delay(10);

    //(STEP 3)
    //Enable charge pump
    send_oled_data(0x8D);
	send_oled_data(0x14);
	
    //Set pre-charge period (STEP 4)
    //phase 1 is 1 cycle, phase 2 is 15 cycles
	send_oled_data(0xD9);
	send_oled_data(0xF1);

    SPI_MAIN_REGISTER &= ~VBAT_CTRL; // TURN OFF VBAT CONTROLL BIT ==> vbat turns on (STEP 5)
	delay(10000000);
	
    //Set Segment Re-map
    //A1 ==> column address 127 is mapped to SEG0
	send_oled_data(0xA1);

    //Set COM Output Scan Direction scan HIGH to LOW.
	send_oled_data(0xC8);
	

    //Com config: sequential + endable left right remap.
	send_oled_data(0xDA);
	send_oled_data(0x20);
	
    //Turn on display (STEP 7)
	send_oled_data(0xAF); 

    //Set screen contrast ration 127/255
    send_oled_data(0x81);
    send_oled_data(0x7F);

    //Set page mode:
    send_oled_data(0x20);
    send_oled_data(0b10);


}
