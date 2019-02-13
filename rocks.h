#include "FlyingObject.h"
#include "uiDraw.h"
#include <vector>

#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10



// Define the following classes here:
//   Rock
//   BigRock
//   MediumRock
//   SmallRock

class Rock : public FlyingObject {
private:
	int lives;
	float angle;
	float radius;

public:

	float getRadius() {
		return radius;
	}

	void setRadius(float radius) {
		this->radius = radius;
	}

	float getAngle() {
		return angle;
	}

	void setAngle(float angle) {
		this->angle = angle;
	}

	int getLives() {
		return lives;
	}

	void setLives(int lives) {
		this->lives = lives;
	}

	virtual void rotate() = 0;

	virtual void advance() = 0;

	virtual void draw() = 0;

	virtual void crash() = 0;

	virtual void makeSmallerRock(vector<Rock*> & rocks) = 0;

};


class SmallRock : public Rock {
private:
	int advX;
	int advY;
	int secAdvY;
	int thirdAdvX;

public:

	SmallRock() {
		setLives(1);
		setAngle(1);
		setAlive();
		Point();
		Velocity();

	}

	SmallRock(Point point, Velocity velocity, int advX, int advY, int secAdvY, int thirdAdvX) {
		setLives(1);
		setAngle(1);
		setAlive();
		setRadius(8);
		setPoint(point);
		Velocity();
		setAdvX(advX);
		setAdvY(advY);
		setSecAdvY(secAdvY);
		setThirdAdvX(thirdAdvX);
	}

	int getAdvX() {
		return advX;
	}

	int getadvY() {
		return advY;
	}

	void setAdvX(int num) {
		advX = num;
	}

	void setAdvY(int num) {
		advY = num;
	}

	int getSecAdvY() {
		return secAdvY;
	}

	void setSecAdvY(int num) {
		secAdvY = num;
	}

	int getThirdAdvX() {
		return thirdAdvX;
	}

	void setThirdAdvX(int thirdAdvX) {
		this->thirdAdvX = thirdAdvX;
	}

	void draw() {
		drawSmallAsteroid(getPoint(), SMALL_ROCK_SPIN);
	}

	void rotate();

	void advance();

	void crash();

	void makeSmallerRock(vector<Rock*> & rocks);
};


class MediumRock : public Rock {
private:
	int advX;
	int advY;
	int secAdvY;

public:

	MediumRock() {
		setLives(1);
		setAngle(1);
		setAlive();
		Point();
		Velocity();
	}

	MediumRock(Point point, Velocity velocity, int advX, int advY, int secAdvY) {
		setLives(1);
		setAngle(1);
		setAlive();
		setRadius(8);
		setPoint(point);
		Velocity();
		setAdvX(advX);
		setAdvY(advY);
		setSecAdvY(secAdvY);
	}

	int getAdvX() {
		return advX;
	}

	int getAdvY() {
		return advY;
	}

	void setAdvX(int num) {
		advX = num;
	}

	void setAdvY(int num) {
		advY = num;
	}

	int getSecAdvY() {
		return secAdvY;
	}

	void setSecAdvY(int num) {
		secAdvY = num;
	}

	void draw() {
		drawMediumAsteroid(getPoint(), MEDIUM_ROCK_SPIN);
	}

	void rotate();

	void advance();

	void crash();

	void makeSmallerRock(vector<Rock*> & rocks);
};

class LargeRock : public Rock {
private:
	int advX;
	int advY;

public:

	LargeRock(Point point) {
		setLives(1);
		setAngle(1);
		setRadius(16);
		setAdvX(random(-1, 2));
		setAdvY(random(-1, 2));
		setAlive();
		setPoint(point);
		Velocity();
	}

	int getAdvX() {
		return advX;
	}

	int getAdvY() {
		return advY;
	}

	void setAdvX(int num) {
		advX = num;
	}

	void setAdvY(int num) {
		advY = num;
	}

	void draw() {
		drawLargeAsteroid(getPoint(), BIG_ROCK_SPIN);
	}

	void rotate();

	void advance();

	void crash();

	void makeSmallerRock(vector<Rock*> & rocks);
};

#endif /* rocks_h */