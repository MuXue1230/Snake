#include "GMOSnake.h"

GMOSnake::GMOSnake()
{
	this->SetColor(0, 0, 0, 0);
	this->SetSize(0, 0);
	this->SetPos(0, 0);
	this->SetBodyColor(0, 0, 0, 0);
	this->SetDirection(Direction::D_EAST);
	this->SetSpeed(0);
	this->SetName("Snake");
}

GMOSnake::GMOSnake(std::string name)
{
	this->SetColor(0, 0, 0, 0);
	this->SetSize(0, 0);
	this->SetPos(0, 0);
	this->SetBodyColor(0, 0, 0, 0);
	this->SetDirection(Direction::D_EAST);
	this->SetSpeed(0);
	this->SetName("Snake<"+name+">");
}

void GMOSnake::Initialize()
{
	this->SetColor(0, 255, 0, 255);
	this->SetSize(5, 5);
	this->SetPos(0, 0);
	this->SetBodyColor(100, 255, 100, 255);
	this->SetDirection(Direction::D_EAST);
	this->SetSpeed(10);
}

void GMOSnake::UpdateRenderer()
{
	snakeHead.w = status.size.w;
	snakeHead.h = status.size.h;
	snakeHead.x = status.pos.x;
	snakeHead.y = status.pos.y;
	SDL_SetRenderDrawColor(this->GetRenderer(), status.color.R, status.color.G, status.color.B, status.color.A);
	SDL_RenderFillRect(this->GetRenderer(), &snakeHead);

	SDL_SetRenderDrawColor(this->GetRenderer(), status.body.color.R, status.body.color.G, status.body.color.B, status.body.color.A);
	for (size_t i = 0; i < status.body.turnPoints.size(); ++i)
	{
		SDL_Rect bodyPart;
		bodyPart.w = status.size.w;
		bodyPart.h = status.size.h;
		bodyPart.x = status.body.turnPoints[i].pos.x * status.size.w;
		bodyPart.y = status.body.turnPoints[i].pos.y * status.size.h;

		SDL_RenderFillRect(this->GetRenderer(), &bodyPart);
	}
}
