/*
 * Ball.cpp
 *
 *  Created on: Sep 17, 2013
 *      Author: daniel
 */

#include "Ball.h"
Ball* Ball::ball = NULL;

Ball::Ball() {
	velocity.speed = 20;

	velocity.x = 10+rand()%73205/10000;
	if (rand()&1) 
		velocity.x = -velocity.x;
	velocity.y = -sqrt(velocity.speed*velocity.speed - velocity.x * velocity.x);

	frameLasted = 0;
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

		if (ball && ball->initWithFile("GameLayer/ball.png"))
		{
			ball->myInit();
			//ball->autorelease();
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

Velocity Ball::getVelocity(){
	return velocity;
}

Velocity Ball::setVelocity(Velocity v){
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
	return CCRectMake(this->getPosition().x-s.width/2, this->getPosition().y-s.height/2, s.width, s.height);

	 
}
       

void Ball::frameAddOne(){
	frameLasted++;

}
int Ball::getFrameLasted(){
	return frameLasted;

}
