/*
 * SettingLayer.cpp
 *
 *  Created on: Sep 22, 2013
 *      Author: daniel
 */

#include "SettingLayer.h"
using namespace cocos2d;
using namespace cocos2d::extension;


SettingLayer::ControlType SettingLayer::controlMode;
int SettingLayer::sensitivity;

SettingLayer::SettingLayer() {

}

SettingLayer::~SettingLayer() {
	// TODO Auto-generated destructor stub
}


CCScene* SettingLayer::scene()
{
    CCScene *scene = CCScene::create();
    SettingLayer* layer = SettingLayer::create();
    scene->addChild(layer);
    return scene;
}

bool SettingLayer::init()
{
	if (!CCLayer::init())
		return false;
	setKeypadEnabled(true);
	setTouchEnabled(true);
	// setTouchPriority(kCCMenuHandlerPriority + 1);
	// setTouchMode(kCCTouchesOneByOne);


	this->initBackground();
	this->initControlMode();
	this->initGravitySeneitivity();
	this->initBackButton();

	return true;
}

void SettingLayer::initBackground()
{

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//Background
	// 创建图片精灵
	CCSprite* settingLayerBackground = CCSprite::create("SettingLayer/SettingSceneBackground.png");

	// 设置图片精灵的位置
	settingLayerBackground->setPosition(ccp(size.width/2, size.height/2));

	// 把图片精灵放置在图层中
	this->addChild(settingLayerBackground, 0);
}
void SettingLayer::initBackButton()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

    //Pause Button
    CCMenuItemImage *backButtonImage = CCMenuItemImage::create(
                                                          "SettingLayer/Back.png",
                                                          "SettingLayer/Back_Pressed.png",
                                                          this,
                                                          menu_selector(SettingLayer::backButtonPressed));
    backButtonImage -> setPosition( ccp(0, 0) );
    CCMenu* backButton = CCMenu::create(backButtonImage, NULL);
    backButton -> setPosition( ccp(size.width / 2, size.height - 1019) );
    this -> addChild(backButton, 3);
}

void SettingLayer::initControlMode()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	
	//Control Mode Label
    // 创建图片精灵
    CCSprite* controlModeLabel = CCSprite::create("SettingLayer/ControlMode/controlModeLabel.png");

    // 设置图片精灵的位置
    controlModeLabel->setPosition(ccp((401.5 + 46.4) / 2, size.height - (394 + 360) / 2));

    // 把图片精灵放置在图层中
    this->addChild(controlModeLabel, 1);

    //Control Mode
    //Gravity
    CCMenuItemImage *controlModeGravityImage = CCMenuItemImage::create(
                                                          "SettingLayer/ControlMode/controlModeGravity.png",
                                                          "SettingLayer/ControlMode/controlModeGravity.png",
                                                          this,
                                                          menu_selector(SettingLayer::controlModeToGravity));
    controlModeGravityImage -> setPosition( ccp(0, 0) );
    controlModeGravity = CCMenu::create(controlModeGravityImage, NULL);
    controlModeGravity -> setPosition( ccp(size.width / 2 - 195, size.height - 456.5) );
    this -> addChild(controlModeGravity, 1);

    //Drag
    CCMenuItemImage *controlModeDragImage = CCMenuItemImage::create(
                                                          "SettingLayer/ControlMode/controlModeDrag.png",
                                                          "SettingLayer/ControlMode/controlModeDrag.png",
                                                          this,
                                                          menu_selector(SettingLayer::controlModeToDrag));
    controlModeDragImage -> setPosition( ccp(0, 0) );
    controlModeDrag = CCMenu::create(controlModeDragImage, NULL);
    controlModeDrag -> setPosition( ccp(size.width / 2  + 195, size.height - 456.5) );
    this -> addChild(controlModeDrag, 1);

    //Touch
    CCMenuItemImage *controlModeTouchImage = CCMenuItemImage::create(
                                                          "SettingLayer/ControlMode/controlModeTouch.png",
                                                          "SettingLayer/ControlMode/controlModeTouch.png",
                                                          this,
                                                          menu_selector(SettingLayer::controlModeToTouch));
    controlModeTouchImage -> setPosition( ccp(0, 0) );
    controlModeTouch = CCMenu::create(controlModeTouchImage, NULL);
    controlModeTouch -> setPosition( ccp(size.width / 2, size.height - 456.5) );
    this -> addChild(controlModeTouch, 1);

    //Selector
    // 创建图片精灵
    controlModeSelector = CCSprite::create("SettingLayer/ControlMode/controlModeSelector.png");

    if(controlMode == GRAVITY){
      controlModeSelector->setPosition(controlModeGravity->getPosition());
    }
    else if( controlMode == TOUCH){
      controlModeSelector->setPosition(controlModeTouch->getPosition());
    }
    else if( controlMode == DRAG){
      controlModeSelector->setPosition(controlModeDrag->getPosition());
    }


    // 把图片精灵放置在图层中
    this->addChild(controlModeSelector, 2);
}
void SettingLayer::initGravitySeneitivity()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//Gravity Sensitivity Label
	// 创建图片精灵
    CCSprite* gravitySensitivityLabel = CCSprite::create("SettingLayer/GravitySensitivity/gravitySensitivityLabel.png");

    // 设置图片精灵的位置
    gravitySensitivityLabel->setPosition(ccp((523.2 + 46.4) / 2, size.height - (590 + 640) / 2));

    // 把图片精灵放置在图层中
    this->addChild(gravitySensitivityLabel, 1);


	//Gravity Sensitivity Control 
	gravitySensitivityControlSlider = this->sliderCtl();
	gravitySensitivityControlSlider->setPosition(ccp(size.width / 2, size.height - 680.5));

	this->addChild(gravitySensitivityControlSlider, 2);
}

