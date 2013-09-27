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
	// TODO Auto-generated destructor stub
}

StealthItem* StealthItem::createStealthItem(){

	StealthItem* stealthItem =new StealthItem();
	if(stealthItem && stealthItem->initWithFile("GameLayer/Items/stealthItem.png")){
		stealthItem->setScale(0.2);
		//shortenItem->autorelease();
		return stealthItem;
	}
	CC_SAFE_DELETE(stealthItem);
	return NULL;
}
