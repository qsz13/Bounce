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
#include "SettingLayer.h"
#define PTM_RATIO 32.0
using namespace cocos2d;

class GameLayer : public CCLayer {
public:
	virtual bool init();
	static CCScene* scene();
	//void menuCloseCallback(CCObject* pSender);


    CREATE_FUNC(GameLayer);
    void doStep(float delta);

    CCSize winSize;

    b2World *world;
    b2Body *groundBody;
    b2Fixture *bottomFixture;
	b2Fixture *ballFixture;
    
    Ball *ball;
    MyPaddle *myPaddle;
    EnemyPaddle *enemyPaddle;
    
    // b2Body *myPaddleBody;
    // b2Body *enemyPaddleBody;

    b2Fixture *myPaddleFixture;
    b2Fixture *enemyPaddleFixture;

    b2MouseJoint *_mouseJoint; 
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    // bool MouseDown(const b2Vec2& p);
    // void MouseMove(const b2Vec2& p);
    // void MouseUp(const b2Vec2& p);
    void restart();
    



private:
    bool gameIsPaused;
    bool gameIsEnded;

};

#endif /* GAMELAYER_H_ */