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

	void GLInitialize() override;
	void GLUpdateObject() override;
	void GLHandleEvent(SDL_Event& event) override;
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
            SDL_Log("[%s->%s] User control turned into: %s.", this->GetObject()->GetName().c_str(), this->GetName().c_str(), this->userMove ?"on":"off");
        }
        if (this->userMove) {
            char key = event.key.keysym.sym;
            if (key == 'w' && this->GetObject()->GetStatus().move.direction != Direction::D_SOUTH && \
                !(this->GetObject()->GetStatus().pos.y == 0)) {
                this->GetObject()->AddBodyTurnPoint();
                this->GetObject()->SetDirection(Direction::D_NORTH);
            }
            else if (key == 's' && this->GetObject()->GetStatus().move.direction != Direction::D_NORTH && \
                !(this->GetObject()->GetStatus().pos.y == 715)) {
                this->GetObject()->AddBodyTurnPoint();
                this->GetObject()->SetDirection(Direction::D_SOUTH);
            }
            else if (key == 'a' && this->GetObject()->GetStatus().move.direction != Direction::D_EAST && \
                !(this->GetObject()->GetStatus().pos.x == 0)) {
                this->GetObject()->AddBodyTurnPoint();
                this->GetObject()->SetDirection(Direction::D_WEST);
            }
            else if (key == 'd' && this->GetObject()->GetStatus().move.direction != Direction::D_WEST && \
                !(this->GetObject()->GetStatus().pos.x == 1075)) {
                this->GetObject()->AddBodyTurnPoint();
                this->GetObject()->SetDirection(Direction::D_EAST);
            }
        }
    }
}

template<class T>
inline void GBSnakeMoveUserControl<T>::GLInitialize()
{
    SDL_Log("[With OpenGL]> > > %s has loaded.", this->GetName().c_str());
}

template<class T>
inline void GBSnakeMoveUserControl<T>::GLUpdateObject()
{
}

template<class T>
inline void GBSnakeMoveUserControl<T>::GLHandleEvent(SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == 'x') {
            this->userMove = !this->userMove;
            SDL_Log("[With OpenGL][%s->%s] User control turned into: %s.", this->GetObject()->GetName().c_str(), this->GetName().c_str(), this->userMove ? "on" : "off");
        }
        if (this->userMove) {
            char key = event.key.keysym.sym;
            if (key == 'w' && this->GetObject()->GetStatus().move.direction != Direction::D_SOUTH && \
                !(this->GetObject()->GetStatus().pos.y == 0)) {
                this->GetObject()->AddBodyTurnPoint();
                this->GetObject()->SetDirection(Direction::D_NORTH);
            }
            else if (key == 's' && this->GetObject()->GetStatus().move.direction != Direction::D_NORTH && \
                !(this->GetObject()->GetStatus().pos.y == 715)) {
                this->GetObject()->AddBodyTurnPoint();
                this->GetObject()->SetDirection(Direction::D_SOUTH);
            }
            else if (key == 'a' && this->GetObject()->GetStatus().move.direction != Direction::D_EAST && \
                !(this->GetObject()->GetStatus().pos.x == 0)) {
                this->GetObject()->AddBodyTurnPoint();
                this->GetObject()->SetDirection(Direction::D_WEST);
            }
            else if (key == 'd' && this->GetObject()->GetStatus().move.direction != Direction::D_WEST && \
                !(this->GetObject()->GetStatus().pos.x == 1075)) {
                this->GetObject()->AddBodyTurnPoint();
                this->GetObject()->SetDirection(Direction::D_EAST);
            }
        }
    }
}
