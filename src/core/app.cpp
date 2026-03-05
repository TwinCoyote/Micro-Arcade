#include <Arduino.h>
#include "app.h"
#include "input.h"
#include "states_displays.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define ANCHO_PANTALLA 128
#define ALTO_PANTALLA 64
#define DIRECCION_OLED 0x3C

// ============================
// Variables internas del módulo
// ============================

static int menu_count = 0;
static unsigned long interval = 200;

static Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);
static Input input(2, 19, 4, 16);

enum State
{
    INIT,
    MAIN_MENU,
    SETTINGS_MENU,
    GAME_PONG,
    GAME_SNAKE,
    LAST_STATE
};

static State current_state = INIT;

// ============================
// Funciones internas privadas
// ============================

static bool canMove(unsigned long interval)
{
    static unsigned long previousTime = 0;
    unsigned long currentTime = millis();

    if (currentTime - previousTime >= interval)
    {
        previousTime = currentTime;
        return true;
    }
    return false;
}

// ============================
// Funciones públicas del módulo
// ============================

void appInit()
{

    Serial.begin(115200);

    if (!display.begin(SSD1306_SWITCHCAPVCC, DIRECCION_OLED))
    {
        Serial.println(F("Error en la asignación de SSD1306"));
        for (;;)
            ;
    }

    input.begin();

    display.clearDisplay();
    display.display();
}

void appUpdate()
{

    int dir = input.realDirection();

    if (dir == 4 && canMove(200))
    {
        menu_count--;
    }

    if (dir == 3 && canMove(200))
    {
        menu_count++;
    }

    if (menu_count > LAST_STATE - 1)
    {
        menu_count = 1;
    }

    if (menu_count < 1)
    {
        menu_count = LAST_STATE - 1;
    }

    current_state = (State)menu_count;

    switch (current_state)
    {

    case INIT:
        display.clearDisplay();
        init_screen(display);
        display.display();

        if (canMove(600) && end_init_screen())
        {
            current_state = MAIN_MENU;
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
        display.clearDisplay();
        snake_display(display);
        display.display();
        break;

    default:
        break;
    }
}