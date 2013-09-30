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

bool ScoreLayer::init()
{
	if (!CCLayer::init())
		return false;
	setKeypadEnabled(true);
	setTouchEnabled(true);
	setTouchPriority(kCCMenuHandlerPriority + 1);
	setTouchMode(kCCTouchesOneByOne);

	this->initBackground();
	this->initBackButton();
	this->initHighScore();
	return true;
}



void ScoreLayer::initBackground()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite* settingLayerBackground = CCSprite::create("ScoreLayer/ScoreSceneBackground.png");
	settingLayerBackground->setPosition(ccp(size.width/2, size.height/2));
	this->addChild(settingLayerBackground, 0);
}



void ScoreLayer::initBackButton()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();




    //Pause Button
    CCMenuItemImage *backButtonImage = CCMenuItemImage::create(
                                                          "ScoreLayer/Back.png",
                                                          "ScoreLayer/Back_Pressed.png",
                                                          this,
                                                          menu_selector(ScoreLayer::backButtonPressed));
    backButtonImage -> setPosition( ccp(0, 0) );
    CCMenu* backButton = CCMenu::create(backButtonImage, NULL);
    backButton -> setPosition( ccp(size.width / 2, size.height - 1019) );
    this -> addChild(backButton, 3);
}


void ScoreLayer::keyBackClicked()
{

	CCDirector::sharedDirector()->popSceneWithTransition<CCTransitionSlideInB>(0.3);

}

void ScoreLayer::backButtonPressed()
{
	CCDirector::sharedDirector()->popSceneWithTransition<CCTransitionSlideInB>(0.3);

}

void ScoreLayer::initHighScore(){
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	highScoreLabel = CCLabelTTF::create("High Score:", "Designer-Notes.ttf", 150);


	char temp[10];
	sprintf(temp,"%d",ScoreData::highScore);
	highScore =  CCLabelTTF::create(temp, "Designer-Notes.ttf", 150);

	highScoreLabel->setPosition(ccp(size.width/2, size.height/2+100));
    this->addChild(highScoreLabel, 3);

    highScore->setPosition(ccp(size.width/2, size.height/2-100));
	this->addChild(highScore, 3);

}
