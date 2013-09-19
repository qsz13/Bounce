/*
 * MyPaddle.h
 *
 *  Created on: Sep 17, 2013
 *      Author: daniel
 */

#ifndef MYPADDLE_H_
#define MYPADDLE_H_
#include "cocos2d.h"
#include "Paddle.h"
using namespace cocos2d;


class MyPaddle : public Paddle {
public:


	static MyPaddle* getMyPaddle();

	void myInit();

	void Drag(CCPoint offSet);
	//touch
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
protected:
	static MyPaddle *myPaddle;
	MyPaddle();
	virtual ~MyPaddle();
};

#endif /* MYPADDLE_H_ */
