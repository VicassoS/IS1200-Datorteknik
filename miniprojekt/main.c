// main.c

#include <pic32mx.h>
#include <stdint.h>
#include "display.h"
#include "snake_game.h"
#include "interrupt.h"
#include "menu.h"


//Main funktionen har skrivits tillsammans eftersom den är grunden för hela programmet.
int main() {

	//initialisera displayen och knapparna
	init_display();
	init_btns();
	
	// initialiserar och startar spelet 
	uint8_t game_player_count = start_menu();	// får antalet spelare beroende på knapptryck
	init_game(game_player_count);
	init_time();

	// Meny loop - oändlig
	for(;;){
		poll_input();
		if(is_game_over()){

			// Stoppar timer interrupts för att sluta spelet
			stop_timer(); 
			game_over_screen();
			long long int ful_delay;
			for(ful_delay = 0; ful_delay < 10000000; ful_delay++){

			}
			
			game_player_count = start_menu();
			init_game(game_player_count);

			// Stätter på timer interrupts för att starta spelet
			init_time();  
		}
	}
	return 0;
}
