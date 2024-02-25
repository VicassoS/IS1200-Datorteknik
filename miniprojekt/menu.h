// menu.h - egenskriven kod
// header fil / include guards mm samma som i snake.h

#ifndef MENU_H
#define MENU_H

#include <pic32mx.h>
#include <stdint.h>
#include "display.h"
#include "snake_game.h"
#include "interrupt.h"

// @Viggo Schütt 
void view_score(uint32_t score);

// @Viggo Schütt 
void game_over_screen();

// @Viggo Schütt 
uint8_t start_menu();

// @Måns Abrahamsson
void int_to_char(char* int_string, uint32_t num);

#endif