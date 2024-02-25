// interrupt.h - egenskriven kod
// samma som andra .h filer

#ifndef INTERRPUT_H
#define INTERRPUT_H


#include <pic32mx.h>
#include "display.h"
#include "snake_game.h"
#define bool uint8_t
#define true 1
#define false 0

//Variabler för knapp-debounce
uint8_t polled_buttons, unreleased_btns, interupted_btns;
bool first_poll;

// debug variabel för externa interrupts
uint8_t interrupt_count;

// Poll_cnt används för att seed:a slumpgeneratorn - "tiden" det tar för att en knapp ska tryckas
uint16_t poll_cnt;

// SKREVS UNDER LABB3 av Måns och Viggo
void init_time();

// Timer interrupts - Viggo ; externa interrupts - Måns
void user_isr();

// chipkitets knappar - Viggo ; externa knappar - Måns
void init_btns();

// @Måns Abrahamsson
uint8_t getbtns ();

// @Måns Abrahamsson
void poll_input();

// @Viggo Schütt
void stop_timer();

#endif
