/*
 * Paddle.cpp
 *
 *  Created on: Sep 17, 2013
 *      Author: daniel
 */

#include "Paddle.h"


Paddle::Paddle() {

	 paddleBodyDef.type = b2_dynamicBody;
	 paddleBodyDef.position.Set(500/PTM_RATIO,500/PTM_RATIO);
	 lengthState = shortPaddle;
	 frameLasted = 0;

}

b2BodyDef* Paddle::getBodyDef(){
	return &paddleBodyDef;

}



Paddle::~Paddle() {
	// TODO Auto-generated destructor stub
}

Paddle::lengthType Paddle::getLengthState(){

	return lengthState;
}

void Paddle::toggleLengthState(){
	if(lengthState==shortPaddle){
		lengthState = longPaddle;
	}
	else if(lengthState==longPaddle){
		lengthState = shortPaddle;
	}
}

void Paddle::setFrameLastedTo0(){
	frameLasted = 0;
}
int Paddle::getFrameLasted(){
	return frameLasted;
}
void Paddle::frameLastedAddOne(){
	frameLasted++;
}