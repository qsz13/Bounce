/*
 * ScrollLayer.cpp
 *
 *  Created on: Sep 29, 2013
 *      Author: daniel
 */

#include "ScrollLayer.h"

using namespace cocos2d;
using namespace cocos2d::extension;

ScrollLayer::ScrollLayer() {
	// TODO Auto-generated constructor stub

}

ScrollLayer::~ScrollLayer() {
	// TODO Auto-generated destructor stub
}

bool ScrollLayer::init() {
	if (!CCLayer::init()) {
		return false;
	}

	m_nCurPage = 1;
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCLayer *pLayer = CCLayer::create();
	char helpstr[30] = { 0 };
	for (int i = 1; i <= 7; ++i) {
		memset(helpstr, 0, sizeof(helpstr));
		sprintf(helpstr, "HelpLayer/HelpLayer-%d.png", i);
		CCSprite *pSprite = CCSprite::create(helpstr);
		pSprite->setPosition(
				ccp(visibleSize.width * (i - 0.5f), (910 - 315) / 2));

		pLayer->addChild(pSprite);
	}

	m_pScrollView = CCScrollView::create(CCSizeMake(720, 910 - 315), pLayer);
	m_pScrollView->setContentOffset(CCPointZero);
	m_pScrollView->setTouchEnabled(false);
	m_pScrollView->setDelegate(this);
	m_pScrollView->setDirection(kCCScrollViewDirectionHorizontal);
	pLayer->setContentSize(CCSizeMake(720 * 7, 910 - 315));

	this->addChild(m_pScrollView);
	return true;

}

//scrollview滚动的时候会调用
void ScrollLayer::scrollViewDidScroll(CCScrollView* view) {

}

//scrollview缩放的时候会调用
void ScrollLayer::scrollViewDidZoom(CCScrollView* view) {

}

void ScrollLayer::onEnter() {
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
			this, 1, false);
}

void ScrollLayer::onExit() {
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

bool ScrollLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
	CCLog("touch begin");
	m_touchPoint = CCDirector::sharedDirector()->convertToGL(
			pTouch->getLocationInView());
	return true;
}

void ScrollLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {

}

void ScrollLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
	CCPoint endPoint = CCDirector::sharedDirector()->convertToGL(
			pTouch->getLocationInView());
	float distance = endPoint.x - m_touchPoint.x;
	if (fabs(distance) > 50) {
		adjustScrollView(distance);
	}
}

void ScrollLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch,
		cocos2d::CCEvent *pEvent) {
	CCPoint endPoint = CCDirector::sharedDirector()->convertToGL(
			pTouch->getLocationInView());
	float distance = endPoint.x - m_touchPoint.x;
	if (fabs(distance) > 50) {
		adjustScrollView(distance);
	}
}

void ScrollLayer::adjustScrollView(float offset) {
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCPoint delta;
	if (offset < 0) {
		m_nCurPage++;
		delta = ccp(45, 0);
	} else {
		m_nCurPage--;
		delta = ccp(-45, 0);
	}

	if (m_nCurPage < 1) {
		m_nCurPage = 1;
	} else if (m_nCurPage > 7) {
		m_nCurPage = 7;
	} else {
		CCActionInterval* move = CCMoveBy::create(0.5, delta);
		CCActionInterval* move_ease_out = CCEaseElasticOut::create(
				(CCActionInterval*) (move->copy()->autorelease()));
		HelpLayer::movingDot->runAction(
				CCSequence::create(move_ease_out, NULL));

		CCPoint adjustPos = ccp(origin.x - visibleSize.width * (m_nCurPage - 1),
				0);
		m_pScrollView->setContentOffset(adjustPos, true);

	}
}
