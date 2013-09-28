/*
 * HelpLayer.cpp
 *
 *  Created on: Sep 28, 2013
 *      Author: daniel
 */

#include "HelpLayer.h"

HelpLayer::HelpLayer() {
	// TODO Auto-generated constructor stub

}

HelpLayer::~HelpLayer() {
	// TODO Auto-generated destructor stub
}


CCScene* HelpLayer::scene()
{
    CCScene *scene = CCScene::create();
    HelpLayer* layer = HelpLayer::create();
    scene->addChild(layer);
    return scene;
}


void HelpLayer::initBackground()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite* settingLayerBackground = CCSprite::create("HelpLayer/HelpSceneBackground.png");
	settingLayerBackground->setPosition(ccp(size.width/2, size.height/2));
	this->addChild(settingLayerBackground, 0);
}

bool HelpLayer::init()
{
	if (!CCLayer::init())
		return false;
	setKeypadEnabled(true);
	setTouchEnabled(true);
	setTouchPriority(kCCMenuHandlerPriority + 1);
	setTouchMode(kCCTouchesOneByOne);

	this->initBackground();

	return true;
}

void HelpLayer::keyBackClicked()
{

	CCDirector::sharedDirector()->popSceneWithTransition<CCTransitionSlideInR>(0.5);

}
