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
#define MAX_ITEM 3

using namespace cocos2d;

class Item :public CCSprite {
public:
	Item();
	virtual ~Item();
private:
	//int MAX_ITEM = 3;
};

#endif /* ITEM_H_ */
