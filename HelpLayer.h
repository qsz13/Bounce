/*
 * HelpLayer.h
 *
 *  Created on: Sep 28, 2013
 *      Author: daniel
 */

#ifndef HELPLAYER_H_
#define HELPLAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ScrollLayer.h"

using namespace cocos2d;
USING_NS_CC_EXT;

class HelpLayer: public CCLayer {
public:
	HelpLayer();
	virtual ~HelpLayer();
	static CCScene* scene();
	CREATE_FUNC (HelpLayer);

	static CCSprite *movingDot;

private:
	void initBackground();
	bool init();
	void keyBackClicked();
	void initBackButton();

	void backButtonPressed();
	void initScroll();
	CCSize winSize;

};

#endif /* HELPLAYER_H_ */
