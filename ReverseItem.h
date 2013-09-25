/*
 * ReverseItem.h
 *
 *  Created on: Sep 25, 2013
 *      Author: daniel
 */

#ifndef REVERSEITEM_H_
#define REVERSEITEM_H_

#include "cocos2d.h"
#include "Item.h"

using namespace cocos2d;
class ReverseItem : public Item{
public:
	ReverseItem();
	virtual ~ReverseItem();
	static ReverseItem* getReverseItem();
	
};

#endif /* REVERSEITEM_H_ */
