/*
 * SettingLayer.cpp
 *
 *  Created on: Sep 22, 2013
 *      Author: daniel
 */

#include "SettingLayer.h"

int SettingLayer::controlMode = 1;

SettingLayer::SettingLayer() {
	// TODO Auto-generated constructor stub

}

SettingLayer::~SettingLayer() {
	// TODO Auto-generated destructor stub
}


int SettingLayer::getControlMode(){
	return controlMode;

}



void SettingLayer::setControlMode(int mode){
	controlMode = mode;

}