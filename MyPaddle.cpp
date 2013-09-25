/*
 * MyPaddle.cpp
 *
 *  Created on: Sep 17, 2013
 *      Author: daniel
 */

#include "MyPaddle.h"
<<<<<<< HEAD
//MyPaddle* MyPaddle::myPaddle = NULL;
=======
MyPaddle* MyPaddle::myPaddle = NULL;
>>>>>>> hst
MyPaddle::MyPaddle():Paddle()
{
   // paddleBodyDef.userData = myPaddle;

}

MyPaddle::~MyPaddle()
{
	// TODO Auto-generated destructor stub
}

MyPaddle* MyPaddle::getMyPaddle(){
	 // if(myPaddle != NULL)
	// {
	// 	CCTexture2D * image = CCTextureCache::sharedTextureCache()->addImage("myPaddle.png");
	// 	myPaddle->setTexture(image);
		
	// 			// CCLOG("123123");
	// 	return myPaddle;
	// }
	// else
	 // {
<<<<<<< HEAD
		MyPaddle* myPaddle =new MyPaddle();
		if(myPaddle && myPaddle->initWithFile("myPaddle.png")){
=======
		myPaddle =new MyPaddle();
		if(myPaddle && myPaddle->initWithFile("GameLayer/myPaddle.png")){
>>>>>>> hst
				myPaddle->myInit();
				myPaddle->autorelease();
				return myPaddle;
		}
		CC_SAFE_DELETE(myPaddle);
		return NULL;
	// }



}


void MyPaddle::myInit(){
// 	this->setScaleX(MY_PADDLE_SCALE_X);
// 	this->setScaleY(MY_PADDLE_SCALE_Y);
//
	}


float MyPaddle::getWidth(){
    return this->getTextureRect().getMaxX();
}

float MyPaddle::getHeight(){
    return this->getTextureRect().getMaxY();
}


b2Body* MyPaddle::getMyPaddleBody(){
	return myPaddleBody;
}

void MyPaddle::setMyPaddleBody(b2Body* myPaddleBody){
	this->myPaddleBody = myPaddleBody;
}




//
//void MyPaddle::onEnter()
//{
//    CCDirector* pDirector = CCDirector::sharedDirector();
//    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
//    CCSprite::onEnter();
//}
//
//void MyPaddle::onExit()
//{
//    CCDirector* pDirector = CCDirector::sharedDirector();
//    pDirector->getTouchDispatcher()->removeDelegate(this);
//    CCSprite::onExit();
//}
//
//bool MyPaddle::ccTouchBegan(CCTouch* touch, CCEvent* event)
//{
//    CCPoint sLocalPos = convertToNodeSpace(touch->getLocation());
//    CCRect sRC = CCRect(getPositionX() - getContentSize().width * getAnchorPoint().x,
//                           getPositionY() - getContentSize().height * getAnchorPoint().y,
//                           getContentSize().width, getContentSize().height);
//
//
//    sRC.origin = CCPointZero;
//    bool isTouched = sRC.containsPoint(sLocalPos);
//    if(isTouched)
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}
//
//void MyPaddle::ccTouchMoved(CCTouch* touch, CCEvent* event)
//{
//
//
//	 CCPoint beginLoc = touch->getLocation();
//
//	 CCPoint endLoc = touch->getPreviousLocation();
//	 CCPoint offSet = ccpSub(beginLoc, endLoc);
//	 offSet.y = 0;
//	 Drag(offSet);
//
//}
//
//void MyPaddle::Drag(CCPoint offSet)
//{
//    //���������������������������������������������������������������
//    CCPoint pos = ccpAdd(this->getPosition(), offSet);
//    this->setPosition(pos);
//
//
//
//}
//
//void MyPaddle::ccTouchEnded(CCTouch* touch, CCEvent* event){
//
//}


