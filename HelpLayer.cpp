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
	this->initBackButton();

	return true;
}

void HelpLayer::keyBackClicked()
{

	CCDirector::sharedDirector()->popSceneWithTransition<CCTransitionSlideInT>(0.3);

}

void HelpLayer::initBackButton()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

    //Pause Button
    CCMenuItemImage *backButtonImage = CCMenuItemImage::create(
                                                          "HelpLayer/Back.png",
                                                          "HelpLayer/Back_Pressed.png",
                                                          this,
                                                          menu_selector(HelpLayer::backButtonPressed));
    backButtonImage -> setPosition( ccp(0, 0) );
    CCMenu* backButton = CCMenu::create(backButtonImage, NULL);
    backButton -> setPosition( ccp(size.width / 2, size.height - 1019) );
    this -> addChild(backButton, 3);
}

void HelpLayer::backButtonPressed()
{

	CCDirector::sharedDirector()->popSceneWithTransition<CCTransitionSlideInT>(0.3);

}