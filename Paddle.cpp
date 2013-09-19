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



}

b2BodyDef* Paddle::getBodyDef(){
	return &paddleBodyDef;

}



Paddle::~Paddle() {
	// TODO Auto-generated destructor stub
}

