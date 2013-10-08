/*
 * ReverseYItem.h
 *
 *  Created on: Sep 25, 2013
 *      Author: daniel
 */

#ifndef REVERSEYITEM_H_
#define REVERSEYITEM_H_

#include "cocos2d.h"
#include "Item.h"

class ReverseYItem: public Item {
public:
	ReverseYItem();
	virtual ~ReverseYItem();
	static ReverseYItem* createReverseYItem();
};

#endif /* REVERSEYITEM_H_ */
