#include "input.h"
#include <Arduino.h>
int pinUp = 2;
int pinDown = 19;
int pinRight = 4;
int pinLeft = 16;

Input::Input(int up, int down, int right, int left)
{
    pinUp = up;
    pinDown = down;
    pinRight = right;
    pinLeft = left;
}

void Input::begin()
{
    pinMode(pinUp, INPUT_PULLUP);
    pinMode(pinDown, INPUT_PULLUP);
    pinMode(pinRight, INPUT_PULLUP);
    pinMode(pinLeft, INPUT_PULLUP);
}

int Input::realDirection()
{
    if (digitalRead(pinUp) == LOW)
        return 1;
    if (digitalRead(pinDown) == LOW)
        return 2;
    if (digitalRead(pinRight) == LOW)
        return 3;
    if (digitalRead(pinLeft) == LOW)
        return 4;
    return 0;
}