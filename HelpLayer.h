/*
 * HelpLayer.h
 *
 *  Created on: Sep 28, 2013
 *      Author: daniel
 */

#ifndef HELPLAYER_H_
#define HELPLAYER_H_
 #include "cocos2d.h"
using namespace cocos2d;

class HelpLayer : public CCLayer{
public:
	HelpLayer();
	virtual ~HelpLayer();
	static CCScene* scene();
	CREATE_FUNC (HelpLayer);
private:
	void initBackground();
	bool init();
	void keyBackClicked();


};

#endif /* HELPLAYER_H_ */
