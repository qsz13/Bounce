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
	CCSprite* settingLayerBackground = CCSprite::create("ScoreLayer/ScoreSceneBackground.png");
	settingLayerBackground->setPosition(ccp(size.width/2, size.height/2));
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

	return true;
}

void ScoreLayer::keyBackClicked()
{

	CCDirector::sharedDirector()->popSceneWithTransition<CCTransitionSlideInR>(0.5);

}
