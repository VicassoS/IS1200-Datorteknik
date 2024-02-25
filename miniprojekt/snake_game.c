// snake_game.c - egenskriven kod

#include "snake_game.h"


void init_game(uint8_t snake_cnt){
	snake_count = snake_cnt;
	create_random_seed();
    
    // start positionen för äpplet (32, 7) - dvs mitten av spelfältet
    game_apple.x = 32;
    game_apple.y = 7;
    
	//Sätt andra variabler
    game_over = false;  
	score = 0;      
    create_grid();  

    // initialiserar ormarna på rätt position och spelare med längden 3:
	init_snake(&snakes[0], 3, right, player1);

    if (snake_cnt == 2){    
        init_snake(&snakes[1], 3, left, player2);
    }
	else{
		init_snake(&snakes[1], 0, left, player2);
	}
    
}

    // skapar ett spelgrid som är tomt (64 x 16 stor)

void create_grid(){
    int i;
    int size = sizeof(grid) / sizeof(grid[0]);
	
	//Initieras alla grid-block till 0
    for(i = 0; i < size; i++){
        int x = i % 64;     
        int y = i / 64;
        grid[i] = 0;	
    }
}

// uppdaterar ormens position 

uint8_t update_snake(snake* snake_ptr, uint8_t input){
    uint8_t direction = right;
    
    // switch case för spelarens orm 
    switch ((*snake_ptr).controller)
    {
    case player1:
        direction = player1_controller(input, snake_ptr);   // får dir om spelare är 1
        break;
    case player2:
        direction = player2_controller(input, snake_ptr);   // får dir om spelare är 2
        break;
    default:
        break;
    }
    (*snake_ptr).direction = direction;   // ändrar rikntingen på orm utefter spelare och knapp input              
    
    //Hitta nya huvudpositionen - upp till vänster är koordinaten (0, 0)
    snake_node new_head;
    switch (direction)
    {
    case up:;       // ändrar huvudets position att gå upp dvs minskar y koordinaten med 1
        new_head.x = snake_ptr->nodes[0].x;
        new_head.y = snake_ptr->nodes[0].y - 1;
        break;
        
    case right:;    // ändrar huvudets position att gå åt höger dvs ökar x koordinaten med 1    
        new_head.x = snake_ptr->nodes[0].x + 1;
        new_head.y = snake_ptr->nodes[0].y;
        break;

    case left:;     // ändrar huvudets position att gå åt vänster dvs minskar x koordinaten med 1
        new_head.x = snake_ptr->nodes[0].x - 1;
        new_head.y = snake_ptr->nodes[0].y;
        break;
    
    case down:;     // ändrar huvudets position att gå ned dvs ökar y koordinaten med 1
        new_head.x = snake_ptr->nodes[0].x;
        new_head.y = snake_ptr->nodes[0].y + 1;
        break;
    }
    
	// Spara sista nodens position (Där ett nytt block kan läggas till)
    snake_node new_body_cell_pos;
    new_body_cell_pos = snake_ptr->nodes[snake_ptr->length-1];

    // Uppdatera orm noderna (förutom huvudet) 
    int i;
    for(i=(*snake_ptr).length - 1; i > 0; i--){
        snake_ptr->nodes[i] = snake_ptr->nodes[i-1];
    }
    
    // Testa kollition med äpple - dvs om ormens x & y koordinat är samma som äpplets
    if(snake_ptr->nodes[0].x == game_apple.x && snake_ptr->nodes[0].y == game_apple.y){
        snake_ptr->length++;    
        snake_ptr->nodes[snake_ptr->length-1] = new_body_cell_pos;  
        score++;                
        update_apple_position();
    }
    
    // tillger orm huvudets nya position
    snake_ptr->nodes[0] = new_head;
}

//Rita ut spelplanen
void draw_snake_game(){
    int size = sizeof(grid) / sizeof(grid[0]);
    
	// Nolla hela gridet
    int i, j;
    for(i=0; i < size; i++){
        grid[i] = 0;
    }
    
    //Skriv ut ormarnas block i gridet
	for(j = 0; j < snake_count; j++){
    	for(i = 0; i < snakes[j].length; i++)
    	{
			// Få grid-positionen av blocket
    	    uint16_t pos = ((snakes[j].nodes[i].y)*64) + snakes[j].nodes[i].x; 
    	    grid[pos] = 0xFF;
    	}
	}
	
    //Skriv äpplet till griden
    uint16_t pos = (game_apple.y*64) + game_apple.x;
    grid[pos] = 0xFF;

	//Skriv ut gridet på skärmen
    draw_snake(grid);
}

