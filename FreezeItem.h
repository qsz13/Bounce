/*
 * FreezeItem.h
 *
 *  Created on: Sep 26, 2013
 *      Author: daniel
 */

#ifndef FreezeItem_H_
#define FreezeItem_H_
#include "cocos2d.h"
#include "Item.h"
using namespace cocos2d;
class FreezeItem : public Item{
public:
	FreezeItem();
	virtual ~FreezeItem();

	static FreezeItem* createFreezeItem();
};

#endif /* FreezeItem_H_ */
