#pragma once
#include "GBehavior.h"
#include "GMoveableObject.h"

template <class T>
class GBSnakeMoveUserControl :
    public GBehavior<T>
{
public:
    GBSnakeMoveUserControl();
    GBSnakeMoveUserControl(std::string name);

	void Initialize() override;
	void UpdateObject() override;
	void HandleEvent(SDL_Event& event) override;
private:
    bool userMove;
};

template<class T>
inline GBSnakeMoveUserControl<T>::GBSnakeMoveUserControl()
    :userMove(false)
{
	this->SetName("GBSnakeMoveUserControlBehavior");
}

template<class T>
inline GBSnakeMoveUserControl<T>::GBSnakeMoveUserControl(std::string name)
    :userMove(false)
{
	this->SetName("GBSnakeMoveUserControlBehavior<" + name + ">");
}

template<class T>
inline void GBSnakeMoveUserControl<T>::Initialize()
{
    SDL_Log("> > > %s has loaded.", this->GetName().c_str());
}

template<class T>
inline void GBSnakeMoveUserControl<T>::UpdateObject()
{
}

template<class T>
inline void GBSnakeMoveUserControl<T>::HandleEvent(SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == 'x') {
            this->userMove = !this->userMove;
        }
        if (this->userMove) {
            switch (event.key.keysym.sym)
            {
            case('w'):
                if (this->GetObject()->GetStatus().move.direction != Direction::D_SOUTH) {
                    this->GetObject()->AddBodyTurnPoint();
                    this->GetObject()->SetDirection(Direction::D_NORTH);
                }
                break;
            case('s'):
                if (this->GetObject()->GetStatus().move.direction != Direction::D_NORTH) {
                    this->GetObject()->AddBodyTurnPoint();
                    this->GetObject()->SetDirection(Direction::D_SOUTH);
                }
                break;
            case('a'):
                if (this->GetObject()->GetStatus().move.direction != Direction::D_EAST) {
                    this->GetObject()->AddBodyTurnPoint();
                    this->GetObject()->SetDirection(Direction::D_WEST);
                }
                break;
            case('d'):
                if (this->GetObject()->GetStatus().move.direction != Direction::D_WEST) {
                    this->GetObject()->AddBodyTurnPoint();
                    this->GetObject()->SetDirection(Direction::D_EAST);
                }
                break;
            default:
                break;
            }
        }
    }
}
