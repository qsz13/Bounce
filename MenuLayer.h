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

class MenuLayer : public cocos2d::CCLayer
{
private:
	void initBackground();
	void initMenu();

public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	void menuCloseCallback(CCObject *pSender);
	void menuStart(CCObject *pSender);
	void menuHelp(CCObject *pSender);
	void menuScores(CCObject *pSender);
	void menuSetting(CCObject *pSender);

	CREATE_FUNC(MenuLayer);
};

#endif /* MENULAYER_H_ */
