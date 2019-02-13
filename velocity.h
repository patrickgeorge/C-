#pragma once
#ifndef VELOCITY_H
#define VELOCITY_H

#include <iostream>

#include "point.h"

class Velocity {
private:
	float dX;
	float dY;

public:
	Velocity() {
		setDx(0);
		setDy(0);
	}

	Velocity(float dX, float dY) {
		setDx(dX);
		setDy(dY);
	}

	float getDx() {
		return dX;
	}

	float getDy() {
		return dY;
	}

	void setDx(float dX);

	void setDy(float dY);
};

#endif




