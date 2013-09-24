/*
 * Ball.cpp
 *
 *  Created on: Sep 17, 2013
 *      Author: daniel
 */

#include "Ball.h"
Ball* Ball::ball = NULL;

Ball::Ball() {
	velocity = 15;

}

Ball::~Ball() {
	// TODO Auto-generated destructor stub
}

Ball* Ball::getBall(){

//	if(ball != NULL)
//	{
//		return ball;
//	}
//	else
//	{
		Ball* ball = new Ball();

		if (ball && ball->initWithFile("ball.png"))
		{
			ball->myInit();
			ball->autorelease();
			return ball;
		}
			CC_SAFE_DELETE(ball);
			return NULL;
	//}
}


void Ball::myInit(){
	//this->setScale(BALL_SCALE);
}


float Ball::getWidth(){
	return this->getTextureRect().getMaxY();
}

float Ball::getHeight(){
	return this->getTextureRect().getMaxX();
}

float Ball::getRadius(){
	return this->getTextureRect().getMaxX()/2;
}

int Ball::getVelocity(){
	return velocity;
}

void Ball::setVelocity(int v){
	velocity = v;
}

b2Body* Ball::getBallBody(){
	return ballBody;
}
void Ball::setBallBody(b2Body* ballBody){
	this->ballBody = ballBody;
}

CCRect Ball::rect(){

	CCSize s = this->getContentSize();
	return CCRectMake(this->getPosition().x, this->getPosition().y, s.width/2, s.height/2);
	 
}
       
