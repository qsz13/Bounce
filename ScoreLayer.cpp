/*
 * ScoreLayer.cpp
 *
 *  Created on: Sep 28, 2013
 *      Author: daniel
 */

#include "ScoreLayer.h"

ScoreLayer::ScoreLayer() {
	// TODO Auto-generated constructor stub

}

ScoreLayer::~ScoreLayer() {
	// TODO Auto-generated destructor stub
}

CCScene* ScoreLayer::scene()
{
    CCScene *scene = CCScene::create();
    ScoreLayer* layer = ScoreLayer::create();
    scene->addChild(layer);
    return scene;
}


void ScoreLayer::initBackground()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//Background
	// 创建图片精灵
	CCSprite* settingLayerBackground = CCSprite::create("ScoreLayer/ScoreSceneBackground.png");

	// 设置图片精灵的位置
	settingLayerBackground->setPosition(ccp(size.width/2, size.height/2));

	// 把图片精灵放置在图层中
	this->addChild(settingLayerBackground, 0);
}

bool ScoreLayer::init()
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

void ScoreLayer::keyBackClicked()
{

	CCDirector::sharedDirector()->popSceneWithTransition<CCTransitionSlideInR>(0.5);

}
