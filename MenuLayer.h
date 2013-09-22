/*
 * MenuLayer.h
 *
 *  Created on: Sep 17, 2013
 *      Author: daniel
 */

#ifndef MENULAYER_H_
#define MENULAYER_H_

#include "cocos2d.h"
#include "GameLayer.h"
using namespace cocos2d;
class MenuLayer : public CCLayer{


private:

	void initBackground();
	void initMenu();

public:
	//MenuLayer();
	virtual bool init();
	static CCScene* scene();
	void menuCloseCallback(CCObject* pSender);
	void menuStart(CCObject* pSender);

	CREATE_FUNC(MenuLayer);

};

#endif /* MENULAYER_H_ */
