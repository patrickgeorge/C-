#include "bullet.h"
#include "uiDraw.h"

#define BULLET_SPEED 10.0
#define _USE_MATH_DEFINES

#include "math.h"

Bullet::Bullet()
{
	Point();
	Velocity();
	FlyingObject::setAlive();
	frames = 40;
}


Bullet::~Bullet()
{
}


void Bullet::advance() {
/*
	Point p = Point(getPoint().getX() + getVelocity().getDx(), getPoint().getY() + getVelocity().getDy());

	setPoint(p);


	*/
	setFrames(getFrames() - 1);

	getPoint().addX(getVelocity().getDx());
	getPoint().addY(getVelocity().getDy());
}



void Bullet::draw()
{
	drawDot(getPoint());
}

void Bullet::fire(Point point, float angle)
{
	setPoint(point); 

	float dX = BULLET_SPEED * (-cos(M_PI / 180.0 * angle));
	float dY = BULLET_SPEED * (sin(M_PI / 180.0 * angle));

	setVelocity(dX, dY);

}