void SettingLayer::backButtonPressed()
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("Sensitivity",sensitivity);
	CCDirector::sharedDirector()->popSceneWithTransition<CCTransitionSlideInR>(0.3);
}

void SettingLayer::controlModeToGravity()
{
	this->setControlMode(GRAVITY);
  CCUserDefault::sharedUserDefault()->setStringForKey("ControlMode","GRAVITY");

  CCPoint delta = controlModeGravity->getPosition() - controlModeSelector->getPosition();

  CCActionInterval* move = CCMoveBy::create(1, delta);
  CCActionInterval* move_ease_out = CCEaseElasticOut::create((CCActionInterval*)(move->copy()->autorelease()));
  controlModeSelector->runAction( CCSequence::create(move_ease_out, NULL));

}

void SettingLayer::controlModeToTouch()
{
	this->setControlMode(TOUCH);
  CCUserDefault::sharedUserDefault()->setStringForKey("ControlMode","TOUCH");

  CCPoint delta = controlModeTouch->getPosition() - controlModeSelector->getPosition();

  CCActionInterval* move = CCMoveBy::create(1, delta);
  CCActionInterval* move_ease_out = CCEaseElasticOut::create((CCActionInterval*)(move->copy()->autorelease()));

  controlModeSelector->runAction( CCSequence::create(move_ease_out, NULL));
}

void SettingLayer::controlModeToDrag()
{
	this->setControlMode(DRAG);
  CCUserDefault::sharedUserDefault()->setStringForKey("ControlMode","DRAG");

  CCPoint delta = controlModeDrag->getPosition() - controlModeSelector->getPosition();

  CCActionInterval* move = CCMoveBy::create(1, delta);
  CCActionInterval* move_ease_out = CCEaseElasticOut::create((CCActionInterval*)(move->copy()->autorelease()));
  controlModeSelector->runAction(CCSequence::create(move_ease_out, NULL));
}



CCControlSlider* SettingLayer::sliderCtl()
{

	CCControlSlider *slider = CCControlSlider::create("SettingLayer/GravitySensitivity/controlSlider.png", "SettingLayer/GravitySensitivity/controlSliderProgress.png", "SettingLayer/GravitySensitivity/controlButton.png");
    slider->setMinimumValue(100);
    slider->setMaximumValue(350);
    slider->addTargetWithActionForControlEvents(this, cccontrol_selector(SettingLayer::sliderAction), CCControlEventValueChanged);


    slider->setValue(sensitivity);

    return slider;
}

void SettingLayer::sliderAction(CCObject* pSender, CCControlEvent controlEvent)
{
	CCControlSlider* pSliderCtl = (CCControlSlider*)pSender;
    sensitivity = pSliderCtl->getValue();

}


int SettingLayer::getSensitivity()
{
	return sensitivity;

}
void SettingLayer::setSensitivity(int s)
{
	sensitivity = s;
}

int SettingLayer::getControlMode()
{
	return controlMode;
}


void SettingLayer::setControlMode(SettingLayer::ControlType mode)
{
	controlMode = mode;
}

void SettingLayer::keyBackClicked()
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("Sensitivity",sensitivity);
	CCDirector::sharedDirector()->popSceneWithTransition<CCTransitionSlideInR>(0.3);
}
