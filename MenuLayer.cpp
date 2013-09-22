/*
 * MenuLayer.cpp
 *
 *  Created on: Sep 17, 2013
 *      Author: daniel
 */

#include "MenuLayer.h"

 // MenuLayer::MenuLayer(){
	// setTouchEnabled(true);
	// setTouchPriority(kCCMenuHandlerPriority + 1);
	// setTouchMode(kCCTouchesOneByOne);
	// CCSprite* startSpriteNormal = CCSprite::create("play_button.png");
	// CCMenuItemSprite* item1 = CCMenuItemSprite::create(startSpriteNormal, startSpriteNormal, startSpriteNormal,
	// 		this, menu_selector(MenuLayer::startCallback) );
	// CCSprite* quitSpriteNormal =  CCSprite::create("quit_button.png");
	// CCMenuItemSprite* item2 = CCMenuItemSprite::create(quitSpriteNormal, quitSpriteNormal, quitSpriteNormal,
	// 			this, menu_selector(MenuLayer::startCallback) );
	// CCMenu* menu = CCMenu::create( item1, item2,NULL);
	// menu->alignItemsVertically();

	// addChild(menu);
	// CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	// menu->setPosition(ccp(winSize.width/2, winSize.height/2));

// }
void MenuLayer::initBackground()
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


void MenuLayer::initMenu()
{
	//Get windows size
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//Start
	CCMenuItemImage *pStartItem = CCMenuItemImage::create(
														  "Start.png",
														  "Start_Pressed.png",
														  this,
														  menu_selector(MenuLayer::menuStart));
	pStartItem -> setPosition( ccp(0, 0) );

	CCMenu* pMenusStart = CCMenu::create(pStartItem, NULL);
	pMenusStart -> setPosition( ccp(size.width / 2, size.height / 2 + 152) );
	this -> addChild(pMenusStart, 1);

	//Help
	CCMenuItemImage *pHelpItem = CCMenuItemImage::create(
														  "Help.png",
														  "Help_Pressed.png",
														  this,
														  menu_selector(MenuLayer::menuStart));
	pHelpItem -> setPosition( ccp(0, 0) );

	CCMenu* pMenusHelp = CCMenu::create(pHelpItem, NULL);
	pMenusHelp -> setPosition( ccp(size.width / 2, size.height / 2) );
	this -> addChild(pMenusHelp, 1);

	//Quit
	CCMenuItemImage *pQuitItem = CCMenuItemImage::create(
														  "Quit.png",
														  "Quit_Pressed.png",
														  this,
														  menu_selector(MenuLayer::menuCloseCallback));
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











CCScene* MenuLayer::scene()
{
    CCScene *scene = CCScene::create();
    MenuLayer *layer = MenuLayer::create();
    scene->addChild(layer);
    return scene;
}

bool MenuLayer::init(){
	//CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	if (!CCLayer::init())
		return false;

	this->initBackground();
	this->initMenu();

	return true;
}


void MenuLayer::menuStart(CCObject* pSender){
	CCDirector::sharedDirector()->replaceScene(GameLayer::scene());

}


void MenuLayer::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
}











