/*
 * MyPaddle.cpp
 *
 *  Created on: Sep 17, 2013
 *      Author: daniel
 */

#include "MyPaddle.h"


MyPaddle::MyPaddle() :
		Paddle() {

}

MyPaddle::~MyPaddle() {

}

MyPaddle* MyPaddle::createMyPaddle() {

	MyPaddle *myPaddle = new MyPaddle();
	if (myPaddle && myPaddle->initWithFile("GameLayer/myPaddle.png")) {
		myPaddle->autorelease();
		return myPaddle;
	}
	CC_SAFE_DELETE(myPaddle);
	return NULL;

}


float MyPaddle::getWidth() {
	return this->getTextureRect().getMaxX();
}

float MyPaddle::getHeight() {
	return this->getTextureRect().getMaxY();
}

b2Body* MyPaddle::getMyPaddleBody() {
	return myPaddleBody;
}

void MyPaddle::setMyPaddleBody(b2Body* myPaddleBody) {
	this->myPaddleBody = myPaddleBody;
}

