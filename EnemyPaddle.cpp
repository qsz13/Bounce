/*
 * EnemyPaddle.cpp
 *
 *  Created on: Sep 17, 2013
 *      Author: daniel
 */

#include "EnemyPaddle.h"



//EnemyPaddle* EnemyPaddle::enemyPaddle = NULL;





EnemyPaddle::EnemyPaddle():Paddle() {
<<<<<<< HEAD
	//paddleBodyDef.userData = enemyPaddle;
=======
	paddleBodyDef.userData = enemyPaddle;
>>>>>>> hst
	//velocity = 100;

}

EnemyPaddle::~EnemyPaddle() {
	// TODO Auto-generated destructor stub
}

EnemyPaddle* EnemyPaddle::getEnemyPaddle(){
	//  if(enemyPaddle != NULL)
	//  {
	// // 	//enemyPaddle->initWithFile("enemyPaddle.png");
	// // 	//CCLOG("123123");
	// // 	CCTexture2D * image = CCTextureCache::sharedTextureCache()->addImage("enemyPaddle.png");
	// // 	enemyPaddle->setTexture(image);
	// // 	CCLOG("set image");
	// // 	return enemyPaddle;
	 
	// }
	//  // else

<<<<<<< HEAD
		EnemyPaddle * enemyPaddle =new EnemyPaddle();
		if(enemyPaddle && enemyPaddle->initWithFile("enemyPaddle.png")){
=======
		enemyPaddle =new EnemyPaddle();
		if(enemyPaddle && enemyPaddle->initWithFile("GameLayer/enemyPaddle.png")){
>>>>>>> hst
				enemyPaddle->myInit();
				enemyPaddle->autorelease();
				return enemyPaddle;
		}
		CC_SAFE_DELETE(enemyPaddle);
		return NULL;
	// }
}

void EnemyPaddle::myInit(){
    // this->setScaleX(ENEMY_PADDLE_SCALE_X);
    // this->setScaleY(ENEMY_PADDLE_SCALE_Y);
}


float EnemyPaddle::getWidth(){
    return this->getTextureRect().getMaxX();
}

float EnemyPaddle::getHeight(){
    return this->getTextureRect().getMaxY();
}

b2Body* EnemyPaddle::getEnemyPaddleBody(){
	return enemyPaddleBody;

}
void EnemyPaddle::setEnemyPaddleBody(b2Body* enemyPaddleBody){
	this->enemyPaddleBody = enemyPaddleBody;

}

<<<<<<< HEAD
void EnemyPaddle::move(Ball *ball, Ball *extraBall){
	CCPoint ballPosition;
	if(extraBall != NULL){
		if(extraBall->getPriority() > ball->getPriority()){
			ballPosition = extraBall->getPosition();

		}
		else{
			ballPosition = ball->getPosition();
		}
	}
	else{
		 ballPosition = ball->getPosition();
	}
	

	int possibility = rand()%100;

	b2Vec2 v;
	if(ballPosition.x+ball->getWidth()/2 < this->getPosition().x){
		
		if(possibility < 2){
			 v = b2Vec2(0,0);
		}
		else if(possibility > 50){
			 v = b2Vec2(-1000,0);
		}
		else{
			 v = b2Vec2(-3000,0);
		}
		
    	enemyPaddleBody->ApplyForceToCenter(v);
	}
	else if(ballPosition.x+ball->getWidth()/2 > this->getPosition().x){
				if(possibility < 2){
			 v = b2Vec2(0,0);
		}
		else if(possibility > 80){
			 v = b2Vec2(1000,0);
		}
		else{
			 v = b2Vec2(3000,0);
		}
    	enemyPaddleBody->ApplyForceToCenter(v);
	}

	// else{
	// 	 v = b2Vec2(0,0);
 //    	enemyPaddleBody->SetLinearVelocity(v);
	// }
	//this->setPosition(ccp(ballPosition.x,this->getPosition().y));
=======
void EnemyPaddle::move(Ball *ball){
	CCPoint ballPosition = ball->getPosition();

	int possibility = rand()%100;
>>>>>>> hst

	b2Vec2 v;
	if(ballPosition.x+ball->getWidth()/2 < this->getPosition().x){
		
		if(possibility < 2){
			 v = b2Vec2(0,0);
		}
		else if(possibility > 50){
			 v = b2Vec2(-1000,0);
		}
		else{
			 v = b2Vec2(-2000,0);
		}
		
    	enemyPaddleBody->ApplyForceToCenter(v);
	}
	else if(ballPosition.x+ball->getWidth()/2 > this->getPosition().x){
				if(possibility < 2){
			 v = b2Vec2(0,0);
		}
		else if(possibility > 80){
			 v = b2Vec2(1000,0);
		}
		else{
			 v = b2Vec2(2000,0);
		}
    	enemyPaddleBody->ApplyForceToCenter(v);
	}
	// else{
	// 	 v = b2Vec2(0,0);
 //    	enemyPaddleBody->SetLinearVelocity(v);
	// }
	//this->setPosition(ccp(ballPosition.x,this->getPosition().y));
}
