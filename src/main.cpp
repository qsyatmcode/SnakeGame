#include <iostream>
#include <chrono>
#include <thread>
#include "Drawer.h"

using namespace std::this_thread;
using namespace std::chrono;

int main() {
    //Snake snake(Position(10, 5), 3);
    Snake snake(Position(15, 10)); // 0x00000000005ffdf0 | head: 0x00000000005ffdf0

//    Position headpos = snake.HeadPosition();
//    for(int i = 0; i <= 3; i++){
//        Position pos1 = headpos + Position(0, i);
//        SnakePart part1 = SnakePart(pos1);
//        snake.AddPart(part1);
//    }

    Position pos1 = Position(15, 6);
    SnakePart part1 = SnakePart(pos1);
    snake.AddPart(part1);

    Position pos2 = Position(10, 7);
    SnakePart part2 = SnakePart(pos2); // 0x00000000005ffd70
    snake.AddPart(part2);

    Position pos3 = Position(10, 8);
    SnakePart part3 = SnakePart(pos3); // 0x00000000005ffd30
    snake.AddPart(part3);


    Drawer &drawer = Drawer::GetInstance();
    drawer.Init(snake, 30, 15); // snake: 0x0000000000653d00 | 0x0000000000653d00

    bool isDead = false;
    while(!isDead){
        sleep_for(100ms);
        drawer.Draw(GetInputAction(), isDead);
    }

    std::cin.get();
}