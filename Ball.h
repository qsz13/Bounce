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
//#define BALL_SCALE 0.2
using namespace cocos2d;

struct Velocity{
	float x;
	float y;
	float speed;

};

class Ball :public CCSprite{
public:
	Ball();
	virtual ~Ball();
	static Ball* getBall();

	void myInit();
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

private:
	static Ball *ball;
	Velocity velocity;
	CCTexture2D ballTexture;
	b2Body *ballBody;

};

#endif /* BALL_H_ */
