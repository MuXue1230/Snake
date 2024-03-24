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
	snakeHead.w = this->status.size.w;
	snakeHead.h = this->status.size.h;
	snakeHead.x = this->status.pos.x;
	snakeHead.y = this->status.pos.y;
	SDL_SetRenderDrawColor(this->GetRenderer(), this->status.color.R, this->status.color.G, this->status.color.B, this->status.color.A);
	SDL_RenderFillRect(this->GetRenderer(), &snakeHead);

	SDL_SetRenderDrawColor(this->GetRenderer(), this->status.body.color.R, this->status.body.color.G, this->status.body.color.B, this->status.body.color.A);
	for (size_t i = 0; i < this->status.body.turnPoints.size(); ++i)
	{
		SDL_Rect bodyPart;
		bodyPart.w = this->status.size.w;
		bodyPart.h = this->status.size.h;
		bodyPart.x = this->status.body.turnPoints[i].pos.x;
		bodyPart.y = this->status.body.turnPoints[i].pos.y;

		SDL_RenderFillRect(this->GetRenderer(), &bodyPart);
	}
	SDL_Log("Update x:%d y:%d", snakeHead.x, snakeHead.y);
	SDL_Delay(100);
}
