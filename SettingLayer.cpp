/*
 * SettingLayer.cpp
 *
 *  Created on: Sep 22, 2013
 *      Author: daniel
 */

#include "SettingLayer.h"
using namespace cocos2d;


SettingLayer::ControlType SettingLayer::controlMode = TOUCH;
int SettingLayer::sensitivity = 250;

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

	setTouchEnabled(true);
	setTouchPriority(kCCMenuHandlerPriority + 1);
	setTouchMode(kCCTouchesOneByOne);

	this->initBackground();
	//this->initMenu();

	return true;
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

