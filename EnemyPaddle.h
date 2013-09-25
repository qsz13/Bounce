/*
 * EnemyPaddle.h
 *
 *  Created on: Sep 17, 2013
 *      Author: daniel
 */

#ifndef ENEMYPADDLE_H_
#define ENEMYPADDLE_H_

#include "cocos2d.h"
#include "Paddle.h"
#include "Ball.h"
// #define ENEMY_PADDLE_SCALE_X 0.3
// #define ENEMY_PADDLE_SCALE_Y 0.5
using namespace cocos2d;

class EnemyPaddle :public Paddle{
public:

	static EnemyPaddle* getEnemyPaddle();
	void myInit();
	float getWidth();
	float getHeight();

    b2Body* getEnemyPaddleBody();
    void setEnemyPaddleBody(b2Body* enemyPaddleBody);
    void move(Ball *ball);
private:
    static EnemyPaddle* enemyPaddle;
    EnemyPaddle();
	virtual ~EnemyPaddle();
	b2Body *enemyPaddleBody;
	//float velocity;


};

#endif /* ENEMYPADDLE_H_ */
