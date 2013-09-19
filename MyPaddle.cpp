/*
 * MyPaddle.cpp
 *
 *  Created on: Sep 17, 2013
 *      Author: daniel
 */

#include "MyPaddle.h"
MyPaddle* MyPaddle::myPaddle = NULL;

MyPaddle::MyPaddle():Paddle()
{
    paddleBodyDef.userData = myPaddle;

}

MyPaddle::~MyPaddle()
{
	// TODO Auto-generated destructor stub
}

MyPaddle* MyPaddle::getMyPaddle(){
	if(myPaddle != NULL)
	{
		return myPaddle;
	}
	else
	{
		myPaddle =new MyPaddle();
		if(myPaddle && myPaddle->initWithFile("paddle.png")){
				myPaddle->myInit();
				myPaddle->autorelease();
				return myPaddle;
		}
		CC_SAFE_DELETE(myPaddle);
		return NULL;
	}



}

void MyPaddle::myInit(){
	this->setScale(0.5);
}


void MyPaddle::onEnter()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
    CCSprite::onEnter();
}

void MyPaddle::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}

bool MyPaddle::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    CCPoint sLocalPos = convertToNodeSpace(touch->getLocation());
    CCRect sRC = CCRect(getPositionX() - getContentSize().width * getAnchorPoint().x,
                           getPositionY() - getContentSize().height * getAnchorPoint().y,
                           getContentSize().width, getContentSize().height);


    sRC.origin = CCPointZero;
    bool isTouched = sRC.containsPoint(sLocalPos);
    if(isTouched)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void MyPaddle::ccTouchMoved(CCTouch* touch, CCEvent* event)
{


	 CCPoint beginLoc = touch->getLocation();

	 CCPoint endLoc = touch->getPreviousLocation();
	 CCPoint offSet = ccpSub(beginLoc, endLoc);
	 offSet.y = 0;
	 Drag(offSet);

}

void MyPaddle::Drag(CCPoint offSet)
{
    //计算精灵坐标加上移动偏移量、并设置精灵位置
    CCPoint pos = ccpAdd(this->getPosition(), offSet);
    this->setPosition(pos);



}

void MyPaddle::ccTouchEnded(CCTouch* touch, CCEvent* event){

}



