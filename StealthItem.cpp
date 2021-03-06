/*
 * StealthItem.cpp
 *
 *  Created on: Sep 27, 2013
 *      Author: daniel
 */

#include "StealthItem.h"

StealthItem::StealthItem() {
	function = "stealth";

}

StealthItem::~StealthItem() {
}

StealthItem* StealthItem::createStealthItem() {

	StealthItem* stealthItem = new StealthItem();
	if (stealthItem
			&& stealthItem->initWithFile("GameLayer/Items/stealthItem.png")) {
		return stealthItem;
	}
	CC_SAFE_DELETE(stealthItem);
	return NULL;
}
