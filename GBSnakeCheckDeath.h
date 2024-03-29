#pragma once
#include "GBehavior.h"

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
    if (x < 0 || x > 1075 || y < 0 || y > 715) {
        SDL_Event event;
        event.type = SDL_QUIT;
        SDL_PushEvent(&event);
    }
}

template<class T>
inline void GBSnakeCheckDeath<T>::HandleEvent(SDL_Event& event)
{
}
