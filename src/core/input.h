#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>

class Input
{
public:
    Input(int up, int down, int right, int left);
    void begin();
    int realDirection();

private:
    int up;
    int down;
    int right;
    int left;
};

#endif
