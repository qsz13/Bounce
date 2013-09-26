/*
 * Paddle.h
 *
 *  Created on: Sep 17, 2013
 *      Author: daniel
 */

#ifndef PADDLE_H_
#define PADDLE_H_

#include "cocos2d.h"
#include "Box2D.h"
#define PTM_RATIO 32.0
using namespace cocos2d;

class Paddle : public CCSprite{
public:
	Paddle();
	virtual ~Paddle();
	b2BodyDef* getBodyDef();
	enum lengthType{shortPaddle,normalPaddle,longPaddle};
	lengthType getLengthState();
	void setLengthState(lengthType length);
	void setFrameLastedTo0();
	int getFrameLasted();
	void frameAddOne();
protected:
	b2BodyDef paddleBodyDef;
	lengthType lengthState;
	int frameLasted;
};

#endif /* PADDLE_H_ */
