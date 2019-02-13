#pragma once

#include "FlyingObject.h"
#include <cmath>

#define BULLET_SPEED 5
#define BULLET_LIFE 40

class Bullet : public FlyingObject
{
private:
	float angle;
	int frames;

public:
	Bullet();
	~Bullet();

	int getFrames() {
		return frames;
	}

	void setFrames(int frames) {
		this->frames = frames;
	}

	void advance();
	virtual void draw();
	void fire(Point point, float angle);
};

