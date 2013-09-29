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
	this->initMenu();

	return true;
}


void PauseLayer::initMenu(){
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCMenuItemImage *pSettingItem = CCMenuItemImage::create(
														  "PauseLayer/Setting.png",
														  "PauseLayer/Setting_Pressed.png",
														  this,
														  menu_selector(PauseLayer::menuSetting));
	pSettingItem -> setPosition( ccp(0, 0) );
	//pSettingItem->setOpacity( 0 );

	CCMenu* pMenusSetting = CCMenu::create(pSettingItem, NULL);
	pMenusSetting -> setPosition( ccp(size.width / 2, size.height / 2 - 171 - 100) );
	this -> addChild(pMenusSetting, 1);





	CCMenuItemImage *pBackToMenuItem = CCMenuItemImage::create(
														  "PauseLayer/BackToMenu.png",
														  "PauseLayer/BackToMenu.png",
														  this,
														  menu_selector(PauseLayer::menuBackToMenu));
	pBackToMenuItem -> setPosition( ccp(0, 0) );
	//pSettingItem->setOpacity( 0 );

	CCMenu* pMenusBackToMenu = CCMenu::create(pBackToMenuItem, NULL);
	pMenusBackToMenu -> setPosition( ccp(size.width / 2, size.height / 2) );
	this -> addChild(pMenusBackToMenu, 1);





	CCMenuItemImage *pResumeItem = CCMenuItemImage::create(
														  "PauseLayer/Resume.png",
														  "PauseLayer/Resume.png",
														  this,
														  menu_selector(PauseLayer::menupResume));
	pResumeItem -> setPosition( ccp(0, 0) );
	//pSettingItem->setOpacity( 0 );

	CCMenu* pMenusResume = CCMenu::create(pResumeItem, NULL);
	pMenusResume -> setPosition( ccp(size.width / 2, size.height / 2 + 100) );
	this -> addChild(pMenusResume, 1);



}

void PauseLayer::keyBackClicked()
{
	CCDirector::sharedDirector()->popSceneWithTransition<CCTransitionSlideInR>(0.3);
}

void PauseLayer::menuSetting(CCObject *pSender){

	CCDirector::sharedDirector()->pushScene(CCTransitionSlideInR::create(0.3, SettingLayer::scene()));
}

void PauseLayer::menuBackToMenu(CCObject *pSender){

	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.3, MenuLayer::scene()));
}

void PauseLayer::menupResume(CCObject *pSender){
	CCDirector::sharedDirector()->popSceneWithTransition<CCTransitionSlideInR>(0.3);
}
