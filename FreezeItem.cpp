/*
 * FreezeItem.cpp
 *
 *  Created on: Sep 26, 2013
 *      Author: daniel
 */

#include "FreezeItem.h"

FreezeItem::FreezeItem() {
	function = "freeze";

}

FreezeItem::~FreezeItem() {
	
}

FreezeItem* FreezeItem::createFreezeItem() {

	FreezeItem* freezeItem = new FreezeItem();
	if (freezeItem
			&& freezeItem->initWithFile("GameLayer/Items/freezeItem.png")) {
		return freezeItem;
	}
	CC_SAFE_DELETE(freezeItem);
	return NULL;

}
