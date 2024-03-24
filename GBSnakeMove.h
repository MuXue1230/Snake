#pragma once
#include "GBehavior.h"

template <class T>
class GBSnakeMove :
    public GBehavior<T>
{
public:
	GBSnakeMove() {
		this->SetName("SnakeMoveBehavior");
	}
	GBSnakeMove(std::string name) {
		this->SetName("SnakeMoveBehavior<" + name + ">");
	}

	void Initialize();
	void UpdateObject();
	void HandleEvent(SDL_Event& event);
};

template<class T>
inline void GBSnakeMove<T>::Initialize()
{
}

template<class T>
inline void GBSnakeMove<T>::UpdateObject()
{
}

template<class T>
inline void GBSnakeMove<T>::HandleEvent(SDL_Event& event)
{
}
