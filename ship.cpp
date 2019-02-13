#include "ship.h"

void Ship::applyThrustLeft() {
	canThrust();
	velocity.setDx(velocity.getDx() + THRUST_AMOUNT);
}

void Ship::applyThrustBottom() {
	canThrust();
	velocity.setDy(velocity.getDy() + THRUST_AMOUNT);
}

void Ship::applyThrustRight() {
	canThrust();
	velocity.setDx(velocity.getDx() - THRUST_AMOUNT);
}

void Ship::applyThrustTop()
{
	canThrust();
	velocity.setDy(velocity.getDy() - THRUST_AMOUNT);
}

void Ship::advance() {
	point.addX(velocity.getDx());
	point.addY(velocity.getDy());
}

void Ship::draw() {
		drawShip(point, ROTATE_AMOUNT, canThrust());
}


// Put your ship methods here

