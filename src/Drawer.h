#ifndef SNAKE_DRAWER_H
#define SNAKE_DRAWER_H

#include <vector>
#include <iomanip>
#include <iostream>
#include <memory>
#include <exception>
#include "windows.h"

#include "SnakePart.h"
#include "Snake.h"
#include "Input.h"

enum class VisualDisplays : char {
    SNAKE_PART = '@',
    PLAYING_FIELD_BORDER = '#',
    APPLE = 'o'
};

class Drawer{ // TODO: MAKE IT A SINGLETON
private:
    Snake m_Snake;
    int m_PlayingFieldWidth = 20;
    int m_PlayingFieldHeight = 10;
    COORD m_CursorWaitingPosition;
    Position m_Velocity;
    bool m_FieldAlreadyDrawer = false;
    std::stringstream m_Field;

    inline static Drawer* m_instance = nullptr;

public:
    static Drawer& GetInstance(){

        if(m_instance == nullptr) {
            m_instance = new Drawer();
            return *m_instance;
        }else{
            return *m_instance;
        }
    }

    void Init(Snake& snake, int fieldWidth, int fieldHeight){
        m_Snake = snake;
        m_PlayingFieldWidth = fieldWidth;
        m_PlayingFieldHeight = fieldHeight;
        m_CursorWaitingPosition.X = fieldWidth + 1;
        m_CursorWaitingPosition.Y = fieldHeight + 1;
        m_Snake.SetBorders(fieldWidth + 1, fieldHeight + 1);
        m_Velocity = Position(0, -1);
    }

    void MoveSnake(MoveAction direction){
        if(direction == MoveAction::RIGHT)
            m_Velocity = Position(1, 0);
        else if(direction == MoveAction::LEFT)
            m_Velocity = Position(-1, 0);
        else if(direction == MoveAction::UP)
            m_Velocity = Position(0, 1);
        else if(direction == MoveAction::DOWN)
            m_Velocity = Position(0, -1);

        m_Snake.MoveHead(m_Snake.HeadPosition() + m_Velocity);
    }

    void Draw(MoveAction, bool&);

private:
    Drawer() = default;
    explicit Drawer(Snake snake) : m_Snake(snake), m_CursorWaitingPosition() {
        snake.SetBorders(m_PlayingFieldWidth, m_PlayingFieldHeight);
        //SetWindowSize(m_PlayingFieldWidth * m_SizeScaler, m_PlayingFieldHeight * m_SizeScaler);
    }

    ~Drawer(){
        delete m_instance;
    }

    void DrawPlayField();

    inline void SetWindowSize(int wndWidth, int wndHeight){
        HWND hWindowConsole = GetConsoleWindow();

        MoveWindow(hWindowConsole, 500, 500, wndWidth, wndHeight, TRUE);
        //RECT currentPosition;
        //GetWindowRect(hWindowConsole, &currentPosition);
        //MoveWindow(hWindowConsole, currentPosition.left, currentPosition.top, 400, 200, TRUE);
    }

    void ClearScreen(){
//        char fillChar = ' ';
//        COORD tl = {0,0};
//        CONSOLE_SCREEN_BUFFER_INFO s;
//        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
//        GetConsoleScreenBufferInfo(console, &s);
//        DWORD written, cells = s.dwSize.X * s.dwSize.Y;
//        FillConsoleOutputCharacter(console, fillChar, cells, tl, &written);
//        FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
//        SetConsoleCursorPosition(console, tl);
        HWND c = GetConsoleWindow();

        RECT cRect;
        GetWindowRect(c, &cRect);
        for(int i = 0; i <= cRect.top - (m_PlayingFieldHeight + 1); i++){
            std::cout << '\n';
        }
    }

    inline void GetFontSize(){
        // TODO
    }

    void DrawSymbolAt(int x, int y, char symbol){
        COORD coord;
        coord.X = x - 1;
        coord.Y = y - 1;

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        std::cout << symbol;

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), m_CursorWaitingPosition);
    }

    void SetCursorPosition(int x, int y){
        COORD coord;
        coord.X = x - 1;
        coord.Y = y - 1;

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
};

#endif //SNAKE_DRAWER_H
