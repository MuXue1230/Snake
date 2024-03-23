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
