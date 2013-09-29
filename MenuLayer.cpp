/*
 * MenuLayer.cpp
 *
 *  Created on: 2013-9-17
 *      Author: tomhu
 */

#include "MenuLayer.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
using namespace CocosDenshion;


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
	pStartItem->setOpacity( 0 );

	CCMenu* pMenusStart = CCMenu::create(pStartItem, NULL);
	pMenusStart -> setPosition( ccp(size.width/2,0) );
	this -> addChild(pMenusStart, 1);

	CCPoint delta =  ccp(size.width / 2, size.height / 2 - 171) - pMenusStart->getPosition();

  	CCActionInterval* move = CCMoveBy::create(1, delta);
  	CCActionInterval* move_ease_out = CCEaseBackOut::create((CCActionInterval*)(move->copy()->autorelease()));
  	pMenusStart->runAction( CCSequence::create(move_ease_out, NULL));




	//Setting
	CCMenuItemImage *pSettingItem = CCMenuItemImage::create(
														  "MenuLayer/Setting.png",
														  "MenuLayer/Setting_Pressed.png",
														  this,
														  menu_selector(MenuLayer::menuSetting));
	pSettingItem -> setPosition( ccp(0, 0) );
	pSettingItem->setOpacity( 0 );

	CCMenu* pMenusSetting = CCMenu::create(pSettingItem, NULL);
	pMenusSetting -> setPosition( ccp(0, size.height / 2 - 171 - 100) );
	this -> addChild(pMenusSetting, 1);




	delta =  ccp(size.width / 2, size.height / 2 - 171 - 100) - pMenusSetting->getPosition();

  	move = CCMoveBy::create(1, delta);
  	move_ease_out = CCEaseBackOut::create((CCActionInterval*)(move->copy()->autorelease()));
  	pMenusSetting->runAction( CCSequence::create(CCDelayTime::create(0.5),move_ease_out, NULL));



	//Help
	CCMenuItemImage *pHelpItem = CCMenuItemImage::create(
														  "MenuLayer/Help.png",
														  "MenuLayer/Help_Pressed.png",
														  this,
														  menu_selector(MenuLayer::menuHelp));
	pHelpItem -> setPosition( ccp(0, 0) );
	pHelpItem->setOpacity( 0 );

	CCMenu* pMenusHelp = CCMenu::create(pHelpItem, NULL);
	pMenusHelp -> setPosition( ccp(size.width, size.height / 2 - 171 - 100 - 80) );
	this -> addChild(pMenusHelp, 1);



	delta =  ccp(size.width / 2, size.height / 2 - 171 - 100 - 80) - pMenusHelp->getPosition();

	move = CCMoveBy::create(1, delta);
	move_ease_out = CCEaseBackOut::create((CCActionInterval*)(move->copy()->autorelease()));
	pMenusHelp->runAction( CCSequence::create(CCDelayTime::create(0.5),move_ease_out, NULL));

	//Scores
	CCMenuItemImage *pScoresItem = CCMenuItemImage::create(
														  "MenuLayer/HighScore.png",
														  "MenuLayer/HighScore_Pressed.png",
														  this,
														  menu_selector(MenuLayer::menuHighScore));
	pScoresItem -> setPosition( ccp(0, 0) );
	pScoresItem->setOpacity( 0 );

	CCMenu* pScoresHelp = CCMenu::create(pScoresItem, NULL);
	pScoresHelp -> setPosition( ccp(0, size.height / 2 - 171 - 100 - 80 * 2) );
	this -> addChild(pScoresHelp, 1);


	delta =  ccp(size.width / 2, size.height / 2 - 171 - 100 - 80 * 2) - pScoresHelp->getPosition();

  	move = CCMoveBy::create(1, delta);
  	move_ease_out = CCEaseBackOut::create((CCActionInterval*)(move->copy()->autorelease()));
  	pScoresHelp->runAction( CCSequence::create(CCDelayTime::create(0.5),move_ease_out, NULL));

	//Quit
	CCMenuItemImage *pQuitItem = CCMenuItemImage::create(
														  "MenuLayer/Quit.png",
														  "MenuLayer/Quit_Pressed.png",
														  this,
														  menu_selector(MenuLayer::menuQuit));
	pQuitItem -> setPosition( ccp(0, 0) );
	pQuitItem->setOpacity( 0 );

	CCMenu* pMenusQuit = CCMenu::create(pQuitItem, NULL);
	pMenusQuit -> setPosition( ccp(size.width, size.height / 2 - 171 - 100 - 80 * 3) );
	this -> addChild(pMenusQuit, 1);

	delta =  ccp(size.width / 2, size.height / 2 - 171 - 100 - 80 * 3) - pMenusQuit->getPosition();

	move = CCMoveBy::create(1, delta);
	move_ease_out = CCEaseBackOut::create((CCActionInterval*)(move->copy()->autorelease()));
	pMenusQuit->runAction( CCSequence::create(CCDelayTime::create(0.5),move_ease_out, NULL));


	CCActionInterval*  action1 = CCFadeIn::create(1.0f);
	pStartItem->runAction( CCSequence::create( action1, NULL));
	pSettingItem->runAction( CCSequence::create(CCDelayTime::create(0.5), CCFadeIn::create(1.0f), NULL));
	pHelpItem->runAction( CCSequence::create( CCDelayTime::create(0.5),CCFadeIn::create(1.0f), NULL));
	pScoresItem->runAction( CCSequence::create( CCDelayTime::create(0.5),CCFadeIn::create(1.0f), NULL));
	pQuitItem->runAction( CCSequence::create( CCDelayTime::create(0.5),CCFadeIn::create(1.0f), NULL));

}

