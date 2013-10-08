/*
 * SkewingItem.cpp
 *
 *  Created on: Sep 27, 2013
 *      Author: daniel
 */

#include "SkewingItem.h"

SkewingItem::SkewingItem() {
	function = "magnet";

}

SkewingItem::~SkewingItem() {
}

SkewingItem* SkewingItem::createSkewingItem() {

	SkewingItem* skewingItem = new SkewingItem();
	if (skewingItem
			&& skewingItem->initWithFile("GameLayer/Items/skewingItem.png")) {
		return skewingItem;
	}
	CC_SAFE_DELETE(skewingItem);
	return NULL;
}
