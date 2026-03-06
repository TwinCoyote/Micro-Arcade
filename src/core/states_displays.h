#ifndef INIT_SCREEN_H
#define INIT_SCREEN_H

#include <Adafruit_SSD1306.h>

void init_screen(Adafruit_SSD1306 &display);
bool end_init_screen();
void main_menu_display(Adafruit_SSD1306 &display);
void settings_display(Adafruit_SSD1306 &display);
void pong_display(Adafruit_SSD1306 &display);
void snake_display(Adafruit_SSD1306 &display);

#endif