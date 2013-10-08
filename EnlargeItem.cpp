/*
 * EnlargeItem.cpp
 *
 *  Created on: Sep 23, 2013
 *      Author: daniel
 */

#include "EnlargeItem.h"

EnlargeItem::EnlargeItem() {
	function = "enlarge";

}

EnlargeItem::~EnlargeItem() {
	
}

EnlargeItem* EnlargeItem::createEnlargeItem() {

	EnlargeItem* enlargeItem = new EnlargeItem();
	if (enlargeItem
			&& enlargeItem->initWithFile("GameLayer/Items/enlargeItem.png")) {
		return enlargeItem;
	}
	CC_SAFE_DELETE(enlargeItem);
	return NULL;
}

