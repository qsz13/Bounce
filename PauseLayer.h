/*
 * PauseLayer.h
 *
 *  Created on: Sep 28, 2013
 *      Author: daniel
 */

#ifndef PAUSELAYER_H_
#define PAUSELAYER_H_
#include "cocos2d.h"
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
};

#endif /* PAUSELAYER_H_ */
