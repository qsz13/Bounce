/*
 * SettingLayer.cpp
 *
 *  Created on: Sep 22, 2013
 *      Author: daniel
 */

#include "SettingLayer.h"
using namespace cocos2d;


SettingLayer::ControlType SettingLayer::controlMode = GRAVITY;
int SettingLayer::sensitivity = 100;

SettingLayer::SettingLayer() {
	// TODO Auto-generated constructor stub

}

SettingLayer::~SettingLayer() {
	// TODO Auto-generated destructor stub
}


CCScene* SettingLayer::scene()
{
    CCScene *scene = CCScene::create();
    SettingLayer* layer = SettingLayer::create();
    scene->addChild(layer);
    return scene;
}

void SettingLayer::initBackground()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//Background
	// 创建图片精灵
	CCSprite* settingLayerBackground = CCSprite::create("SettingLayer/SettingSceneBackground.png");

	// 设置图片精灵的位置
	settingLayerBackground->setPosition(ccp(size.width/2, size.height/2));

	// 把图片精灵放置在图层中
	this->addChild(settingLayerBackground, 0);
}

bool SettingLayer::init()
{
	if (!CCLayer::init())
		return false;
	setKeypadEnabled(true);
	setTouchEnabled(true);
	setTouchPriority(kCCMenuHandlerPriority + 1);
	setTouchMode(kCCTouchesOneByOne);

	this->initBackground();
	// this->initControlMode();
	this->initBackButton();

	return true;
}

void SettingLayer::initBackButton()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

    //Pause Button
    CCMenuItemImage *backButtonImage = CCMenuItemImage::create(
                                                          "SettingLayer/Back.png",
                                                          "SettingLayer/Back_Pressed.png",
                                                          this,
                                                          menu_selector(SettingLayer::backButtonPressed));
    backButtonImage -> setPosition( ccp(0, 0) );
    //CCLOG("%f",backButtonImage->getContentSize().height);
    CCMenu* backButton = CCMenu::create(backButtonImage, NULL);
    backButton -> setPosition( ccp(size.width / 2, size.height - 1019) );
    this -> addChild(backButton, 3);
}

void SettingLayer::initControlMode()
{

}
void SettingLayer::initGravitySeneitivity()
{

}

void SettingLayer::backButtonPressed()
{
	CCDirector::sharedDirector()->popSceneWithTransition<CCTransitionSlideInR>(0.5);
}


int SettingLayer::getSensitivity(){
	return sensitivity;

}
void SettingLayer::setSensitivity(int s){
	sensitivity = s;
}



int SettingLayer::getControlMode(){
	return controlMode;
}


void SettingLayer::setControlMode(SettingLayer::ControlType mode){
	controlMode = mode;
}

void SettingLayer::keyBackClicked(){

	CCDirector::sharedDirector()->popSceneWithTransition<CCTransitionSlideInR>(0.5);
}
