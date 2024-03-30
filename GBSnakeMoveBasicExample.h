#pragma once
#include "GBehavior.h"
#include "GMoveableObject.h"

template <class T>
class GBSnakeMoveBasicExample :
    public GBehavior<T>
{
public:
	GBSnakeMoveBasicExample();
	GBSnakeMoveBasicExample(std::string name);

	void Initialize() override;
	void UpdateObject() override;
	void HandleEvent(SDL_Event& event) override;

    void GLInitialize() override;
    void GLUpdateObject() override;
    void GLHandleEvent(SDL_Event& event) override;
private:
    bool userMove;
};

template<class T>
inline GBSnakeMoveBasicExample<T>::GBSnakeMoveBasicExample()
    :userMove(false)
{
	this->SetName("GBSnakeMoveBasicExampleBehavior");
}

template<class T>
inline GBSnakeMoveBasicExample<T>::GBSnakeMoveBasicExample(std::string name)
    :userMove(false)
{
	this->SetName("GBSnakeMoveBasicExampleBehavior<" + name + ">");
}

template<class T>
inline void GBSnakeMoveBasicExample<T>::Initialize()
{
    SDL_Log("> > > %s has loaded.", this->GetName().c_str());
}

template<class T>
inline void GBSnakeMoveBasicExample<T>::UpdateObject()
{
	if (this->GetObject()->GetStatus().move.direction == Direction::D_EAST && this->GetObject()->GetStatus().pos.x == 3835) {
		this->GetObject()->AddBodyTurnPoint();
		this->GetObject()->SetDirection(Direction::D_NORTH);
	}
	else if (this->GetObject()->GetStatus().move.direction == Direction::D_NORTH && this->GetObject()->GetStatus().pos.y == 0) {
		this->GetObject()->AddBodyTurnPoint();
		this->GetObject()->SetDirection(Direction::D_WEST);
	}
	else if (this->GetObject()->GetStatus().move.direction == Direction::D_WEST && this->GetObject()->GetStatus().pos.x == 0) {
		this->GetObject()->AddBodyTurnPoint();
		this->GetObject()->SetDirection(Direction::D_SOUTH);
	}
	else if (this->GetObject()->GetStatus().move.direction == Direction::D_SOUTH && this->GetObject()->GetStatus().pos.y == 2155) {
		this->GetObject()->AddBodyTurnPoint();
		this->GetObject()->SetDirection(Direction::D_EAST);
	}
}

template<class T>
inline void GBSnakeMoveBasicExample<T>::HandleEvent(SDL_Event& event)
{
}

template<class T>
inline void GBSnakeMoveBasicExample<T>::GLInitialize()
{
    SDL_Log("[With OpenGL]> > > %s has loaded.", this->GetName().c_str());
}

template<class T>
inline void GBSnakeMoveBasicExample<T>::GLUpdateObject()
{
    if (this->GetObject()->GetStatus().move.direction == Direction::D_EAST && this->GetObject()->GetStatus().pos.x == 3835) {
        this->GetObject()->AddBodyTurnPoint();
        this->GetObject()->SetDirection(Direction::D_NORTH);
    }
    else if (this->GetObject()->GetStatus().move.direction == Direction::D_NORTH && this->GetObject()->GetStatus().pos.y == 0) {
        this->GetObject()->AddBodyTurnPoint();
        this->GetObject()->SetDirection(Direction::D_WEST);
    }
    else if (this->GetObject()->GetStatus().move.direction == Direction::D_WEST && this->GetObject()->GetStatus().pos.x == 0) {
        this->GetObject()->AddBodyTurnPoint();
        this->GetObject()->SetDirection(Direction::D_SOUTH);
    }
    else if (this->GetObject()->GetStatus().move.direction == Direction::D_SOUTH && this->GetObject()->GetStatus().pos.y == 2155) {
        this->GetObject()->AddBodyTurnPoint();
        this->GetObject()->SetDirection(Direction::D_EAST);
    }
}

template<class T>
inline void GBSnakeMoveBasicExample<T>::GLHandleEvent(SDL_Event& event)
{
}
