// snake_game.h - egenskriven kod
// header fil / include guards - används på samma sätt som beksrivs i snake.h

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

// inkluderar alla header filer vars c fil behövs för att snake_game.c ska fungera 

#include <stdint.h>
#include "snake.h"
#include "display.h"
#include "interrupt.h"

//Definiera
#define bool uint8_t
#define true  1         // definierar true till 1 för tydlighet
#define false 0         // samma som ovan

// konstanter för vilken vinnartyp det är - används för game_over_screen  
enum winner_type {single_player, player1_win, player2_win, player_1_2_draw}; 

typedef struct apple{
    uint8_t x, y;       // beskriver äpplets x & y position --> apple = (x, y)
} apple;

// HUR POSITION I GRIDET FUNGERAR:
// Högst upp till vänster är (0, 0), sedan ökar den till höger rad för rad.
// Exempel:  
//  int pos = 155;
//  int grid_pos_x = 155 % 64;
//  int grid_pos_y = 155 / 64;

uint8_t grid[1024];      // 1024 - antaletet snake block som finns i spelet (64 * 16)

// Globala variabler
snake snakes[2];        // kan max vara 2 ormar (för 1v1)
apple game_apple;       
uint16_t score;
uint8_t snake_count, game_winner;
static bool game_over;

// variabler för rand funktionen
uint16_t random_seed, generator_a, generator_c, is_first_seed;

/***** Funtions *****/

// @Viggo Schütt
void init_game(uint8_t snake_cnt);

// @Viggo Shütt och Måns Abrahamsson
void update_game(uint8_t input);

// @Viggo Schütt
bool has_snake_collided(snake* snake_ptr);

// @Måns Abrahamsson
void draw_snake_game();

// @Måns Abrahamsson
void create_random_seed();

// @Måns Abrahamsson
uint8_t get_random_uint8();

// @ Viggo Schütt
void update_apple_position();

// @ Viggo Schütt
bool is_game_over();

// @Måns Abrahamsson & Viggo Schütt
uint8_t update_snake(snake* snake, uint8_t input);

// @Måns Abrahamsson
void create_grid();

#endif