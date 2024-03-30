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
	void GLPreInitialize(T& obj, SDL_GLContext context);

	virtual void Initialize() {};
	virtual void UpdateObject() {};
	virtual void HandleEvent(SDL_Event& event) {};

    virtual void GLInitialize() {};
    virtual void GLUpdateObject() {};
    virtual void GLHandleEvent(SDL_Event& event) {};

	// Getter & Setter
	std::string GetName() const { return this->name; }
	SDL_Renderer* GetRenderer() const { return this->renderer; }
    SDL_GLContext GetContext() const { return this->context; }
	T* GetObject() const { return this->obj; }
	void SetName(std::string name)
	{
		this->name = name;
	}
private:
	T* obj;
	std::string name;
	SDL_Renderer* renderer;
    SDL_GLContext context;
};

template<class T>
inline void GBehavior<T>::PreInitialize(T& obj, SDL_Renderer* renderer)
{
	this->obj = &obj;
	this->renderer = renderer;
}

template<class T>
inline void GBehavior<T>::GLPreInitialize(T& obj, SDL_GLContext context)
{
    this->obj = &obj;
    this->context = context;
}
