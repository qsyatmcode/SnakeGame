#include "Drawer.h"
#include <sstream>

void Drawer::DrawPlayField() {
//    int height = m_PlayingFieldHeight + 1; // + 2 for borders
//    int width = m_PlayingFieldWidth + 1;
//
//    // todo stringStream
//    //std::stringstream m_Field;
//
//    char borderChar = static_cast<char>(VisualDisplays::PLAYING_FIELD_BORDER);

    if(!m_FieldAlreadyDrawer) {
        int height = m_PlayingFieldHeight + 1; // + 2 for borders
        int width = m_PlayingFieldWidth + 1;

        // todo stringStream
        //std::stringstream m_Field;

        char borderChar = static_cast<char>(VisualDisplays::PLAYING_FIELD_BORDER);

        for (int i = 0; i <= height; i++) {
            if (i == 0 || i == height) {
                m_Field << std::setfill(borderChar) << std::setw(width + 2) << "\n";
                continue;
            }
            m_Field << borderChar;
            m_Field << std::setfill(' ') << std::setw(width) << borderChar << "\n";
        }
        std::cout << m_Field.str();
    }

    //std::cout << m_Field.str();
    m_FieldAlreadyDrawer = true;
}

void Drawer::DrawApples() {

    if(m_AppleIsEated) {
        m_AppleIsEated = false;

        std::uniform_int_distribution<int> y(2, m_PlayingFieldHeight);
        std::uniform_int_distribution<int> x(2, m_PlayingFieldWidth);

        m_ApplePosition = Position(x(m_RandomEngine), y(m_RandomEngine));
    }

    DrawSymbolAt(m_ApplePosition.X, m_ApplePosition.Y, static_cast<char>(VisualDisplays::APPLE));
}

void Drawer::Draw(MoveAction moveDirection, bool& isDead) {
    isDead = m_Snake->IsDead();

    DrawPlayField();

    static int lastScore = 0;
    if(lastScore != m_Score) {
        DrawScore();
        lastScore = m_Score;
    }

    ClearSnake();

    DrawApples();
    // TODO: print score on the screen
    if(m_Snake->HeadPosition() == m_ApplePosition) {
        m_AppleIsEated = true;

        m_Score += m_AppleScore;

        Position newPartPosition = m_Snake->Last().GetPastPosition();
        m_Snake->AddPart(new SnakePart(newPartPosition));
    }

    MoveSnake(moveDirection);

    char snakeChar = static_cast<char>(VisualDisplays::SNAKE_PART);
    for(int i = 0; i < m_Snake->Size(); i++){
        Position coord =(*m_Snake)[i]->GetPosition();
        DrawSymbolAt(coord.X, coord.Y, snakeChar);
    }
}