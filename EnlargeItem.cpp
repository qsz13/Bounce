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
	// TODO Auto-generated destructor stub
}

EnlargeItem* EnlargeItem::createEnlargeItem(){

	EnlargeItem* enlargeItem =new EnlargeItem();
	if(enlargeItem && enlargeItem->initWithFile("GameLayer/Items/enlargeItem.png")){
		enlargeItem->setScale(0.2);
		//enlargeItem->autorelease();
		return enlargeItem;
	}
	CC_SAFE_DELETE(enlargeItem);
	return NULL;
}

