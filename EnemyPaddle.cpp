/*
 * EnemyPaddle.cpp
 *
 *  Created on: Sep 17, 2013
 *      Author: daniel
 */

#include "EnemyPaddle.h"



EnemyPaddle* EnemyPaddle::enemyPaddle = NULL;
EnemyPaddle::EnemyPaddle():Paddle() {
	paddleBodyDef.userData = enemyPaddle;

}

EnemyPaddle::~EnemyPaddle() {
	// TODO Auto-generated destructor stub
}

EnemyPaddle* EnemyPaddle::getEnemyPaddle(){
	if(enemyPaddle != NULL)
	{
		return enemyPaddle;
	}
	else
	{
		enemyPaddle =new EnemyPaddle();
		if(enemyPaddle && enemyPaddle->initWithFile("paddle.png")){
				enemyPaddle->myInit();
				enemyPaddle->autorelease();
				return enemyPaddle;
		}
		CC_SAFE_DELETE(enemyPaddle);
		return NULL;
	}
}

void EnemyPaddle::myInit(){
    this->setScale(ENEMY_PADDLE_SCALE);
}


float EnemyPaddle::getWidth(){
    return this->getTextureRect().getMaxX()*ENEMY_PADDLE_SCALE;
}

float EnemyPaddle::getHeight(){
    return this->getTextureRect().getMaxY()*ENEMY_PADDLE_SCALE;
}

b2Body* EnemyPaddle::getEnemyPaddleBody(){
	return enemyPaddleBody;

}
void EnemyPaddle::setEnemyPaddleBody(b2Body* enemyPaddleBody){
	this->enemyPaddleBody = enemyPaddleBody;

}
