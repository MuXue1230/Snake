#pragma once
#include "GObject.h"

enum Direction {
	D_NORTH = 0,
	D_SOUTH,
	D_WEST,
	D_EAST,
};

struct GMoveableObjectStatus
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
	Color color;
	Size size;
	Postion pos;
	MoveInfo move;
};

class GMoveableObject :
    public GObject
{
public:
    GMoveableObject();
    GMoveableObject(std::string name);

	void UpdateObject() override;

	virtual void UpdateObjectExernal() {}
	virtual void MoveUp() { this->status.pos.y += this->status.move.speed; }
	virtual void MoveDown() { this->status.pos.y -= this->status.move.speed; }
	virtual void MoveLeft() { this->status.pos.x -= this->status.move.speed; }
	virtual void MoveRight() { this->status.pos.x += this->status.move.speed; }

	// Getter & Setter
	GMoveableObjectStatus GetStatus() const { return this->status; }
	void SetSpeed(unsigned int speed) { this->status.move.speed = speed; }
	void SetDirection(Direction direction) { this->status.move.direction = direction; }

	// Handle Behaviors
	void AddBehaviors(GBehavior<GMoveableObject> behavior)
	{
		this->behaviors.push_back(std::make_shared<GBehavior<GMoveableObject>>(behavior));
	}
private:
	GMoveableObjectStatus status;
	std::vector<std::shared_ptr<GBehavior<GMoveableObject>>> behaviors;
};

