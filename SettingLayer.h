/*
 * SettingLayer.h
 *
 *  Created on: Sep 22, 2013
 *      Author: daniel
 */

#ifndef SETTINGLAYER_H_
#define SETTINGLAYER_H_


#include "cocos2d.h"
#include "GameLayer.h"
using namespace cocos2d;

class SettingLayer : public CCLayer{
public:
	SettingLayer();
	virtual ~SettingLayer();

	static int getControlMode();
	static void setControlMode(int mode);

private:
	static int controlMode;
	//0 for Accelerometer 1 for drag 2 for touch
};

#endif /* SETTINGLAYER_H_ */
