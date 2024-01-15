#ifndef SNAKE_INPUT_H
#define SNAKE_INPUT_H

#include <conio.h>

#define KEY_UP 80
#define KEY_DOWN 72
#define KEY_LEFT 75
#define KEY_RIGHT 77

enum class MoveAction {
    LEFT = KEY_LEFT, RIGHT = KEY_RIGHT, UP = KEY_UP, DOWN = KEY_DOWN, NONE = 0
};

inline MoveAction GetInputAction(){
    int input = 0;

    if(kbhit())
        input = getch();

    if(input == KEY_LEFT || input == KEY_RIGHT ||input == KEY_UP || input == KEY_DOWN)
        return static_cast<MoveAction>(input);
    else
        return MoveAction::NONE;
}

#endif //SNAKE_INPUT_H
