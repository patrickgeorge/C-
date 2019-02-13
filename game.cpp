/*************************************************************
 * File: game.cpp
 * Author: Br. Burton
 *
 * Description: Contains the implementations of the
 *  method bodies for the game class.
 *
 * Please DO NOT share this code with other students from
 *  other sections or other semesters. They may not receive
 *  the same code that you are receiving.
 *************************************************************/

#include "game.h"

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"

#include <limits> 
#include <algorithm>
#include <vector>
using namespace std;

#define OFF_SCREEN_BORDER_AMOUNT 5


/***************************************
 * GAME CONSTRUCTOR
 ***************************************/
Game :: Game(Point tl, Point br)
 : topLeft(tl), bottomRight(br)
{
   // Set up the initial conditions of the game
   score = 0;

   // TODO: Create Rock Vector

   createVector(rocks);
}

/****************************************
 * GAME DESTRUCTOR
 ****************************************/
Game :: ~Game()
{
   // TODO: Check to see if there is currently a rock allocated
   //       and if so, delete it.
	for (int i = 0; i < rocks.size(); i++)
    {
       if (rocks[i] != NULL) {
	   delete rocks[i];
	   rocks[i] = NULL;
	   }
	}
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
   advanceBullets();
   advanceRock();
   advanceShip();

   handleCollisions();
   cleanUpZombies();
}

/***************************************
 * GAME :: ADVANCE BULLETS
 * Go through each bullet and advance it.
 ***************************************/
void Game :: advanceBullets()
{
   // Move each of the bullets forward if it is alive
   for (int i = 0; i < bullets.size(); i++)
   {
      if (bullets[i].isAlive())
      {
         // this bullet is alive, so tell it to move forward
         bullets[i].advance();
         
		 if ((!isOnScreen(bullets[i].getPoint())) &&
			 ((bullets[i].getPoint().getX() > 200) || (bullets[i].getPoint().getX() < -200)))
         {
            // the bullet has left the screen
			 Point p = Point(bullets[i].getPoint().getX() * -1, bullets[i].getPoint().getY());
			 bullets[i].setPoint(p);
         }
         
		 if ((!isOnScreen(bullets[i].getPoint())) &&
			 ((bullets[i].getPoint().getY() > 200) || (bullets[i].getPoint().getY() < -200)))
		 {
			 // the bullet has left the screen
			 Point p = Point(bullets[i].getPoint().getX(), bullets[i].getPoint().getY() * -1);
			 bullets[i].setPoint(p);
		 }

		 if (bullets[i].getFrames() <= 0)
		 {
			 bullets[i].kill();
		 }
      }
   }
}

/**************************************************************************
 * GAME :: ADVANCE ROCK
 *
 * 1. If there is no rock, do nothing
 * 2. If there is a rock, and it's alive, advance it
 * 3. Check if the rock has gone of the screen, and if so, roundabout!
 **************************************************************************/
void Game :: advanceRock()
{
	for (int i = 0; i < 5; i++)
      // we have a rock, make sure it's alive
      if ((rocks[i] != NULL) && (rocks[i]->isAlive()))
      {
          //move it forward
		  rocks[i]->advance();
         
          //check if the rock has gone off the screen
         if ((!isOnScreen(rocks[i]->getPoint())) && 
			 ((rocks[i]->getPoint().getX() > 200) || (rocks[i]->getPoint().getX() < -200)))
         {
             //We have missed the rock. Make a Roundabout!
			 Point p = Point(rocks[i]->getPoint().getX() * -1, rocks[i]->getPoint().getY());
			 rocks[i]->setPoint(p);
         }

		 if ((!isOnScreen(rocks[i]->getPoint())) &&
			 ((rocks[i]->getPoint().getY() > 200) || (rocks[i]->getPoint().getY() < -200)))
		 {
			 //We have missed the rock. Make a Roundabout!
			 Point pnt = Point(rocks[i]->getPoint().getX(), rocks[i]->getPoint().getY() * -1);
			 rocks[i]->setPoint(pnt);
		 }
      }
}

/**************************************************************************
* GAME :: ADVANCE SHIP
* Move the Ship
**************************************************************************/
void Game::advanceShip()
{
	ship.advance();

	if ((!isOnScreen(ship.getPoint())) &&
		((ship.getPoint().getX() > 200) || (ship.getPoint().getX() < -200)))
	{
		// the ship has left the screen
		Point p = Point(ship.getPoint().getX() * -1, ship.getPoint().getY());
		ship.setPoint(p);

	}

	if ((!isOnScreen(ship.getPoint())) &&
		((ship.getPoint().getY() > 200) || (ship.getPoint().getY() < -200)))
	{
		// the ship has left the screen
		Point pnt = Point(ship.getPoint().getX(), ship.getPoint().getY() * -1);
		ship.setPoint(pnt);
	}
}

void Game::createVector(vector<Rock*> & rocks)
{
	for (int i = 0; i < 5; i++)
	{
		rocks.push_back(createRock());

	}

}

/**************************************************************************
 * GAME :: CREATE ROCKS
 * Create Asteroids according to the rules of the game.
 **************************************************************************/
Rock* Game :: createRock()
{

	   Rock * newRock = NULL;

	   Point point(random(-200, 200), random(-200, 200));

	   newRock = new LargeRock(point);

   // TODO: Fill this in
   return newRock;
}

/**************************************************************************
 * GAME :: IS ON SCREEN
 * Determines if a given point is on the screen.
 **************************************************************************/
