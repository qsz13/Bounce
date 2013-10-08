/*
 * DoubleItem.h
 *
 *  Created on: Sep 25, 2013
 *      Author: daniel
 */

#ifndef DOUBLEITEM_H_
#define DOUBLEITEM_H_

#include "cocos2d.h"
#include "Item.h"

using namespace cocos2d;

class DoubleItem: public Item {
public:
	DoubleItem();
	virtual ~DoubleItem();
	static DoubleItem* createDoubleItem();
};

#endif /* DOUBLEITEM_H_ */
