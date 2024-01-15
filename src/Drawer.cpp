#include "Drawer.h"
#include <sstream>

void Drawer::DrawPlayField() {
    int height = m_PlayingFieldHeight + 1; // + 2 for borders
    int width = m_PlayingFieldWidth + 1;

    // todo stringStream
    //std::stringstream m_Field;

    char borderChar = static_cast<char>(VisualDisplays::PLAYING_FIELD_BORDER);

    if(!m_FieldAlreadyDrawer) {
        for (int i = 0; i <= height; i++) {
            if (i == 0 || i == height) {
                m_Field << std::setfill(borderChar) << std::setw(width + 2) << "\n";
                continue;
            }
            m_Field << borderChar;
            m_Field << std::setfill(' ') << std::setw(width) << borderChar << "\n";
        }
    }

    std::cout << m_Field.str();
    m_FieldAlreadyDrawer = true;
}

void Drawer::Draw(MoveAction moveDirection, bool& isDead) {
    system("cls");
//    ClearScreen();
    //SetCursorPosition(0, 0);

    isDead = m_Snake.IsDead();

    DrawPlayField();

    // Генерация яблочек..
    MoveSnake(moveDirection);

    char snakeChar = static_cast<char>(VisualDisplays::SNAKE_PART);
    for(int i = 0; i < m_Snake.Size(); i++){
        Position coord = m_Snake[i].GetPosition();
        DrawSymbolAt(coord.X, coord.Y, snakeChar);
    }
}