/*
 * SettingLayer.h
 *
 *  Created on: Sep 22, 2013
 *      Author: daniel
 */

#ifndef SETTINGLAYER_H_
#define SETTINGLAYER_H_

#include "cocos2d.h"
using namespace cocos2d;

class SettingLayer:public CCLayer {
public:
	SettingLayer();
	virtual ~SettingLayer();
	virtual bool init();
	//static cocos2d::CCScene* scene();

	static int getControlMode();
	static void setControlMode(int mode);

private:
	static int controlMode;
	//0 for gravity 1 for drag 2 for touch;





};

#endif /* SETTINGLAYER_H_ */
