#pragma once
#include "GBehavior.h"
#include "GMOSnake.h"

template <class T>
class GBSnakeCheckDeath :
    public GBehavior<T>
{
public:
    GBSnakeCheckDeath();
    GBSnakeCheckDeath(std::string name);

    void Initialize() override;
    void UpdateObject() override;
    void HandleEvent(SDL_Event& event) override;

    void GLInitialize() override;
    void GLUpdateObject() override;
    void GLHandleEvent(SDL_Event& event) override;
private:
};

template<class T>
inline GBSnakeCheckDeath<T>::GBSnakeCheckDeath()
{
    this->SetName("GBSnakeCheckDeath");
}

template<class T>
inline GBSnakeCheckDeath<T>::GBSnakeCheckDeath(std::string name)
{
    this->SetName("GBSnakeCheckDeath<" + name + ">");
}

template<class T>
inline void GBSnakeCheckDeath<T>::Initialize()
{
}

template<class T>
inline void GBSnakeCheckDeath<T>::UpdateObject()
{
    int x = this->GetObject()->GetStatus().pos.x, y = this->GetObject()->GetStatus().pos.y;
    if (x < 0 || x > 3835 || y < 0 || y > 2155) {
        SDL_Event event;
        event.type = SDL_QUIT;
        SDL_PushEvent(&event);
    }

    TurnPoint point;
    point.pos.x = this->GetObject()->GetStatus().pos.x;
    point.pos.y = this->GetObject()->GetStatus().pos.y;
    point.from = this->GetObject()->GetStatus().move.direction;
    int index = 1;
    size_t t = 1;
    for (size_t i = 0; i < this->GetObject()->GetStatus().body.length; ++i) {
        SDL_Rect bodyPart;
        switch (point.from)
        {
        case D_SOUTH:
            bodyPart.x = point.pos.x;
            bodyPart.y = point.pos.y - t * this->GetObject()->GetStatus().size.h;
            break;
        case D_NORTH:
            bodyPart.x = point.pos.x;
            bodyPart.y = point.pos.y + t * this->GetObject()->GetStatus().size.h;
            break;
        case D_EAST:
            bodyPart.x = point.pos.x - t * this->GetObject()->GetStatus().size.w;
            bodyPart.y = point.pos.y;
            break;
        case D_WEST:
            bodyPart.x = point.pos.x + t * this->GetObject()->GetStatus().size.w;
            bodyPart.y = point.pos.y;
            break;
        }
        if (index <= this->GetObject()->GetStatus().body.turnPoints.size()) {
            if (this->GetObject()->GetStatus().body.turnPoints[this->GetObject()->GetStatus().body.turnPoints.size() - index].pos.x == bodyPart.x && this->GetObject()->GetStatus().body.turnPoints[this->GetObject()->GetStatus().body.turnPoints.size() - index].pos.y == bodyPart.y) {
                point = this->GetObject()->GetStatus().body.turnPoints[this->GetObject()->GetStatus().body.turnPoints.size() - index];
                index += 1;
                t = 0;
            }
        }

        if (this->GetObject()->GetStatus().pos.x == bodyPart.x && this->GetObject()->GetStatus().pos.y == bodyPart.y) {
            SDL_Event event;
            event.type = SDL_QUIT;
            SDL_PushEvent(&event);
        }

        t++;
    }
}

template<class T>
inline void GBSnakeCheckDeath<T>::HandleEvent(SDL_Event& event)
{
}

template<class T>
inline void GBSnakeCheckDeath<T>::GLInitialize()
{
}

template<class T>
inline void GBSnakeCheckDeath<T>::GLUpdateObject()
{
    int x = this->GetObject()->GetStatus().pos.x, y = this->GetObject()->GetStatus().pos.y;
    if (x < 0 || x > 3835 || y < 0 || y > 2155) {
        SDL_Event event;
        event.type = SDL_QUIT;
        SDL_PushEvent(&event);
    }

    TurnPoint point;
    point.pos.x = this->GetObject()->GetStatus().pos.x;
    point.pos.y = this->GetObject()->GetStatus().pos.y;
    point.from = this->GetObject()->GetStatus().move.direction;
    int index = 1;
    size_t t = 1;
    for (size_t i = 0; i < this->GetObject()->GetStatus().body.length; ++i) {
        SDL_Rect bodyPart;
        switch (point.from)
        {
        case D_SOUTH:
            bodyPart.x = point.pos.x;
            bodyPart.y = point.pos.y - t * this->GetObject()->GetStatus().size.h;
            break;
        case D_NORTH:
            bodyPart.x = point.pos.x;
            bodyPart.y = point.pos.y + t * this->GetObject()->GetStatus().size.h;
            break;
        case D_EAST:
            bodyPart.x = point.pos.x - t * this->GetObject()->GetStatus().size.w;
            bodyPart.y = point.pos.y;
            break;
        case D_WEST:
            bodyPart.x = point.pos.x + t * this->GetObject()->GetStatus().size.w;
            bodyPart.y = point.pos.y;
            break;
        }
        if (index <= this->GetObject()->GetStatus().body.turnPoints.size()) {
            if (this->GetObject()->GetStatus().body.turnPoints[this->GetObject()->GetStatus().body.turnPoints.size() - index].pos.x == bodyPart.x && this->GetObject()->GetStatus().body.turnPoints[this->GetObject()->GetStatus().body.turnPoints.size() - index].pos.y == bodyPart.y) {
                point = this->GetObject()->GetStatus().body.turnPoints[this->GetObject()->GetStatus().body.turnPoints.size() - index];
                index += 1;
                t = 0;
            }
        }

        if (this->GetObject()->GetStatus().pos.x == bodyPart.x && this->GetObject()->GetStatus().pos.y == bodyPart.y) {
            SDL_Event event;
            event.type = SDL_QUIT;
            SDL_PushEvent(&event);
        }

        t++;
    }
}

template<class T>
inline void GBSnakeCheckDeath<T>::GLHandleEvent(SDL_Event& event)
{
}
