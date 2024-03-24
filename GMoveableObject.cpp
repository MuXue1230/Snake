#include "GMoveableObject.h"

GMoveableObject::GMoveableObject()
{
	this->status = {
		{ 0, 0, 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, Direction::D_WEST }
	};
}

GMoveableObject::GMoveableObject(std::string name)
{
	this->status = {
		{ 0, 0, 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, Direction::D_WEST }
	};
	this->SetName(name);
}

void GMoveableObject::UpdateObject()
{
	if (this->GetStatus().move.direction == Direction::D_NORTH) this->MoveUp();
	else if (this->GetStatus().move.direction == Direction::D_SOUTH) this->MoveDown();
	else if (this->GetStatus().move.direction == Direction::D_EAST) this->MoveRight();
	else if (this->GetStatus().move.direction == Direction::D_WEST) this->MoveLeft();
	this->UpdateObjectExernal();
}
