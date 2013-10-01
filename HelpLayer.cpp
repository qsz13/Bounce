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
	winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* settingLayerBackground = CCSprite::create("HelpLayer/HelpSceneBackground.png");
	settingLayerBackground->setPosition(ccp(winSize.width/2, winSize.height/2));
	this->addChild(settingLayerBackground, 0);
}

bool HelpLayer::init()
{
	if (!CCLayer::init())
		return false;
	setKeypadEnabled(true);
	setTouchEnabled(true);
//	setTouchPriority(kCCMenuHandlerPriority + 1);
//	setTouchMode(kCCTouchesOneByOne);

	this->initBackground();
	this->initBackButton();
	this->initScroll();
	return true;
}

void HelpLayer::keyBackClicked()
{

	CCDirector::sharedDirector()->popSceneWithTransition<CCTransitionSlideInT>(0.3);

}

void HelpLayer::initBackButton()
{

	 //Pause Button
	    CCMenuItemImage *backButtonImage = CCMenuItemImage::create(
	                                                          "HelpLayer/Back.png",
	                                                          "HelpLayer/Back_Pressed.png",
	                                                          this,
	                                                          menu_selector(HelpLayer::backButtonPressed));
	    backButtonImage -> setPosition( ccp(0, 0) );
	    CCMenu* backButton = CCMenu::create(backButtonImage, NULL);
	    backButton -> setPosition( ccp(winSize.width / 2, winSize.height - 1019) );
	    this -> addChild(backButton, 3);


}

void HelpLayer::backButtonPressed()
{

	CCDirector::sharedDirector()->popSceneWithTransition<CCTransitionSlideInT>(0.3);

}



void HelpLayer::initScroll(){

	 CCSize _size = CCDirector::sharedDirector()->getWinSize();
	 CCLayerColor* layer= CCLayerColor::create((ccColor4B){100,100,100,100});
	 layer->setContentSize(CCSizeMake(1500,winSize.height/2));
	 layer->setPosition(ccp(0,winSize.height/2));
	ScrollLayer* scroll=ScrollLayer::create();
//	scroll->setClippingToBounds(true);
//	scroll->setDirection(kCCScrollViewDirectionHorizontal);
	//scroll->setPosition(ccp((910+315)/2, winSize.width/2));
	layer->addChild(scroll,1);
	this->addChild(layer);



   
}



