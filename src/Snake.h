#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include "SnakePart.h"
#include <vector>

class Snake{
private:
    SnakePart m_Head;
    int m_Size = 1;
    bool m_isDead = false;

    int m_PlayingFieldWidth = 0;
    int m_PlayingFieldHeight = 0;

public:
    explicit Snake(Position startPosition) : m_Head(startPosition){ }
    Snake(const Snake& other) : m_Head(other.m_Head) {}
    Snake() = default;

    ~Snake(){
        for(int i = m_Size - 1; i >= 0; i++){
            delete (*this)[i];
        }
    }

    void AddPart(SnakePart* newPart){
        this->Last().SetNext(newPart);

        m_Size++;
    }

    SnakePart* operator[](int index){
        if(index >= m_Size)
            throw std::out_of_range("Snake: out of range");

        SnakePart* currentPart = &m_Head;
        if(index > 0) {
            for (int i = 0; i < index; i++) {
                currentPart = currentPart->GetNext();
            }
        }

        return currentPart;
    }

    void MoveHead(const Position newPosition){
        m_Head.MoveTo(newPosition);

        Position headPos = m_Head.GetPosition();
        if(headPos.X >= m_PlayingFieldWidth + 1 || headPos.X <= 1 || headPos.Y >= m_PlayingFieldHeight + 1 || headPos.Y <= 1) {// 0 and PlayingFieldX/Y + 1 is a border
            m_isDead = true;
        }else {
            for(int i = 1; i < this->m_Size; i++){
                if(headPos == (*this)[i]->GetPosition())
                    m_isDead = true;
            }
        }
    }

    [[nodiscard]] unsigned Size() const{
        return m_Size;
    }

    [[nodiscard]] bool IsDead() const{
        return m_isDead;
    }

    SnakePart& Last(){
        SnakePart* currentPart = &m_Head;
        for (int i = 0; i < m_Size - 1; i++) {
            SnakePart* next = currentPart->GetNext();
            if(next != nullptr){
                currentPart = next;
            }else{
                return *currentPart;
            }
        }

        return *currentPart;
    }

    Position HeadPosition(){
        return m_Head.GetPosition();
    }

    void SetBorders(int fieldWidth, int fieldHeight){
        m_PlayingFieldWidth = fieldWidth;
        m_PlayingFieldHeight = fieldHeight;
    }
};

#endif //SNAKE_SNAKE_H
