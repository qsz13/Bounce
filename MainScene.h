/*
 * MainScene.h
 *
 *  Created on: 2013-9-17
 *      Author: tomhu
 */

#ifndef MAINSCENE_H_
#define MAINSCENE_H_

#include "cocos2d.h"
#include "GameLayer.h"

class MainScene : public cocos2d::CCLayer
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

	CREATE_FUNC(MainScene);
};

#endif /* TESTSCENE_H_ */
