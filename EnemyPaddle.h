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
#define ENEMY_PADDLE_SCALE 0.5
using namespace cocos2d;

class EnemyPaddle :public Paddle{
public:

	static EnemyPaddle* getEnemyPaddle();
	void myInit();
	float getWidth();
	float getHeight();

    b2Body* getEnemyPaddleBody();
    void setEnemyPaddleBody(b2Body* enemyPaddleBody);

private:
    static EnemyPaddle* enemyPaddle;
    EnemyPaddle();
	virtual ~EnemyPaddle();
	b2Body *enemyPaddleBody;
};

#endif /* ENEMYPADDLE_H_ */
