/*
 * SettingLayer.cpp
 *
 *  Created on: Sep 22, 2013
 *      Author: daniel
 */

#include "SettingLayer.h"

SettingLayer::ControlType SettingLayer::controlMode = Drag;
int SettingLayer::sensitivity = 250;

int SettingLayer::getSensitivity(){
	return sensitivity;

}
void SettingLayer::setSensitivity(int s){
	sensitivity = s;
}


SettingLayer::SettingLayer() {
	// TODO Auto-generated constructor stub

}

SettingLayer::~SettingLayer() {
	// TODO Auto-generated destructor stub
}


int SettingLayer::getControlMode(){
	return controlMode;
}


void SettingLayer::setControlMode(SettingLayer::ControlType mode){
	controlMode = mode;
}
