/*
 * MenuLayer.h
 *
 *  Created on: 2013-9-17
 *      Author: tomhu
 */

#ifndef MENULAYER_H_
#define MENULAYER_H_

#include "cocos2d.h"
#include "GameLayer.h"
#include "SettingLayer.h"
#include "ScoreLayer.h"
#include "HelpLayer.h"
#include <string>
class MenuLayer: public cocos2d::CCLayer {
private:
	void initBackground();
	void initMenu();
	void actionCallback();
	static bool haveSavedFile();

public:

	virtual bool init();

	static cocos2d::CCScene* scene();

	void menuQuit(CCObject *pSender);
	void menuStart(CCObject *pSender);
	void menuHelp(CCObject *pSender);
	void menuHighScore(CCObject *pSender);
	void menuSetting(CCObject *pSender);

	static void getSensitivityFromFile();
	static void getHighScoreFromFile();
	static void getControlModeFromFile();
	CREATE_FUNC (MenuLayer);
	bool ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent);
};

#endif /* MENULAYER_H_ */
