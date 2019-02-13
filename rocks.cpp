#include "rocks.h"

// Put your Rock methods here

void Rock::rotate()
{
}

void Rock::advance()
{
}

void Rock::draw()
{
}

void Rock::makeSmallerRock(vector<Rock*> & rocks)
{
}

void Rock::crash()
{
}

void MediumRock::rotate()
{
}

void MediumRock::advance()
{
	Point p = Point(getPoint().getX() - advX, getPoint().getY() - advY - secAdvY);

	setPoint(p);
}

void MediumRock::crash()
{
	setLives(0);
	kill();
}

void MediumRock::makeSmallerRock(vector<Rock*> & rocks)
{
	Rock * newSmall1 = NULL;
	Rock * newSmall2 = NULL;

	newSmall1 = new SmallRock(getPoint(), getVelocity(), getAdvX(), getAdvY(), 0, 3);
	newSmall2 = new SmallRock(getPoint(), getVelocity(), getAdvX(), getAdvY(), 0, -3);

	rocks.push_back(newSmall1);
	rocks.push_back(newSmall2);
}

void LargeRock::rotate()
{
}

void LargeRock::advance()
{
	Point p = Point(getPoint().getX() - advX, getPoint().getY() - advY);

	setPoint(p);
}

void LargeRock::crash()
{
	setLives(0);
	kill();
}

void LargeRock::makeSmallerRock(vector<Rock*> & rocks)
{
	Rock * newMed1 = NULL;
	Rock * newMed2 = NULL;
	Rock * newSmall = NULL;

	newMed1 = new MediumRock(getPoint(), getVelocity(), getAdvX(), getAdvY(), 1);
	newMed2 = new MediumRock(getPoint(), getVelocity(), getAdvX(), getAdvY(), -1);
	newSmall = new SmallRock(getPoint(), getVelocity(), getAdvX(), getAdvY(), 0, 2);

	rocks.push_back(newMed1);
	rocks.push_back(newMed2);
}

void SmallRock::rotate()
{
}

void SmallRock::advance()
{
	Point p = Point(getPoint().getX() - advX - thirdAdvX, getPoint().getY() - advY - secAdvY);

	setPoint(p);
}

void SmallRock::crash()
{
	setLives(0);
	kill();
}

void SmallRock::makeSmallerRock(vector<Rock*> & rocks)
{
}
