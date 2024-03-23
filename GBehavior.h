#pragma once
#include "sdl_include.h"

template <class T>
class GBehavior
{
public:
	GBehavior() {}
	GBehavior(std::string name) 
	{
		this->SetName(name);
	}

	void PreInitialize(T& obj, SDL_Renderer* renderer);

	virtual void Initialize();
	virtual void UpdateObject();
	virtual void HandleEvent(SDL_Event& event);

	// Getter & Setter
	std::string GetName() const { return this->name; }
	void SetName(std::string name)
	{
		this->name = name;
	}
private:
	T obj;
	std::string name;
	SDL_Renderer* renderer;
};

template<class T>
inline void GBehavior<T>::PreInitialize(T& obj, SDL_Renderer* renderer)
{
	this->obj = obj;
	this->renderer = renderer;
}

template<class T>
inline void GBehavior<T>::Initialize()
{
}

template<class T>
inline void GBehavior<T>::UpdateObject()
{
}

template<class T>
inline void GBehavior<T>::HandleEvent(SDL_Event& event)
{
}