bool MenuLayer::init()
{
	if (!CCLayer::init())
		return false;

	setTouchEnabled(true);
//	setTouchPriority(kCCMenuHandlerPriority + 1);
//	setTouchMode(kCCTouchesOneByOne);

	this->initBackground();
	this->initMenu();
	this->getHighScoreFromFile();
	this->getControlModeFromFile();
	this->getSensitivityFromFile();
	//preloadBackgroundMusic("background.mp3");
	//SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background.mp3",true);
	return true;
}

CCScene* MenuLayer::scene()
{
	CCScene *scene = CCScene::create();
	MenuLayer *layer = MenuLayer::create();
	scene->addChild(layer);
	return scene;
}

void MenuLayer::menuQuit(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

}

void MenuLayer::menuStart(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.3, GameLayer::scene()));
}

void MenuLayer::menuHelp(CCObject *pSender)
{
	CCDirector::sharedDirector()->pushScene(CCTransitionSlideInB::create(0.3, HelpLayer::scene()));
}

void MenuLayer::menuHighScore(CCObject *pSender)
{
	CCDirector::sharedDirector()->pushScene(CCTransitionSlideInT::create(0.3, ScoreLayer::scene()));
}

void MenuLayer::menuSetting(CCObject *pSender)
{
	CCDirector::sharedDirector()->pushScene(CCTransitionSlideInL::create(0.3, SettingLayer::scene()));
}


bool MenuLayer::haveSavedFile()
{  
    if(!CCUserDefault::sharedUserDefault()->getBoolForKey("haveSavedFileXml"))//通过设置的bool型标志位判断，如果不存在  
    {  
        CCUserDefault::sharedUserDefault()->setBoolForKey("haveSavedFileXml", true);//写入bool判断位  
        CCUserDefault::sharedUserDefault()->setIntegerForKey("HighScore",0);//写入初始分数0  
        CCUserDefault::sharedUserDefault()->setStringForKey	("ControlMode","TOUCH");
        CCUserDefault::sharedUserDefault()->setIntegerForKey("Sensitivity",200);
        CCUserDefault::sharedUserDefault()->flush();//设置完一定要调用flush，才能从缓冲写入io  
        return false;
    }  
    else  
    {  
        return true;  
    }  
}  

void MenuLayer::getHighScoreFromFile()
{  
    if (haveSavedFile())//如果存在存档  
    {  
        ScoreData::highScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("HighScore",0); 
    }  
}  


void MenuLayer::getControlModeFromFile(){;
	if(haveSavedFile()){
		string cm = CCUserDefault::sharedUserDefault()->getStringForKey("ControlMode","TOUCH");
		if(cm == "TOUCH"){
			SettingLayer::setControlMode(SettingLayer::TOUCH);
		} 
		else if(cm == "GRAVITY"){
			SettingLayer::setControlMode(SettingLayer::GRAVITY);
		}
		else if(cm == "DRAG"){
			SettingLayer::setControlMode(SettingLayer::DRAG);
		}
	}
}

void MenuLayer::getSensitivityFromFile(){
	if(haveSavedFile()){
		//CCLOG("from file : %d",CCUserDefault::sharedUserDefault()->getIntegerForKey("Sensitivity",200));
		SettingLayer::setSensitivity(CCUserDefault::sharedUserDefault()->getIntegerForKey("Sensitivity",200));
		//CCLOG("%d !!",SettingLayer::getSensitivity());
	}
}
