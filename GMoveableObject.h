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

	// Getter & Setter
	GMoveableObjectStatus GetStatus() const { return this->status; }
private:
	GMoveableObjectStatus status;
};

