/*
 * SkewingItem.h
 *
 *  Created on: Sep 27, 2013
 *      Author: daniel
 */

#ifndef MAGNETITEM_H_
#define MAGNETITEM_H_

#include "Item.h"

class SkewingItem: public Item {
public:
	SkewingItem();
	virtual ~SkewingItem();
	static SkewingItem* createSkewingItem();

};

#endif /* MAGNETITEM_H_ */
