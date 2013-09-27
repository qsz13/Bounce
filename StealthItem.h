/*
 * StealthItem.h
 *
 *  Created on: Sep 27, 2013
 *      Author: daniel
 */

#ifndef STEALTHITEM_H_
#define STEALTHITEM_H_

#include "Item.h"

class StealthItem :public Item {
public:
	StealthItem();
	virtual ~StealthItem();
	static StealthItem* createStealthItem();
};

#endif /* STEALTHITEM_H_ */
