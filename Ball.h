/*
 * Ball.h
 *
 *  Created on: Sep 17, 2013
 *      Author: daniel
 */

#ifndef BALL_H_
#define BALL_H_
#include "cocos2d.h"
#include "Box2D.h"
#include <cmath>
#define PTM_RATIO 32.0

using namespace cocos2d;

struct Velocity {
	float x;
	float y;
	float speed;

};

class Ball: public CCSprite {
public:
	Ball();
	virtual ~Ball();
	static Ball* createBall();
	static Ball* createGhostBall();
	void createBody(b2World &world);
	b2Body* getBody();
	float getWidth();
	float getHeight();
	float getRadius();
	Velocity getVelocity();
	Velocity setVelocity(Velocity v);

	b2Body* getBallBody();
	void setBallBody(b2Body* ballBody);
	CCRect rect();

	void frameAddOne();
	int getFrameLasted();
	int getPriority();

	void frozenFrameAddOne();
	int getFrozenFrameLasted();
	void setFrozenFrameTo0();

	void skewFrameAddOne();
	int getSkewFrameLasted();
	void setSkewFrameLastedTo0();
private:

	Velocity velocity;
	CCTexture2D ballTexture;
	b2Body *ballBody;
	int frameLasted;
	int frozenFrameLasted;
	int skewFrameLasted;
	int priority;
};

#endif /* BALL_H_ */
