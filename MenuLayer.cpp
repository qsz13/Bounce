/*
 * MenuLayer.cpp
 *
 *  Created on: 2013-9-17
 *      Author: tomhu
 */

#include "MenuLayer.h"

using namespace cocos2d;

void MenuLayer::initBackground()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//Background
	// 创建图片精灵
	CCSprite* menuLayerBackground = CCSprite::create("MenuLayer/Background.png");

	// 设置图片精灵的位置
	menuLayerBackground->setPosition(ccp(size.width/2, size.height/2));

	// 把图片精灵放置在图层中
	this->addChild(menuLayerBackground, 0);
}

void MenuLayer::initMenu()
{
	//Get windows size
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//Start
	CCMenuItemImage *pStartItem = CCMenuItemImage::create(
														  "MenuLayer/Start.png",
														  "MenuLayer/Start_Pressed.png",
														  this,
														  menu_selector(MenuLayer::menuStart));
	pStartItem -> setPosition( ccp(0, 0) );

	CCMenu* pMenusStart = CCMenu::create(pStartItem, NULL);
	pMenusStart -> setPosition( ccp(size.width / 2, size.height / 2 - 171) );
	this -> addChild(pMenusStart, 1);

	//Setting
	CCMenuItemImage *pSettingItem = CCMenuItemImage::create(
<<<<<<< HEAD
														  "Setting.png",
														  "Setting_Pressed.png",
=======
														  "MenuLayer/Setting.png",
														  "MenuLayer/Setting_Pressed.png",
>>>>>>> hst
														  this,
														  menu_selector(MenuLayer::menuSetting));
	pSettingItem -> setPosition( ccp(0, 0) );

	CCMenu* pMenusSetting = CCMenu::create(pSettingItem, NULL);
	pMenusSetting -> setPosition( ccp(size.width / 2, size.height / 2 - 171 - 100) );
	this -> addChild(pMenusSetting, 1);

	//Help
	CCMenuItemImage *pHelpItem = CCMenuItemImage::create(
														  "MenuLayer/Help.png",
														  "MenuLayer/Help_Pressed.png",
														  this,
														  menu_selector(MenuLayer::menuHelp));
	pHelpItem -> setPosition( ccp(0, 0) );

	CCMenu* pMenusHelp = CCMenu::create(pHelpItem, NULL);
	pMenusHelp -> setPosition( ccp(size.width / 2, size.height / 2 - 171 - 100 - 80) );
	this -> addChild(pMenusHelp, 1);

	//Scores
	CCMenuItemImage *pScoresItem = CCMenuItemImage::create(
<<<<<<< HEAD
														  "Scores.png",
														  "Scores_Pressed.png",
=======
														  "MenuLayer/Scores.png",
														  "MenuLayer/Scores_Pressed.png",
>>>>>>> hst
														  this,
														  menu_selector(MenuLayer::menuScores));
	pScoresItem -> setPosition( ccp(0, 0) );

	CCMenu* pScoresHelp = CCMenu::create(pScoresItem, NULL);
	pScoresHelp -> setPosition( ccp(size.width / 2, size.height / 2 - 171 - 100 - 80 * 2) );
	this -> addChild(pScoresHelp, 1);

	//Quit
	CCMenuItemImage *pQuitItem = CCMenuItemImage::create(
														  "MenuLayer/Quit.png",
														  "MenuLayer/Quit_Pressed.png",
														  this,
														  menu_selector(MenuLayer::menuCloseCallback));
	pQuitItem -> setPosition( ccp(0, 0) );

	CCMenu* pMenusQuit = CCMenu::create(pQuitItem, NULL);
	pMenusQuit -> setPosition( ccp(size.width / 2, size.height / 2 - 171 - 100 - 80 * 3) );
	this -> addChild(pMenusQuit, 1);


	CCActionInterval*  action1 = CCFadeIn::create(1.0f);
	pStartItem->runAction( CCSequence::create( action1, NULL));
	pSettingItem->runAction( CCSequence::create( CCFadeIn::create(1.0f), NULL));
	pHelpItem->runAction( CCSequence::create( CCFadeIn::create(1.0f), NULL));
	pScoresItem->runAction( CCSequence::create( CCFadeIn::create(1.0f), NULL));
	pQuitItem->runAction( CCSequence::create( CCFadeIn::create(1.0f), NULL));

}

bool MenuLayer::init()
{
	if (!CCLayer::init())
		return false;

	setTouchEnabled(true);
	setTouchPriority(kCCMenuHandlerPriority + 1);
	setTouchMode(kCCTouchesOneByOne);

	this->initBackground();
	this->initMenu();

	return true;
}

CCScene* MenuLayer::scene()
{
	CCScene *scene = CCScene::create();
	MenuLayer *layer = MenuLayer::create();
	scene->addChild(layer);
	return scene;
}

void MenuLayer::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MenuLayer::menuStart(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(1, GameLayer::scene()));
}

void MenuLayer::menuHelp(CCObject *pSender)
{
	CCLabelTTF *testLabel = CCLabelTTF::create("Help", "Jenna Sue", 30);
	CCSize size=CCDirector::sharedDirector()->getWinSize();
	testLabel->setPosition(ccp(size.width / 2, size.height / 3));
	this->addChild(testLabel, 2);
}

void MenuLayer::menuScores(CCObject *pSender)
{
	CCLabelTTF *testLabel = CCLabelTTF::create("Scores", "Jenna Sue", 30);
	CCSize size=CCDirector::sharedDirector()->getWinSize();
	testLabel->setPosition(ccp(size.width / 2, size.height / 5));
	this->addChild(testLabel, 2);
}

void MenuLayer::menuSetting(CCObject *pSender)
{
	CCLabelTTF *testLabel = CCLabelTTF::create("Setting", "Jenna Sue", 30);
	CCSize size=CCDirector::sharedDirector()->getWinSize();
	testLabel->setPosition(ccp(size.width / 2, size.height / 4));
	this->addChild(testLabel, 2);
}
