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

class SettingLayer : public cocos2d::CCLayer{
public:
	SettingLayer();
	virtual ~SettingLayer();
	static CCScene* scene();
	enum ControlType{GRAVITY,DRAG,TOUCH};
	static int getControlMode();
	static void setControlMode(ControlType mode);
	static int getSensitivity();
	static void setSensitivity(int sensitivity);
	CREATE_FUNC (SettingLayer);

private:
	void initBackground();
	bool init();
	static int sensitivity;
	static ControlType controlMode;
	

	//0 for Accelerometer 1 for drag 2 for touch



	/*
	 * control mode
	 * music on/off
	 * volume
	 * if gravity control{
	 * 		set sensitivity
	 * }
	 *
	 *
	 */




};

#endif /* SETTINGLAYER_H_ */