// funktion som uppdaterar spelet 

void update_game(uint8_t input){

    // Uppdatera ormarna:
    int s;
	for(s=0;s<snake_count;s++){
		update_snake(&snakes[s], input);
	}

    // Testa kollitioner
    bool did_snake1_collide = has_snake_collided(&snakes[0]);
    bool did_snake2_collide = (snake_count>1) && has_snake_collided(&snakes[1]);
	
    // Oavgjort
    if(did_snake1_collide && did_snake2_collide){
		game_winner = player_1_2_draw;
		game_over = true;

	}

    //Snake 2 vann!
	else if(did_snake1_collide){
		game_winner = (snake_count>1) ? player2_win : single_player;
		game_over = true;
	}

    // Snake 1 vann!
	else if(did_snake2_collide){
		game_winner = player1_win;
		game_over = true;
	}
    
}

bool has_snake_collided(snake* snake_ptr){
    //Test collitions with walls
    bool did_collide = false;
	
    // Test x dir - om orm går utanför grid i x-koordinater
    if(snake_ptr->nodes[0].x < 0 || snake_ptr->nodes[0].x >= 64){
        did_collide = true;
    }
    
	// Test y dir - om orm går utangör grid i y-koordinater
	if(snake_ptr->nodes[0].y < 0 || snake_ptr->nodes[0].y >= 16){
        did_collide = true;
    }
    
	// Testar om orm kolliderar med sig själv
    int i, s;
	for(s=0;s<snake_count;s++){

        // om ormen kolliderar med sig själv skall dess huvud testas med annan orm nod - dvs i = 1
		bool is_me = (snake_ptr->controller == snakes[s].controller);
    	i = is_me ? 1:0;
		for(; i < snakes[s].length; i++){
    	    if(snake_ptr->nodes[0].x == snakes[s].nodes[i].x &&
    	        snake_ptr->nodes[0].y == snakes[s].nodes[i].y)
    	    { 
    	        did_collide = true;
    	        break;
    	    }
    	}
	}
    return did_collide;
}

void create_random_seed(){
	
	//Läs oinitzialiserat minne och använd xor:
	volatile uint32_t *seeder = (volatile uint32_t*) 0xA0004000;  
	uint32_t new_seed = 0xCCCCCCCC; // Hälften 1:or, hälften 0:or (101010......)
	int i;
	for(i = 0; i < 1024; i++){
		new_seed ^= *seeder;       // xor new_seed med seeder
		seeder++;
	}
	random_seed = (new_seed >>8) & 0xFF;

	//Modifiera med antalet knapp_polls som programmet gjort totalt för att få ett slumpat värde
	random_seed ^= poll_cnt;
	random_seed |= 1; // Ger bäst slump om seed:en är udda
	generator_a = 3;
	generator_c = 0;

	get_random_uint8();
}

uint8_t get_random_uint8(){
    // En implmentation av en "linear congruential generator"
    // Mer information finns på: https://en.wikipedia.org/wiki/Linear_congruential_generator
    uint8_t rand_value = 0;
    rand_value = (generator_a*random_seed+generator_c) & 0xFF; //Retunera minsta byten i rand_val   
    random_seed = rand_value;
    return rand_value;
}

void update_apple_position(){
    int i, s;
	
	// Hitta en slumpad position för äpplet 
    game_apple.x = get_random_uint8() & 0x3F; // Slumptal i intervallet [0, 63]
    game_apple.y = get_random_uint8() & 0xF;  // Slumptal i intervallet [0, 15]

    //Testa om platsen är ledig, om inte, försök med en ny position
    for(s=0;s<snake_count;s++){
		for(i=0; i < snakes[s].length; i++){
    	    if(snakes[s].nodes[i].x == game_apple.x && snakes[s].nodes[i].y == game_apple.y) {
    	        // Kalla funktionen rekursivt om platsen inte är ledig 
				update_apple_position();
    	    }
    	}
	}
}

bool is_game_over(){
    return game_over;
}

