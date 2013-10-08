/*
 * ReverseXItem.h
 *
 *  Created on: Sep 25, 2013
 *      Author: daniel
 */

#ifndef REVERSEITEM_H_
#define REVERSEITEM_H_

#include "cocos2d.h"
#include "Item.h"

using namespace cocos2d;
class ReverseXItem: public Item {
public:
	ReverseXItem();
	virtual ~ReverseXItem();
	static ReverseXItem* createReverseXItem();

};

#endif /* REVERSEITEM_H_ */
