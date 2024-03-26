#pragma once
#include "GBehavior.h"

template <class T>
class GBSnakeMove :
    public GBehavior<T>
{
public:
	GBSnakeMove();
	GBSnakeMove(std::string name);

	void Initialize() override;
	void UpdateObject() override;
	void HandleEvent(SDL_Event& event) override;
};

template<class T>
inline GBSnakeMove<T>::GBSnakeMove()
{
	this->SetName("SnakeMoveBehavior");
}

template<class T>
inline GBSnakeMove<T>::GBSnakeMove(std::string name)
{
	this->SetName("SnakeMoveBehavior<" + name + ">");
}

template<class T>
inline void GBSnakeMove<T>::Initialize()
{
	SDL_Log("Hello, world!");
}

template<class T>
inline void GBSnakeMove<T>::UpdateObject()
{
}

template<class T>
inline void GBSnakeMove<T>::HandleEvent(SDL_Event& event)
{
}
