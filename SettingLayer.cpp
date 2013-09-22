/*
 * SettingLayer.cpp
 *
 *  Created on: Sep 22, 2013
 *      Author: daniel
 */

#include "SettingLayer.h"

int SettingLayer::controlMode = 1;

SettingLayer::SettingLayer() {

}

SettingLayer::~SettingLayer() {
	
}

//
//CCScene* SettingLayer::scene()
//{
//       // 'scene' is an autorelease object
//    CCScene *scene = CCScene::create();
//
//    // 'layer' is an autorelease object
//    SettingLayer *layer = SettingLayer::create();
//
//    // add layer as a child to scene
//    scene->addChild(layer);
//
//    // return the scene
//    return scene;
//
//}



bool SettingLayer::init(){

}





int SettingLayer::getControlMode(){
	return controlMode;
}

void SettingLayer::setControlMode(int mode){
	controlMode = mode;

}
