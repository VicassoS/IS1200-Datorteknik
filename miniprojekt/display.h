// display.h 

#ifndef DISPLAY_H
#define DISPLAY_H

#include <pic32mx.h>
#include <stdint.h>

// @Måns Abrahamsson
void draw_snake(uint8_t* grid);

// tagen från labbarna
void display_string(int line, char *s);

// tagen från labbarna - liten modifikation (rensa textbuffern)
void display_update();

// tagen från labbarna
void init_display();

// tagen från labbarna
uint8_t send_oled_data(uint8_t data);

// tagen från labbarna
void delay(int cyc);

// @Måns Abrahamsson
void clear_screen();

#endif