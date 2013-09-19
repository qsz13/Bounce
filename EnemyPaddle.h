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
using namespace cocos2d;

class EnemyPaddle :public Paddle{
public:

	static EnemyPaddle* getEnemyPaddle();
	void myInit();
private:
    static EnemyPaddle* enemyPaddle;
    EnemyPaddle();
	virtual ~EnemyPaddle();
};

#endif /* ENEMYPADDLE_H_ */
