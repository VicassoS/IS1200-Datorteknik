// snake.h - header fil för att kunna inkluderas snake.c i andra c filer 
// ifndef / endif används som include guards - för att samma fil ska endast inkluderas 1 gång

#ifndef SNAKE_H
#define SNAKE_H

#include <stdint.h>
#include <pic32mx.h>


enum snake_controller {player1, player2};    // Konstaner för spelarens orm - dvs om det är spelares 1 eller 2 

enum direction {right=0, down=1, left=2, up=3}; // konstanter för riktningar som ormen kan röra sig

typedef struct snake_node snake_node;
typedef struct snake snake;             

struct snake_node{
    uint8_t x, y;           //Beskriver ett orm-block som en 2D Vektor.
};

// Snake beskriver typen snake - de delar som skapar en orm
struct snake{
    uint8_t controller;         // beskriver att en snake har en spelare
    uint8_t direction;          // en snake har en rörelseiknting 
    snake_node nodes[1024];     // Längden kan vara lika stor som griden = 1024 celler (16*64)
    uint8_t length;             // beskriver att en snake har en längd
};

// Definierar alla snake.c funktionerrna - @Viggo Schütt

void init_snake(snake* snake_ptr, uint8_t length, uint8_t dir, uint8_t controller);

uint8_t player1_controller(uint8_t input, snake * snake_ptr);

uint8_t player2_controller(uint8_t input, snake * snake_ptr);


#endif