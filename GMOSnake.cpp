#include "GMOSnake.h"

GMOSnake::GMOSnake()
{
	this->SetColor(0, 0, 0, 0);
	this->SetSize(0, 0);
	this->SetPos(0, 0);
	this->SetBodyColor(0, 0, 0, 0);
	this->SetDirection(Direction::D_EAST);
	this->SetSpeed(0);
	this->SetLength(0);
	this->SetName("Snake");

	this->AddBehaviors(GBSnakeMove<GMOSnake>("BasicMove"));
}

GMOSnake::GMOSnake(std::string name)
{
	this->SetColor(0, 0, 0, 0);
	this->SetSize(0, 0);
	this->SetPos(0, 0);
	this->SetBodyColor(0, 0, 0, 0);
	this->SetDirection(Direction::D_EAST);
	this->SetSpeed(0);
	this->SetLength(0);
	this->SetName("Snake<"+name+">");
}

void GMOSnake::Initialize()
{
	this->SetColor(0, 255, 0, 255);
	this->SetSize(5, 5);
	this->SetPos(540, 360);
	this->SetBodyColor(100, 255, 100, 255);
	this->SetDirection(Direction::D_EAST);
	this->SetLength(15);
	this->SetSpeed(5);
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
	TurnPoint point = { this->status.pos.x, this->status.pos.y, this->status.move.direction, this->status.move.direction };
	int index = 1;
	for (size_t i = 0; i < this->status.body.length; ++i)
	{
		SDL_Rect bodyPart;
		bodyPart.w = this->status.size.w;
		bodyPart.h = this->status.size.h;
		switch (point.from)
		{
		case D_NORTH:
			bodyPart.x = point.pos.x;
			bodyPart.y = point.pos.y - i * this->status.size.h;
			break;
		case D_SOUTH:
			bodyPart.x = point.pos.x;
			bodyPart.y = point.pos.y + (i + 1)*this->status.size.h;
			break;
		case D_WEST:
			bodyPart.x = point.pos.x - i * this->status.size.w;
			bodyPart.y = point.pos.y;
			break;
		case D_EAST:
			bodyPart.x = point.pos.x + (i + 1)*this->status.size.w;
			bodyPart.y = point.pos.y;
			break;
		}
		if (index <= this->status.body.turnPoints.size()) {
			if (this->status.body.turnPoints[this->status.body.turnPoints.size() - index].pos.x == bodyPart.x && this->status.body.turnPoints[this->status.body.turnPoints.size() - index].pos.y == bodyPart.y) {
				point = this->status.body.turnPoints[this->status.body.turnPoints.size() - index];
				index += 1;
			}
		}

		SDL_RenderFillRect(this->GetRenderer(), &bodyPart);
	}
}
