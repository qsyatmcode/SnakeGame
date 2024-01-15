#ifndef SNAKE_SNAKEPART_H
#define SNAKE_SNAKEPART_H

#include <stdexcept>
#include <vector>

struct Position{
    int X = 0;
    int Y = 0;

    Position(int x, int y) : X(x), Y(y) {}
    Position() = default;

    Position& operator-(Position other){
        this->X - other.X;
        this->Y - other.Y;

        return *this;
    }

    Position& operator+(Position other){
        this->X += other.X;
        this->Y += other.Y;

        return *this;
    }

    bool operator==(Position other) const{
        return (X == other.X && Y == other.Y);
    }
};

//==========================================================================
class SnakePart;
void MovePartTo(SnakePart&, const Position&);

struct SnakePartMoveEvent{
    inline void Invoke(SnakePart& part, const Position& newPos){
        if(m_Listeners.empty())
            return;

        for(void (*listener) (SnakePart&, const Position&) : m_Listeners){
            listener(part, newPos);
        }
    }
    SnakePartMoveEvent() = default;

    explicit SnakePartMoveEvent(void (*function) (SnakePart&, const Position&)){
        m_Listeners.push_back(function);
    }

    bool Empty(){
        return m_Listeners.empty();
    }

    SnakePartMoveEvent(SnakePartMoveEvent& other){
        this->m_Listeners = other.m_Listeners;
    }

    SnakePartMoveEvent& operator+=(SnakePartMoveEvent&& other){
        for(void (*otherListener) (SnakePart&, const Position&) : other.m_Listeners){
            this->m_Listeners.push_back(otherListener);
        }
        return *this;
    }
    SnakePartMoveEvent& operator+=(void (*newListener) (SnakePart&, const Position&)){
        this->m_Listeners.push_back(newListener);
        return *this;
    }

private:
    std::vector<void (*) (SnakePart&, const Position&)> m_Listeners;
};

//==========================================================================

class SnakePart{
    SnakePart* m_Next = nullptr;

    Position m_CurrentPosition;
    Position m_PastPosition;

    void (SnakePart::*m_Listener) (const Position);
public:
    SnakePartMoveEvent MoveEvent;

    friend void MovePartTo(SnakePart& part, const Position& newPos);

    explicit SnakePart(const Position& position) : m_CurrentPosition(position), m_PastPosition(position), MoveEvent() { };
    SnakePart(const SnakePart& other) : m_CurrentPosition(other.m_CurrentPosition), m_PastPosition(other.m_PastPosition), m_Next(other.m_Next) {}
    SnakePart() = default;

    inline void SetNext(SnakePart& next){
        m_Next = &next;
       // m_Next->MoveEvent += SnakePartMoveEvent(MovePartTo);
        //m_Next->MoveEvent += MovePartTo;
        //m_Next->m_Listener = &SnakePart::MoveTo;
    }
    inline SnakePart* GetNext() const{
        if(m_Next == nullptr) {
            return m_Next;
            //throw std::out_of_range("SnakePart: out of range");
        }
        return m_Next;
    }
    inline void MoveTo(const Position newPosition){
        m_PastPosition = m_CurrentPosition;
        m_CurrentPosition = newPosition;

//            if(MoveEvent.Empty())
//                throw std::exception();
            //MoveEvent.Invoke(*this, m_PastPosition);
        //(this->*m_Listener)(newPosition);
        if(m_Next != nullptr)
            m_Next->MoveTo(m_PastPosition);
    }

    inline Position GetPosition() const{
        return m_CurrentPosition;
    }

    inline Position GetPastPosition() const{
        return m_PastPosition;
    }

//    SnakePart& operator=(const SnakePart& other){
//        m_CurrentPosition = other.m_CurrentPosition;
//        m_PastPosition = other.m_PastPosition;
//        return *this;
//    }
};

inline void MovePartTo(SnakePart& part, const Position& newPos){ // called after the MoveEvent is fired
    part.m_PastPosition = part.m_CurrentPosition;
    part.m_CurrentPosition = newPos;
}

//inline void MovePartTo(SnakePart& part, const Position& newPos);

#endif //SNAKE_SNAKEPART_H
