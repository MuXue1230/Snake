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

void GMOSnake::PreInitialize(SDL_Renderer* renderer)
{
	this->SetRenderer(renderer);
	for (auto& item : this->GetBehaviors()) {
		SDL_Log("> > Pre-initializing Behavior <%s>...", item->GetName().c_str());
		item->PreInitialize(*this, renderer);
	}
}

void GMOSnake::InitializeBehaviors()
{
	for (auto& item : this->GetBehaviors()) {
		SDL_Log("> > Initializing Behavior <%s>...", item->GetName().c_str());
		item->Initialize();
	}
	this->Initialize();
}

void GMOSnake::UpdateBehaviors()
{
	for (auto& item : this->GetBehaviors()) {
		item->UpdateObject();
	}
	this->UpdateObject();
}

void GMOSnake::HandleBehaviorsEvent(SDL_Event event)
{
	for (auto& item : this->GetBehaviors()) {
		item->HandleEvent(event);
	}
	this->HandleEvent(event);
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

void GMOSnake::UpdateObject()
{
	if (this->GetStatus().move.direction == Direction::D_NORTH) this->MoveUp();
	else if (this->GetStatus().move.direction == Direction::D_SOUTH) this->MoveDown();
	else if (this->GetStatus().move.direction == Direction::D_EAST) this->MoveRight();
	else if (this->GetStatus().move.direction == Direction::D_WEST) this->MoveLeft();
	this->UpdateObjectExernal();
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
	TurnPoint point;
	point.pos.x = this->status.pos.x;
	point.pos.y = this->status.pos.y;
	point.from = this->status.move.direction;
	int index = 1;
    size_t t = 0;
	for (size_t i = 0; i < this->status.body.length; ++i) {
		SDL_Rect bodyPart;
		bodyPart.w = this->status.size.w;
		bodyPart.h = this->status.size.h;
		switch (point.from)
		{
		case D_SOUTH:
			bodyPart.x = point.pos.x;
			bodyPart.y = point.pos.y - t * this->status.size.h;
			break;
		case D_NORTH:
			bodyPart.x = point.pos.x;
			bodyPart.y = point.pos.y + t*this->status.size.h;
			break;
		case D_EAST:
			bodyPart.x = point.pos.x - t * this->status.size.w;
			bodyPart.y = point.pos.y;
			break;
		case D_WEST:
			bodyPart.x = point.pos.x + t*this->status.size.w;
			bodyPart.y = point.pos.y;
			break;
		}
		if (index <= this->status.body.turnPoints.size()) {
			if (this->status.body.turnPoints[this->status.body.turnPoints.size() - index].pos.x == bodyPart.x && this->status.body.turnPoints[this->status.body.turnPoints.size() - index].pos.y == bodyPart.y) {
				point = this->status.body.turnPoints[this->status.body.turnPoints.size() - index];
				index += 1;
                t = 0;
			}
		}

        t++;

		SDL_RenderFillRect(this->GetRenderer(), &bodyPart);
	}

    for (size_t i = 0; i < this->status.body.turnPoints.size(); ++i) {
        this->status.body.turnPoints[i].runLength += 1;
    }
    if (this->status.body.turnPoints.size() > 0 && this->status.body.turnPoints[0].runLength >= this->status.body.length) {
        this->DeleteLastTurnPoint();
    }
}
