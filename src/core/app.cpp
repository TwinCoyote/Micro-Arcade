#include "app.h"

bool selectPressed = false;
unsigned long initStart = 0;
bool initStarted = false;

int menu_count = 0;

Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);

unsigned long interval = 200;

int max_state = (int)LAST_STATE;

state current_state = INIT;

Input input(2, 19, 4, 16, 5);

bool canMove(unsigned long interval)
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

void setup()
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

void loop()
{

    int dir = input.realDirection();
    Serial.println(menu_count);
    if (dir == 3)
    {
        menu_count++;
        delay(200);
    }
    if (dir == 4)
    {
        menu_count--;
        delay(200);
    }
    // TODO - Crear antirebote en los botones para eliminar el delay
    current_state = (state)menu_count;
    switch (current_state)
    {
    case INIT:
        if (initStarted == false)
        {
            display.clearDisplay();
            init_screen(display);
            display.display();
            canMove(3000);
            initStarted = true;
            current_state = MAIN_MENU;
        }
        else
        {
            current_state = MAIN_MENU;
        }

        break;

    case MAIN_MENU:
        display.clearDisplay();
        main_menu_display(display);
        display.display();
        canMove(200);
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
    }

    if (menu_count >= max_state)
        menu_count = 1;
    if (menu_count <= 0 && initStarted == false)
        menu_count = max_state - 1;
}