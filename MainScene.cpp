/*
 * MainScene.cpp
 *
 *  Created on: 2013-9-17
 *      Author: tomhu
 */

#include "MainScene.h"

using namespace cocos2d;

void MainScene::initBackground()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//Background
	// 创建图片精灵
	CCSprite* pSprite = CCSprite::create("Background.png");

	// 设置图片精灵的位置
	pSprite->setPosition(ccp(size.width/2, size.height/2));

	// 把图片精灵放置在图层中
	this->addChild(pSprite, 0);
}

void MainScene::initMenu()
{
	//Get windows size
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//Start
	CCMenuItemImage *pStartItem = CCMenuItemImage::create(
														  "Start.png",
														  "Start_Pressed.png",
														  this,
														  menu_selector(MainScene::menuStart));
	pStartItem -> setPosition( ccp(0, 0) );

	CCMenu* pMenusStart = CCMenu::create(pStartItem, NULL);
	pMenusStart -> setPosition( ccp(size.width / 2, size.height / 2 + 152) );
	this -> addChild(pMenusStart, 1);

	//Help
	CCMenuItemImage *pHelpItem = CCMenuItemImage::create(
														  "Help.png",
														  "Help_Pressed.png",
														  this,
														  menu_selector(MainScene::menuStart));
	pHelpItem -> setPosition( ccp(0, 0) );

	CCMenu* pMenusHelp = CCMenu::create(pHelpItem, NULL);
	pMenusHelp -> setPosition( ccp(size.width / 2, size.height / 2) );
	this -> addChild(pMenusHelp, 1);

	//Quit
	CCMenuItemImage *pQuitItem = CCMenuItemImage::create(
														  "Quit.png",
														  "Quit_Pressed.png",
														  this,
														  menu_selector(MainScene::menuCloseCallback));
	pQuitItem -> setPosition( ccp(0, 0) );

	CCMenu* pMenusQuit = CCMenu::create(pQuitItem, NULL);
	pMenusQuit -> setPosition( ccp(size.width / 2, size.height / 2 - 152) );
	this -> addChild(pMenusQuit, 1);

//	//Close
//	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
//											"CloseNormal.png",
//											"CloseSelected.png",
//											this,
//											menu_selector(MainScene::menuCloseCallback));
//	pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
//	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
//	pMenu->setPosition( CCPointZero );
//	this->addChild(pMenu, 1);
}

bool MainScene::init()
{
	if (!CCLayer::init())
		return false;

	this->initBackground();
	this->initMenu();

	return true;
}

CCScene* MainScene::scene()
{
	CCScene *scene = CCScene::create();
	MainScene *layer = MainScene::create();
	scene->addChild(layer);
	return scene;
}

void MainScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
}

void MainScene::menuStart(CCObject* pSender)
{
//	CCLabelTTF *testLabel = CCLabelTTF::create("Test", "Jenna Sue", 30);
//	CCSize size=CCDirector::sharedDirector()->getWinSize();
//	testLabel->setPosition(ccp(size.width / 2, size.height / 3));
//	this->addChild(testLabel, 2);

	CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
}
