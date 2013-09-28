/*
 * PauseLayer.cpp
 *
 *  Created on: Sep 28, 2013
 *      Author: daniel
 */

#include "PauseLayer.h"

PauseLayer::PauseLayer() {
	// TODO Auto-generated constructor stub

}

PauseLayer::~PauseLayer() {
	// TODO Auto-generated destructor stub
}

CCScene* PauseLayer::scene()
{
    CCScene *scene = CCScene::create();
    PauseLayer* layer = PauseLayer::create();
    scene->addChild(layer);
    return scene;
}


void PauseLayer::initBackground()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//Background
	// 创建图片精灵
	CCSprite* settingLayerBackground = CCSprite::create("PauseLayer/PauseSceneBackground.png");

	// 设置图片精灵的位置
	settingLayerBackground->setPosition(ccp(size.width/2, size.height/2));

	// 把图片精灵放置在图层中
	this->addChild(settingLayerBackground, 0);
}

bool PauseLayer::init()
{
	if (!CCLayer::init())
		return false;
	setKeypadEnabled(true);
	setTouchEnabled(true);
	setTouchPriority(kCCMenuHandlerPriority + 1);
	setTouchMode(kCCTouchesOneByOne);

	this->initBackground();
	//this->initMenu();

	return true;
}

void PauseLayer::keyBackClicked()
{

	CCDirector::sharedDirector()->popScene();

}
