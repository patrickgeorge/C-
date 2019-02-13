#include "FlyingObject.h"



FlyingObject::FlyingObject()
{
	Point();
	Velocity();
	setPoint(point);
	alive = true;
}


FlyingObject::~FlyingObject()
{
}
