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
	// TODO Auto-generated destructor stub
}


SkewingItem* SkewingItem::createSkewingItem(){

	SkewingItem* skewingItem =new SkewingItem();
	if(skewingItem && skewingItem->initWithFile("GameLayer/Items/skewingItem.png")){
		skewingItem->setScale(0.2);
		//shortenItem->autorelease();
		return skewingItem;
	}
	CC_SAFE_DELETE(skewingItem);
	return NULL;
}
