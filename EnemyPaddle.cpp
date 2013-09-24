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
	velocity = 100;
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
		if(enemyPaddle && enemyPaddle->initWithFile("enemyPaddle.png")){
				enemyPaddle->myInit();
				enemyPaddle->autorelease();
				return enemyPaddle;
		}
		CC_SAFE_DELETE(enemyPaddle);
		return NULL;
	}
}

void EnemyPaddle::myInit(){
    this->setScaleX(ENEMY_PADDLE_SCALE_X);
    this->setScaleY(ENEMY_PADDLE_SCALE_Y);
}


float EnemyPaddle::getWidth(){
    return this->getTextureRect().getMaxX()*ENEMY_PADDLE_SCALE_X;
}

float EnemyPaddle::getHeight(){
    return this->getTextureRect().getMaxY()*ENEMY_PADDLE_SCALE_Y;
}

b2Body* EnemyPaddle::getEnemyPaddleBody(){
	return enemyPaddleBody;

}
void EnemyPaddle::setEnemyPaddleBody(b2Body* enemyPaddleBody){
	this->enemyPaddleBody = enemyPaddleBody;

}

void EnemyPaddle::move(Ball *ball){
	CCPoint ballPosition = ball->getPosition();
	if(ballPosition.x+ball->getWidth()/2 < this->getPosition().x){
		b2Vec2 v = b2Vec2(-50,0);
    	enemyPaddleBody->SetLinearVelocity(v);
	}
	else if(ballPosition.x+ball->getWidth()/2 > this->getPosition().x){
		b2Vec2 v = b2Vec2(50,0);
    	enemyPaddleBody->SetLinearVelocity(v);
	}
	else{
		b2Vec2 v = b2Vec2(0,0);
    	enemyPaddleBody->SetLinearVelocity(v);
	}
	//this->setPosition(ccp(ballPosition.x,this->getPosition().y));
}
