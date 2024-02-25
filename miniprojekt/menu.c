// menu.c - egenskriven kod

#include "menu.h"


//Visa senaste spelets score på skärmen - kallas endast om winner_type är single_player
void view_score(uint32_t score){
	
    char score_string[] = "score = 00000000";
	char number[8];
	int_to_char(number, score);
	int i;
	for(i=8; i<16; i++){
		score_string[i] = number[i-8];	// ändrar värdet på scoren - dvs 0:orn (börjar på 8)
	}
	
	clear_screen();
	display_string(1, score_string);
	
	display_update();
    
}

//Visa lämplig spel-relaterad information efter att spelet är över.
void game_over_screen(){

	switch (game_winner)
	{
	case single_player:		
		view_score(score);
		break;
	case player1_win:
		clear_screen();
		display_string(1, "    WINNER");
		display_string(2, "   PLAYER 1");
		display_update();
		break;
	case player2_win:
		clear_screen();
		display_string(1, "    WINNER");
		display_string(2, "   PLAYER 2");
		display_update();
		break;
	case player_1_2_draw:
		clear_screen();
		display_string(1, "     DRAW");
		display_update();
		break;
	default:
		break;
	}
}

// Visa en start-meny på skärmen och vänta tills ett alternativ valts
uint8_t start_menu(){

	uint8_t player_amount = 1;
	clear_screen();
	display_string(0, "      SNEK");
	display_string(2, "	*BTN 4   *BTN 1");
	display_string(3, " Classic    1v1");
	display_update();
	uint8_t btns = 0;

	//Vänta tills en giltig knapp tryck ned: - dvs knapp 1 eller 4
	while(!(btns&1 | btns&0x8)){
		int i;
		for(i = 0; i < 100; i++)
			poll_input();
		btns = getbtns();
	}
	
	// för två spelare 
	if(btns & 0b0001) {			// btn 1 har tryckts
		player_amount = 2;
	}
		
	// en spelare
	else if(btns & 0b1000) {	// btn 4 har tryckts
		player_amount = 1; 
	}
	
	return player_amount;
}

//Konvertera en int till en 8 karaktärers repressentation av talet.
void int_to_char(char* int_string, uint32_t num){
	int i;
	int mul=1;
	char siffra = 0;
	for(i=0; i < 8; i++){
		//Få den decimala siffran på position i från vänster. (little-endian typ) 
		siffra = (num % (mul*10)) / mul;
		mul*=10;
		int_string[7-i] = '0' + siffra;
	}
	
	//Ta bort inledande nollor, förutom nollan längst till vänstar.
	i=0;
	while (i<7 && int_string[i]=='0')
	{
		int_string[i] = ' ';
		i++;
	}
	
}
