/*
 * MyPaddle.h
 *
 *  Created on: Sep 17, 2013
 *      Author: daniel
 */

#ifndef MYPADDLE_H_
#define MYPADDLE_H_
#include "cocos2d.h"
#include "Paddle.h"
using namespace cocos2d;
// #define MY_PADDLE_SCALE_X 0.3
// #define MY_PADDLE_SCALE_Y 0.5

class MyPaddle : public Paddle {
public:


	static MyPaddle* getMyPaddle();

	void myInit();
	float getWidth();
	float getHeight();

    b2Body* getMyPaddleBody();
    void setMyPaddleBody(b2Body* myPaddleBody);

	
protected:
	//static MyPaddle *myPaddle;
	MyPaddle();
	virtual ~MyPaddle();
	b2Body *myPaddleBody;
	//static CCTexture2D * image ;
};

#endif /* MYPADDLE_H_ */
