/*
 * GameLayer.h
 *
 *  Created on: Sep 17, 2013
 *      Author: daniel
 */

#ifndef GAMELAYER_H_
#define GAMELAYER_H_

#include "cocos2d.h"
#include "Box2D.h"
#include "MyPaddle.h"
#include "EnemyPaddle.h"
#include "Ball.h"
#define PTM_RATIO 32.0
using namespace cocos2d;

class GameLayer : public CCLayer {
public:
	virtual bool init();
	static CCScene* scene();
	void menuCloseCallback(CCObject* pSender);


    CREATE_FUNC(GameLayer);
    void doStep(float delta);
    b2World *world;
    Ball *ball;
    MyPaddle *myPaddle;
    EnemyPaddle *enemyPaddle;
};

#endif /* GAMELAYER_H_ */
