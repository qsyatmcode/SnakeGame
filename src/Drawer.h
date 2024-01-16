#ifndef SNAKE_DRAWER_H
#define SNAKE_DRAWER_H

#include <vector>
#include <iomanip>
#include <iostream>
#include <memory>
#include <exception>
#include <cstdlib>
#include <random>
#include "windows.h"

#include "SnakePart.h"
#include "Snake.h"
#include "Input.h"

enum class VisualDisplays : char {
    SNAKE_PART = '@',
    PLAYING_FIELD_BORDER = '#',
    APPLE = 'o'
};

class Drawer{
private:
    Snake* m_Snake;

    int m_PlayingFieldWidth = 20;
    int m_PlayingFieldHeight = 10;
    bool m_FieldAlreadyDrawer = false;
    int m_Score = 0;
    int m_AppleScore = 8;
    bool m_AppleIsEated = true;
    int m_FontScale = 18;

    Position m_ApplePosition;
    Position m_Velocity;

    std::stringstream m_Field;
    std::default_random_engine m_RandomEngine;

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

    void Init(Snake* snake, int fieldWidth, int fieldHeight){
        m_Snake = snake;
        m_PlayingFieldWidth = fieldWidth;
        m_PlayingFieldHeight = fieldHeight;
        m_Snake->SetBorders(fieldWidth + 1, fieldHeight + 1);
        m_Velocity = Position(0, -1);

        HideCursor();
        SetConsoleFont();
        SetWindowSize(m_FontScale * (m_PlayingFieldHeight + 11), m_FontScale * (m_PlayingFieldWidth + 2));
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

        m_Snake->MoveHead(m_Snake->HeadPosition() + m_Velocity);
    }

    void Draw(MoveAction, bool&);

private:
    Drawer() = default;

    ~Drawer(){
        delete m_instance;
        delete m_Snake;
    }

    void DrawPlayField();
    void DrawApples();

    inline void SetWindowSize(int wndWidth, int wndHeight){
        HWND hWindowConsole = GetConsoleWindow();

        RECT currentPosition;
        GetWindowRect(hWindowConsole, &currentPosition);
        MoveWindow(hWindowConsole, currentPosition.left, currentPosition.top, wndWidth, wndHeight, TRUE);
    }

    void HideCursor(){
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(handle, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(handle, &cursorInfo);
    }

    void ClearSnake(){
        for(int i = 0; i < m_Snake->Size(); i++) {
            Position pos = (*m_Snake)[i]->GetPastPosition();
            DrawSymbolAt(pos.X, pos.Y, ' ');
        }
    }

    void SetConsoleFont(){
        HANDLE cHandle = GetStdHandle(STD_OUTPUT_HANDLE);

        CONSOLE_FONT_INFOEX cfi = {0};
        cfi.cbSize = sizeof(cfi);
        cfi.dwFontSize.X = 18;
        cfi.dwFontSize.Y = 18;

        wcscpy_s(cfi.FaceName, L"Terminal");
        SetCurrentConsoleFontEx(cHandle, 0, &cfi);
    }

    void DrawScore(){
        SetCursorPosition(m_PlayingFieldWidth + 4, (m_PlayingFieldHeight + 2) / 2);
        std::cout << std::setfill('0') << std::setw(5) << m_Score;
    }

    void DrawSymbolAt(int x, int y, char symbol){
        COORD coord;
        coord.X = x - 1;
        coord.Y = y - 1;

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        std::cout << symbol;
    }

    void SetCursorPosition(int x, int y){
        COORD coord;
        coord.X = x - 1;
        coord.Y = y - 1;

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
};

#endif //SNAKE_DRAWER_H
