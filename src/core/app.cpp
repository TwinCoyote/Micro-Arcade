#include <Arduino.h>
#include "input.h"
#include "states_displays.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "games/Snake.h"

#define ANCHO_PANTALLA 128
#define ALTO_PANTALLA 64
#define DIRECCION_OLED 0x3C

bool selectPressed = false;
unsigned long initStart = 0;
bool initStarted = false;
bool continue_init = false;
int menu_count = 0;

bool snakeStarted = false;
bool inMenu = true;

Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);

unsigned long interval = 200;

enum state {
  INIT,
  MAIN_MENU,
  SETTINGS_MENU,
  GAME_PONG,
  GAME_SNAKE,
  LAST_STATE
};
int max_state = (int)LAST_STATE;

state current_state = INIT;

Input input(2, 19, 4, 16, 5, 23);

bool canMove(unsigned long interval) {

  static unsigned long previousTime = 0;

  unsigned long currentTime = millis();

  if (currentTime - previousTime >= interval) {
    previousTime = currentTime;
    return true;
  }

  return false;
}

void setup() {

  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, DIRECCION_OLED)) {
    Serial.println(F("Error en la asignación de SSD1306"));
    for (;;);
  }

  input.begin();

  display.clearDisplay();
  display.display();
}

void loop() {

  int dir = input.realDirection();
  Serial.println(menu_count);
  if (dir == 3) {
    menu_count++;
    delay(200);
  }
  if (dir == 4) {
    menu_count--;
    delay(200);
  }
  // TODO - Crear antirebote en los botones para eliminar el delay

  if (inMenu) {
    current_state = (state)menu_count;
  }

  switch (current_state) {

    case INIT:

      if (!initStarted) {
        display.clearDisplay();
        init_screen(display);
        display.display();
        initStarted = true;
      }

      if (canMove(3000)) {
        current_state = MAIN_MENU;
        menu_count = 1;
        continue_init = true;
      }

      break;

    case MAIN_MENU:
      display.clearDisplay();
      main_menu_display(display);
      display.display();
      break;

    case SETTINGS_MENU:
      display.clearDisplay();
      settings_display(display);
      display.display();
      break;

    case GAME_PONG:
      display.clearDisplay();
      pong_display(display);
      display.display();
      break;

    case GAME_SNAKE:
    Serial.println(dir);

      inMenu = false;

      if (!snakeStarted) {
        display.clearDisplay();
        snake_display(display);   
        display.display();

        snake_init();
        if(dir == 5) snakeStarted = true;
      }

      if (canMove(100) && snakeStarted) {
        
        snake_game();
      }

      if (dir == 6) {   
        inMenu = true;
        snakeStarted = false;
        current_state = MAIN_MENU;
      }

      break;
  }

  if (menu_count >= max_state) menu_count = 1;
  if (menu_count <= 0 && continue_init == true) menu_count = max_state - 1;

}