bool Game :: isOnScreen(const Point & point)
{
   return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
      && point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
      && point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
      && point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

/**************************************************************************
 * GAME :: HANDLE COLLISIONS
 * Check for a collision between a rock and a bullet.
 **************************************************************************/
void Game :: handleCollisions()
{
   // now check for a hit (if it is close enough to any live bullets)
   for (int i = 0; i < bullets.size(); i++)
   {
      if (bullets[i].isAlive())
      {
         // this bullet is alive, see if its too close

         // check if the rock is at this point (in case it was hit)
		  for (int j = 0; j < rocks.size(); j++)
		  {
			  if (rocks[j] != NULL && rocks[j]->isAlive())
			  {
				  // BTW, this logic could be more sophisticated, but this will
				  // get the job done for now...
				  if (fabs(bullets[i].getPoint().getX() - rocks[j]->getPoint().getX()) < CLOSE_ENOUGH
					  && fabs(bullets[i].getPoint().getY() - rocks[j]->getPoint().getY()) < CLOSE_ENOUGH)
				  {
					  //we have a hit!

					  // hit the rock!
					  rocks[j]->makeSmallerRock(rocks);
					  rocks[j]->kill();
					  score += 10;

					  // the bullet is dead as well
     					  bullets[i].kill();
				  }

			  }
		  }
      } // if bullet is alive
      
   } // for bullets

   //Ship & Rock collisions
   for (int k = 0; k < rocks.size(); k++)
   {
	   if (rocks[k] != NULL && rocks[k]->isAlive())
	   {
		   if (fabs(ship.getPoint().getX() - rocks[k]->getPoint().getX()) < CLOSE_ENOUGH
			   && fabs(ship.getPoint().getY() - rocks[k]->getPoint().getY()) < CLOSE_ENOUGH)
		   {
			   rocks[k]->kill();
			   ship.kill();
		   }
	   }
   }
}

/**************************************************************************
 * GAME :: CLEAN UP ZOMBIES
 * Remove any dead objects (take bullets out of the list, deallocate rock)
 **************************************************************************/
void Game :: cleanUpZombies()
{
   // check for dead rock

	for (vector <Rock*> ::iterator it = rocks.begin(); it != rocks.end(); ++it)
   if (*it != NULL && !(*it)->isAlive())
   {
      // the rock is dead, but the memory is not freed up yet
      
      // TODO: Clean up the memory used by the rock
	   delete *it;
	   *it = NULL;
   
   }
   
   // Look for dead bullets
   vector<Bullet>::iterator bulletIt = bullets.begin();
   while (bulletIt != bullets.end())
   {
      Bullet bullet = *bulletIt;
      // Asteroids Hint:
      // If we had a list of pointers, we would need this line instead:
      //Bullet* pBullet = *bulletIt;
      
      if (!bullet.isAlive())
      {
         // If we had a list of pointers, we would need to delete the memory here...
         
         
         // remove from list and advance
         bulletIt = bullets.erase(bulletIt);
      }
      else
      {
         bulletIt++; // advance
      }
   }
}

/***************************************
 * GAME :: HANDLE INPUT
 * accept input from the user
 ***************************************/
void Game :: handleInput(const Interface & ui)
{
   // Change the direction of the ship
   if (ui.isLeft())
   {
      ship.applyThrustLeft();
   }
   
   if (ui.isRight())
   {
     ship.applyThrustRight();
   }

   if (ui.isUp())
   {
	   ship.applyThrustBottom();
   }

   if (ui.isDown())
   {
	   ship.applyThrustTop();
   }
   
   // Check for "Spacebar
   if ((ui.isSpace()) && (ship.isAlive()))
   {
      Bullet newBullet;
      newBullet.fire(ship.getPoint(), 90.00);
      
      bullets.push_back(newBullet);
   }
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw(const Interface & ui)
{
   // draw the rock

   // TODO: Check if you have a valid rock and if it's alive
   // then call it's draw method

	for (int i = 0; i < rocks.size(); i++)
	{
		if ((rocks[i] != NULL) && (rocks[i]->isAlive()))
			rocks[i]->draw();
	}
   // draw the ship

	if (ship.isAlive())
	{
		ship.draw();
	}
   // draw the bullets, if they are alive
   for (int i = 0; i < bullets.size(); i++)
   {
      if (bullets[i].isAlive())
      {
         bullets[i].draw();
      }
   }
   
   // Put the score on the screen
   Point scoreLocation;
   scoreLocation.setX(topLeft.getX() + 5);
   scoreLocation.setY(topLeft.getY() - 5);
   
   drawNumber(scoreLocation, score);

}


/**********************************************************
* Function: getClosestDistance
* Description: Determine how close these two objects will
*   get in between the frames.
**********************************************************/

float Game :: getClosestDistance(FlyingObject &obj1, FlyingObject &obj2)
{
// find the maximum distance traveled
float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
dMax = max(dMax, abs(obj2.getVelocity().getDx()));
dMax = max(dMax, abs(obj2.getVelocity().getDy()));
dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.

float distMin = std::numeric_limits<float>::max();
for (float i = 0.0; i <= dMax; i++)
{
Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));

float xDiff = point1.getX() - point2.getX();
float yDiff = point1.getY() - point2.getY();

float distSquared = (xDiff * xDiff) +(yDiff * yDiff);

distMin = min(distMin, distSquared);
}

return sqrt(distMin);
}


