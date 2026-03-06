#ifndef APP_H
#define APP_H

#include <Arduino.h>
#include "input.h"
#include "states_displays.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define ANCHO_PANTALLA 128
#define ALTO_PANTALLA 64
#define DIRECCION_OLED 0x3C

extern bool selectPressed;
extern unsigned long initStart;
extern bool initStarted;

extern int menu_count;

extern Adafruit_SSD1306 display;

extern unsigned long interval;

enum state
{
    INIT,
    MAIN_MENU,
    SETTINGS_MENU,
    GAME_PONG,
    GAME_SNAKE,
    LAST_STATE
};

extern int max_state;

extern state current_state;

extern Input input;

bool canMove(unsigned long interval);

#endif