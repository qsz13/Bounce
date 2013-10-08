/*
 * EnlargeItem.h
 *
 *  Created on: Sep 23, 2013
 *      Author: daniel
 */

#ifndef ENLARGEITEM_H_
#define ENLARGEITEM_H_

#include "cocos2d.h"
#include "Item.h"
#define PTM_RATIO 32.0
using namespace cocos2d;

class EnlargeItem: public Item {
public:
	EnlargeItem();
	virtual ~EnlargeItem();
	static EnlargeItem* createEnlargeItem();

};

#endif /* ENLARGEITEM_H_ */
