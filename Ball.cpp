/*
 * Ball.cpp
 *
 *  Created on: Sep 17, 2013
 *      Author: daniel
 */

#include "Ball.h"

Ball* Ball::ball = NULL;

Ball::Ball() {


}

Ball::~Ball() {
	// TODO Auto-generated destructor stub
}

Ball* Ball::getBall(){

	if(ball != NULL)
	{
		return ball;
	}
	else
	{
		Ball* ball = new Ball();
		if (ball && ball->initWithFile("ball.png"))
		{
			ball->myInit();
			ball->autorelease();
			return ball;
		}
			CC_SAFE_DELETE(ball);
			return NULL;
	}
}


void Ball::myInit(){
	this->setScale(0.5);
}






