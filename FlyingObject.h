#pragma once
#ifndef FLYING_OBJECT_H
#define FLYING_OBJECT_H

#include "point.h"
#include "velocity.h"

using namespace std;

class FlyingObject
{
private:
	Velocity velocity;
	Point point;
	bool alive;

public:
	FlyingObject();
	~FlyingObject();

	Point & getPoint() {
		return point;
	}

	void setPoint(Point point) {
		this->point = point;
	}

	Velocity getVelocity() {
		return velocity;
	}

	void setVelocity(float dX, float dY) {
		velocity.setDx(dX);
		velocity.setDy(dY);
	}

	bool isAlive() {
		return alive;
	}

	void setAlive() {
		alive = true;
	}

	void kill() {
		alive = false;
	}

	virtual void draw() = 0;
};

#endif