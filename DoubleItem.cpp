/*
 * DoubleItem.cpp
 *
 *  Created on: Sep 25, 2013
 *      Author: daniel
 */

#include "DoubleItem.h"

DoubleItem::DoubleItem() {
	function = "double";
}

DoubleItem::~DoubleItem() {
	
}

DoubleItem* DoubleItem::createDoubleItem() {

	DoubleItem* doubleItem = new DoubleItem();
	if (doubleItem
			&& doubleItem->initWithFile("GameLayer/Items/doubleItem.png")) {
		return doubleItem;
	}
	CC_SAFE_DELETE(doubleItem);
	return NULL;
}

