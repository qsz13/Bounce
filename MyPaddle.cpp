/*
 * MyPaddle.cpp
 *
 *  Created on: Sep 17, 2013
 *      Author: daniel
 */

#include "MyPaddle.h"

//MyPaddle* MyPaddle::myPaddle = NULL;

MyPaddle::MyPaddle() :
		Paddle() {
	// paddleBodyDef.userData = myPaddle;

}

MyPaddle::~MyPaddle() {
	// TODO Auto-generated destructor stub
}

MyPaddle* MyPaddle::createMyPaddle() {

	MyPaddle *myPaddle = new MyPaddle();
	if (myPaddle && myPaddle->initWithFile("GameLayer/myPaddle.png")) {
		myPaddle->myInit();
		myPaddle->autorelease();
		return myPaddle;
	}
	CC_SAFE_DELETE(myPaddle);
	return NULL;

}

void MyPaddle::myInit() {
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

