/*
 * MenuLayer.cpp
 *
 *  Created on: Sep 17, 2013
 *      Author: daniel
 */

#include "MenuLayer.h"

 MenuLayer::MenuLayer(){
	setTouchEnabled(true);
	setTouchPriority(kCCMenuHandlerPriority + 1);
	setTouchMode(kCCTouchesOneByOne);
	CCSprite* startSpriteNormal = CCSprite::create("play_button.png");
	CCMenuItemSprite* item1 = CCMenuItemSprite::create(startSpriteNormal, startSpriteNormal, startSpriteNormal,
			this, menu_selector(MenuLayer::startCallback) );
	CCSprite* quitSpriteNormal =  CCSprite::create("quit_button.png");
	CCMenuItemSprite* item2 = CCMenuItemSprite::create(quitSpriteNormal, quitSpriteNormal, quitSpriteNormal,
				this, menu_selector(MenuLayer::startCallback) );
	CCMenu* menu = CCMenu::create( item1, item2,NULL);
	menu->alignItemsVertically();

	addChild(menu);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	menu->setPosition(ccp(winSize.width/2, winSize.height/2));

}

CCScene* MenuLayer::scene()
{
    CCScene *scene = CCScene::create();
    MenuLayer *layer = MenuLayer::create();
    scene->addChild(layer);
    return scene;
}

bool MenuLayer::init(){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

}


void MenuLayer::startCallback(CCObject* pSender){
	CCDirector::sharedDirector()->replaceScene(GameLayer::scene());

}














