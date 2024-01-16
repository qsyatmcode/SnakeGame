#include <iostream>
#include <chrono>
#include <thread>
#include "Drawer.h"

using namespace std::this_thread;
using namespace std::chrono;

int main() {
    Snake* snake = new Snake(Position(15, 10));

    Position headpos = snake->HeadPosition();
    for(int i = 0; i < 3; i++){
        SnakePart* part = new SnakePart(headpos + Position(0, i));
        snake->AddPart(part);
    }

    Drawer &drawer = Drawer::GetInstance();
    drawer.Init(snake, 30, 30);

    bool isDead = false;

    while(!isDead){
        sleep_for(100ms);
        drawer.Draw(GetInputAction(), isDead);
    }

    std::cin.get();
}