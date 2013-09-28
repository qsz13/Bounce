/*
 * PauseLayer.h
 *
 *  Created on: Sep 28, 2013
 *      Author: daniel
 */

#ifndef PAUSELAYER_H_
#define PAUSELAYER_H_
#include "cocos2d.h"
#include "SettingLayer.h"
#include "MenuLayer.h"
using namespace cocos2d;
class PauseLayer : public CCLayer {
public:
	PauseLayer();
	virtual ~PauseLayer();
	static CCScene* scene();

	CREATE_FUNC (PauseLayer);

private:

	void initBackground();
	bool init();
	void keyBackClicked();
	void initMenu();
	void menuSetting(CCObject *pSender);
	void menuBackToMenu(CCObject *pSender);
	void menupResume(CCObject *pSender);
};

#endif /* PAUSELAYER_H_ */
