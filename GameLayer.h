/*
 * GameLayer.h
 *
 *  Created on: Sep 17, 2013
 *      Author: daniel
 */

#ifndef GAMELAYER_H_
#define GAMELAYER_H_

#define MAX_ITEM 3
#include "cocos2d.h"
#include "Box2D.h"
#include "MyPaddle.h"
#include "EnemyPaddle.h"
#include "Ball.h"
#include "SettingLayer.h"
#include "PauseLayer.h"
#include "ScoreData.h"
#include "EnlargeItem.h"
#include "BallContactListener.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "ReverseXItem.h"
#include "ReverseYItem.h"
#include "DoubleItem.h"
#include "Item.h"
#include "FreezeItem.h"
#include "ShortenItem.h"
#include "StealthItem.h"
#include "SkewingItem.h"
#include <list>
#define PTM_RATIO 32.0
using namespace cocos2d;

class GameLayer: public CCLayer {
public:


	virtual bool init();
	static CCScene* scene();
	CREATE_FUNC (GameLayer);
	static GameLayer *getLayer();


	void doStep(float delta);

	CCSize winSize;

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	void restartConfirm();
	void didAccelerate(CCAcceleration* pAccelerationValue);

	void restart();
	void itemIntersects();
	void dropItem();
	Ball* getBall();
	Ball* getGhostBall();
	MyPaddle* getMyPaddle();
	EnemyPaddle* getEnemyPaddle();


private:
	static GameLayer *layer;
	static Ball *ball;
	static Ball *ghostBall;
	static MyPaddle *myPaddle;
	static EnemyPaddle* enemyPaddle;

	b2World *world;
	b2Body *groundBody;
	b2Fixture *bottomFixture;
	b2Fixture *ballFixture;
	b2Fixture *myPaddleFixture;
	b2Fixture *enemyPaddleFixture;
	b2MouseJoint *_mouseJoint;
	CCLabelTTF *scores;

	void onEnterTransitionDidFinish();
	void keyBackClicked();


	void initBackground();
	void initTopBar();
	void pause();
	void resume();
	bool gameIsPaused;
	bool gameIsEnded;
	bool gameIsOver;
	bool newGame;
	bool isSkweing;
	bool freezeMode;
	bool skewDirectionIsRight;
	Item* item;
	list<Item *> itemList;
	void enlargePaddle(Ball *ball);
	void paddleTimer();
	void avoidUnwantedSituation();
	void reverseBallXVelocity();
	void reverseBallYVelocity();
	void doubleBall();
	void ghostBallTimer();
	void freezeBall();
	void freezeTimer();
	void shortenPaddle(Ball *ball);
	void stealthBall();
	void skewBall();
	void skewTimer();
	b2Vec2 velocityBeforeFrozen;

	void buildBall();
	void buildMyPaddle();
	void buildEnemyPaddle();
	void buildGround();
	void restrictPaddleMovement();
	void countDown();
	void setHighScore();

};

#endif /* GAMELAYER_H_ */
