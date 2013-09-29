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
	winSize = CCDirector::sharedDirector()->getWinSize();

	//Background
	// 创建图片精灵
	CCSprite* settingLayerBackground = CCSprite::create("PauseLayer/PauseSceneBackground.png");

	// 设置图片精灵的位置
	settingLayerBackground->setPosition(ccp(winSize.width/2, winSize.height/2));

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


	CCMenuItemImage *pResumeItem = CCMenuItemImage::create(
														  "PauseLayer/Resume.png",
														  "PauseLayer/Resume.png",
														  this,
														  menu_selector(PauseLayer::menupResume));
	pResumeItem -> setPosition( ccp(0, 0) );

	pMenusResume = CCMenu::create(pResumeItem, NULL);
	pMenusResume -> setPosition( ccp(winSize.width / 2, winSize.height+57/2) );
	pMenusResume->setOpacity( 0 );
	this -> addChild(pMenusResume, 1);



	CCMenuItemImage *pSettingItem = CCMenuItemImage::create(
														  "PauseLayer/Setting.png",
														  "PauseLayer/Setting_Pressed.png",
														  this,
														  menu_selector(PauseLayer::menuSetting));
	pSettingItem -> setPosition( ccp(0, 0) );
	//pSettingItem->setOpacity( 0 );

	pMenusSetting = CCMenu::create(pSettingItem, NULL);
	pMenusSetting -> setPosition( ccp(winSize.width / 2, 640) );
	pMenusSetting->setOpacity( 0 );
	this -> addChild(pMenusSetting, 1);





	CCMenuItemImage *pBackToMenuItem = CCMenuItemImage::create(
														  "PauseLayer/BackToMenu.png",
														  "PauseLayer/BackToMenu.png",
														  this,
														  menu_selector(PauseLayer::menuBackToMenu));
	pBackToMenuItem -> setPosition( ccp(0, 0) );
	//pSettingItem->setOpacity( 0 );

	pMenusBackToMenu = CCMenu::create(pBackToMenuItem, NULL);
	pMenusBackToMenu -> setPosition( ccp(winSize.width / 2,-57/2) );
	pMenusBackToMenu->setOpacity( 0 );
	this -> addChild(pMenusBackToMenu, 1);









}

void PauseLayer::keyBackClicked()
{
	resume();
}

void PauseLayer::menuSetting(CCObject *pSender){

	CCDirector::sharedDirector()->pushScene(CCTransitionSlideInR::create(0.3, SettingLayer::scene()));
}

void PauseLayer::menuBackToMenu(CCObject *pSender){

	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.3, MenuLayer::scene()));
}

void PauseLayer::menupResume(CCObject *pSender){
	resume();
}

void PauseLayer::onEnterTransitionDidFinish(){

	CCPoint delta =  ccp(winSize.width / 2, winSize.height-500) - pMenusResume->getPosition();
	CCActionInterval* move = CCMoveBy::create(0.5, delta);
	CCActionInterval* move_ease_out = CCEaseBackOut::create((CCActionInterval*)(move->copy()->autorelease()));
	pMenusResume->runAction( CCSequence::create(CCDelayTime::create(0.5),move_ease_out, NULL));


	delta =  ccp(winSize.width / 2, winSize.height-780) - pMenusBackToMenu->getPosition();
	move = CCMoveBy::create(0.5, delta);
	move_ease_out = CCEaseBackOut::create((CCActionInterval*)(move->copy()->autorelease()));
	pMenusBackToMenu->runAction( CCSequence::create(CCDelayTime::create(0.5),move_ease_out, NULL));


	pMenusResume->runAction( CCSequence::create(  CCFadeIn::create(0.5f), NULL));
	pMenusSetting->runAction( CCSequence::create(  CCFadeIn::create(0.5f), NULL));
	pMenusBackToMenu->runAction( CCSequence::create(  CCFadeIn::create(0.5f), NULL));
}


void PauseLayer::resume(){
	CCPoint delta =  ccp(winSize.width / 2, winSize.height+57/2) - pMenusResume->getPosition();
	CCActionInterval* move = CCMoveBy::create(0.5, delta);
	CCActionInterval* move_ease_in = CCEaseBackIn::create((CCActionInterval*)(move->copy()->autorelease()));
	pMenusResume->runAction( CCSequence::create(CCDelayTime::create(0.5),move_ease_in, NULL));

	delta =  ccp(winSize.width / 2, -57/2) - pMenusBackToMenu->getPosition();
	move = CCMoveBy::create(0.5, delta);
	move_ease_in = CCEaseBackIn::create((CCActionInterval*)(move->copy()->autorelease()));
	pMenusBackToMenu->runAction( CCSequence::create(CCDelayTime::create(0.5),move_ease_in, NULL));


	pMenusResume->runAction( CCSequence::create(  CCFadeOut::create(0.5f), NULL));
	pMenusSetting->runAction( CCSequence::create(  CCFadeOut::create(0.5f), NULL));
	pMenusBackToMenu->runAction(
				CCSequence::create(CCFadeOut::create(0.5f),
						CCCallFunc::create(this,
								callfunc_selector(PauseLayer::popToGameLayer)),
						NULL));

}

void PauseLayer::popToGameLayer(){
	CCDirector::sharedDirector()->popScene();

}

