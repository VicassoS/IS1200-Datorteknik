// snake.c - egenskriven kod 
#include "snake.h"

// funktion som initierar en snake i början av spelet 
void init_snake(snake* snake_ptr, uint8_t length, uint8_t dir, uint8_t controller){
    snake_ptr->length = length;         
    snake_ptr->controller = controller;
    snake_ptr->direction = dir;
    
    int i;
    if(dir == right){                               // beskriver var en orm med riktningen höger spawnar
        for(i = 0; i < length; i++){
            snake_ptr->nodes[i].x = length-i+1;   // börjar längst till vänster - dvs ormens ända är på kanten 
            snake_ptr->nodes[i].y = 7;            // börjar på y koordinaten 7 - dvs typ i mitten (7 av 16)
        }
    }
    
    else if(dir == left){                           // beskriver var en orm med riktningen vänster spawnar
        for(i = 0; i < length; i++){
            snake_ptr->nodes[length-1 - i].x = 63-i;  // börjar längst till höger - samma som ovan
            snake_ptr->nodes[length-1 - i].y = 7; // börjar på y koordinaten 7 - dvs typ i mitten (7 av 16)
        }
    }
}

/*
bit 0 - btn 1
bit 1 - btn 2
bit 2 - btn 3
bit 3 - btn 4
*/

// rotation kontroller för spelare 1 - använder btn 1 & 2
// Positiv riktning ==> medsols, negativ riktning ==> motsols

uint8_t player1_controller(uint8_t input, snake * snake_ptr){ 
    
    int dir = (input&1) - ((input & 0b10) >> 1);    // knapp 1 nedtryck - knapp 2 nedtryckt (shiftad åt höger)
    
    // Öka riktningen på ormen med dir. &0b11 för att hålla sig i spannet [0, 3]
    // ex. om ormens riktning är höger (0) och knapp 2 är nedtryck --> dir = -1 --> -1 = 0b11 --> 3 (up)                                 
    input = (snake_ptr->direction + dir) & 0b11; 
    return input;
}

// rotation kontroller för spelare 2 - använder btn 3 & 4
// Positiv riktning ==> medsols, negativ riktning ==> motsols

uint8_t player2_controller(uint8_t input, snake * snake_ptr){
    input = input >> 2;                             // Shitfta för att använda rätt knappar
    int dir = (input&1) - ((input & 0b10) >> 1);    // knapp 3 nedtryck - knapp 4 nedtryckt (shiftad åt höger)                              
    
    // Öka riktningen på ormen med dir. &0b11 för att hålla sig i spannet [0, 3]
    input = (snake_ptr->direction + dir) & 0b11;    
    return input;
}

