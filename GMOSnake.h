#pragma once
#include "GMoveableObject.h"

struct TurnPoint
{
	struct Postion
	{
		int x;
		int y;
	};
	Postion pos;
	Direction from;
	unsigned int runLength;
};

struct GMOSnakeStatus
{
	struct Color
	{
		unsigned short R;
		unsigned short G;
		unsigned short B;
		unsigned short A;
	};
	struct Size
	{
		unsigned int w;
		unsigned int h;
	};
	struct Postion
	{
		int x;
		int y;
	};
	struct MoveInfo
	{
		unsigned int speed;
		Direction direction;
	};
	struct SnakeBody
	{
		std::vector<TurnPoint> turnPoints;
		unsigned int length;
		Color color;
	};
	Color color;
	Size size;
	Postion pos;
	MoveInfo move;
	SnakeBody body;
};

class GMOSnake :
    public GMoveableObject
{
public:
    GMOSnake();
    GMOSnake(std::string name);

	void PreInitialize(SDL_Renderer* renderer);
	void InitializeBehaviors();
	void UpdateBehaviors();
	void HandleBehaviorsEvent(SDL_Event event);

	void Initialize() override;
	void UpdateObject() override;
	// void UpdateObjectExernal() override; // Leave it to Behaviors.
	// void HandleEvent(SDL_Event event) override; // Leave it to Behaviors.
	void UpdateRenderer() override;


	void MoveUp() override { this->status.pos.y -= this->status.move.speed; }
	void MoveDown() override { this->status.pos.y += this->status.move.speed; }
	void MoveLeft() override { this->status.pos.x -= this->status.move.speed; }
	void MoveRight() override { this->status.pos.x += this->status.move.speed; }

	// Getter & Setter
	GMOSnakeStatus GetStatus() const { return this->status; }
	std::vector<std::shared_ptr<GBehavior<GMOSnake>>> GetBehaviors() const { return this->behaviors; }
	void SetBodyColor(unsigned short R, unsigned short G, unsigned short B, unsigned short A)
	{
		if (R > 0x00ff || G > 0x00ff || B > 0x00ff || A > 0x00ff) throw ColorError();
		this->status.body.color = { R, G, B, A };
	}
	void SetBodyLength(unsigned int length) { this->status.body.length = length; }
	void SetSpeed(unsigned int speed) { this->status.move.speed = speed; }
	void SetLength(unsigned int length) { this->status.body.length = length; }
	void SetDirection(Direction direction) { this->status.move.direction = direction; }
	void SetColor(unsigned short R, unsigned short G, unsigned short B, unsigned short A)
	{
		if (R > 0x00ff || G > 0x00ff || B > 0x00ff || A > 0x00ff) throw ColorError();
		this->status.color = { R, G, B, A };
	}
	void SetSize(unsigned int w, unsigned int h)
	{
		this->status.size = { w, h };
	}
	void SetPos(int x, int y) {
		this->status.pos = { x, y };
	}
	void AddBodyTurnPoint()
	{
		TurnPoint turnPoint;
		turnPoint.pos.x = this->status.pos.x;
		turnPoint.pos.y = this->status.pos.y;
		turnPoint.from = this->status.move.direction;
		turnPoint.runLength = 0;
		this->status.body.turnPoints.push_back(turnPoint);
        SDL_Log("[%s] New TurnPoint has been Added: { x: %d, y: %d }", this->GetName().c_str(), turnPoint.pos.x, turnPoint.pos.y);
	}
	TurnPoint DeleteLastTurnPoint()
	{ 
		TurnPoint temp = this->status.body.turnPoints[0];
		status.body.turnPoints.erase(status.body.turnPoints.begin());
		return temp;
	}

	// Handle Behaviors
	void AddBehaviors(std::shared_ptr<GBehavior<GMOSnake>> behavior)
	{
		this->behaviors.push_back(behavior);
	}
private:
	GMOSnakeStatus status;
	std::vector<std::shared_ptr<GBehavior<GMOSnake>>> behaviors;
	SDL_Rect snakeHead;
	std::vector<SDL_Rect> snakeBodies;
};

