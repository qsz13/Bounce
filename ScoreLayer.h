/*
 * ScoreLayer.h
 *
 *  Created on: Sep 28, 2013
 *      Author: daniel
 */

#ifndef SCORELAYER_H_
#define SCORELAYER_H_
#include "cocos2d.h"
using namespace cocos2d;

class ScoreLayer :public CCLayer{
public:
	ScoreLayer();
	virtual ~ScoreLayer();
	static CCScene* scene();
	CREATE_FUNC (ScoreLayer);
private:
	void initBackground();
	bool init();
	void keyBackClicked();

};

#endif /* SCORELAYER_H_ */
