#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5



// Put your Ship class here

#include <iostream>

#include "point.h"
#include "velocity.h"
#include "uiDraw.h"
#include "uiInteract.h"


class Ship {
private:
	Point point;
	Velocity velocity;
	bool alive;
	int fuel;
	bool thrust;
	bool landed;
	float gravity;

public:
	Ship() {
		setAlive(true);
		setLanded(false);
		thrust = true;
	}

	Point getPoint() const {
		return point;
	}

	void setPoint(Point point) {
		this->point = point;
	}

	Velocity getVelocity() const {
		return velocity;
	}

	bool isAlive() {
		return alive;
	}

	bool isLanded() {
		return landed;
	}

	int getFuel() {
		return fuel;
	}

	bool canThrust() {
		if (isAlive())
		{
			return thrust;
		}
		else if (!isAlive()) {
			thrust = false;
			return thrust;
		}
	}

	bool cantThrust() {
		return thrust = false;
	}

	void setLanded(bool landed) {
		this->landed = landed;
	}

	void setAlive(bool alive) {
		this->alive = alive;
	}

	void kill() {
		this->alive = false;
	}

	void setFuel(int fuel) {
		this->fuel = fuel;
	}

	void applyGravity(float gravity) {
		velocity.setDy(velocity.getDy() - (gravity / 10));
	}

	void applyThrustLeft();
	void applyThrustBottom();
	void applyThrustRight();
	void applyThrustTop();

	void advance();

	void draw();

};

#endif /* ship_h */
