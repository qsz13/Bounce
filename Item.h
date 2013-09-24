/*
 * Item.h
 *
 *  Created on: Sep 23, 2013
 *      Author: daniel
 */

#ifndef ITEM_H_
#define ITEM_H_

#include "cocos2d.h"
#define PTM_RATIO 32.0


using namespace cocos2d;

class Item :public CCSprite {
public:
	//static int itemNum;
	Item();
	virtual ~Item();

	CCRect rect();


private:

	//int MAX_ITEM = 3;
};

#endif /* ITEM_H_ */
