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
public:
	MenuLayer();
	virtual bool init();
	static CCScene* scene();

	CREATE_FUNC(MenuLayer);


	 void startCallback(CCObject* pSender);

private:

	//CCSprite *startButton;

};

#endif /* MENULAYER_H_ */
