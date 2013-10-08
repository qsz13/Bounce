/*
 * EnemyPaddle.cpp
 *
 *  Created on: Sep 17, 2013
 *      Author: daniel
 */

#include "EnemyPaddle.h"

EnemyPaddle::EnemyPaddle() :
		Paddle() {

}

EnemyPaddle::~EnemyPaddle() {

}

EnemyPaddle* EnemyPaddle::createEnemyPaddle() {

	EnemyPaddle *enemyPaddle = new EnemyPaddle();
	if (enemyPaddle && enemyPaddle->initWithFile("GameLayer/enemyPaddle.png")) {
		enemyPaddle->autorelease();
		return enemyPaddle;
	}
	CC_SAFE_DELETE(enemyPaddle);
	return NULL;
}

void EnemyPaddle::myInit() {

}

float EnemyPaddle::getWidth() {
	return this->getTextureRect().getMaxX();
}

float EnemyPaddle::getHeight() {
	return this->getTextureRect().getMaxY();
}

b2Body* EnemyPaddle::getEnemyPaddleBody() {
	return enemyPaddleBody;

}
void EnemyPaddle::setEnemyPaddleBody(b2Body* enemyPaddleBody) {
	this->enemyPaddleBody = enemyPaddleBody;

}

void EnemyPaddle::move(Ball *ball, Ball *extraBall) {
	CCPoint ballPosition;
	if (extraBall != NULL) {
		if (extraBall->getPriority() > ball->getPriority()) {
			ballPosition = extraBall->getPosition();

		} else {
			ballPosition = ball->getPosition();
		}
	} else {
		ballPosition = ball->getPosition();
	}

	int possibility = rand() % 100;

	b2Vec2 v;
	if (ballPosition.x + ball->getWidth() / 2 < this->getPosition().x) {

		v = b2Vec2(-2000, 0);

		enemyPaddleBody->ApplyForceToCenter(v);
	} else if (ballPosition.x + ball->getWidth() / 2 > this->getPosition().x) {

		v = b2Vec2(2000, 0);

		enemyPaddleBody->ApplyForceToCenter(v);
	}
}
